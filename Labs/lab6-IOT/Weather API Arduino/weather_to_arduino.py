#!/usr/bin/env python3
# weather_bridge.py

import os
import gzip
import json
import random
import requests
import serial
import time

API_KEY        = "52d73842c1b33471f1d6d1d48ad9f87f"
CITY_LIST_PATH = "city.list.json.gz"
CITY_LIST_URL  = "https://bulk.openweathermap.org/sample/city.list.json.gz"
PORT           = "/dev/tty.usbmodem4827E2DFBAD82"
BAUD           = 115200

def ensure_city_list(path, url):
    if not os.path.exists(path):
        print(f"⏬ Downloading city list…")
        resp = requests.get(url, stream=True)
        resp.raise_for_status()
        with open(path, "wb") as f:
            for chunk in resp.iter_content(8192):
                f.write(chunk)
        print("✅ Done.")

def load_cities(path):
    print(f"Loading {path}…")
    with gzip.open(path, "rt", encoding="utf-8") as f:
        cities = json.load(f)
    print(f"Loaded {len(cities):,} cities")
    return cities

def pick_random_city(cities):
    c = random.choice(cities)
    n, country = c["name"], c["country"]
    state = c.get("state","")
    return f"{n},{state},{country}" if state else f"{n},{country}"

def fetch_weather(query):
    url    = "http://api.openweathermap.org/data/2.5/weather"
    params = {"q": query, "units": "imperial", "appid": API_KEY}
    r = requests.get(url, params=params, timeout=10)
    if r.status_code == 401:
        print("❌ Unauthorized:", r.json())
    r.raise_for_status()
    d = r.json()
    return d["main"]["temp"], d["weather"][0]["description"], d["coord"]["lat"], d["coord"]["lon"]

def lookup_county(lat, lon):
    try:
        url = "https://nominatim.openstreetmap.org/reverse"
        p = {"lat": lat, "lon": lon, "format": "json", "zoom": 10, "addressdetails": 1}
        h = {"User-Agent": "ArduinoWeatherClient/1.0"}
        r = requests.get(url, params=p, headers=h, timeout=(3,5))
        r.raise_for_status()
        return r.json().get("address",{}).get("county","")
    except:
        return ""

def main():
    ensure_city_list(CITY_LIST_PATH, CITY_LIST_URL)
    cities = load_cities(CITY_LIST_PATH)

    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)  # allow Arduino to reset

    print("Waiting for RFID scans…")
    while True:
        line = ser.readline().decode("utf-8",errors="ignore").strip()
        if line.startswith("TAG:"):
            print("→ Scan detected:", line)

            # 1) pick & fetch
            query = pick_random_city(cities)
            try:
                temp, desc, lat, lon = fetch_weather(query)
            except Exception as e:
                print("Weather fetch error:", e)
                continue

            # 2) build LOC display
            parts = query.split(",")
            if len(parts)==3:  # US
                name, st, co = parts
                county = lookup_county(lat, lon)
                loc = f"{name},{county},{st}" if county else f"{name},{st}"
            else:
                name, co = parts
                loc = f"{name},{co}"

            # 3) send once
            ser.write(f"LOC:{loc}\n".encode())
            ser.write(f"TMP:{temp:.1f},{desc}\n".encode())
            print(f"  Sent LOC:{loc}")
            print(f"  Sent TMP:{temp:.1f},{desc}")

            # now wait for *next* scan
            print("Waiting for next scan…")

        # small pause to yield CPU
        time.sleep(0.05)

if __name__=="__main__":
    main()
