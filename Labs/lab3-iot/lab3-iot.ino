// HC-SR04 Pins
const int trigPin = 7;
const int echoPin = 8;

// LED Pins (PWM capable, but used here as ON/OFF)
const int green1 = 3;
const int green2 = 5;
const int yellow1 = 6;
const int yellow2 = 9;
const int red1 = 10;
const int red2 = 11;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  int pins[] = {green1, green2, yellow1, yellow2, red1, red2};
  for (int i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

float measureDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    return -1.0;
  }
  return (duration * 0.0343) / 2.0;
}

void setLEDZones(float distance) {
  // Turn everything off first
  int pins[] = {green1, green2, yellow1, yellow2, red1, red2};
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }

  if (distance < 0) {
    return; // No reading, keep all LEDs off
  }

  if (distance > 30) {
    // Only green ON
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
  }
  else if (distance > 15) {
    // Green and Yellow ON
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
  }
  else {
    // Green, Yellow, and Red ON
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
}

void loop() {
  float distance_cm = measureDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  setLEDZones(distance_cm);

  delay(200);
}
