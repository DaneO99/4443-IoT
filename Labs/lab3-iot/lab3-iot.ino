// HC-SR04 Pins
const int trigPin = 7;
const int echoPin = 8;

// LED Pins (PWM-capable)
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

  int pwmPins[] = {green1, green2, yellow1, yellow2, red1, red2};
  for (int i = 0; i < 6; i++) {
    pinMode(pwmPins[i], OUTPUT);
  }
}

float measureDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 10000); // Short timeout for responsiveness
  if (duration == 0) {
    return -1.0; // No reading
  }
  return (duration * 0.0343) / 2.0;
}

void setLEDFade(float distance) {
  int pwmPins[] = {green1, green2, yellow1, yellow2, red1, red2};
  
  if (distance < 0 || distance > 30) {
    // No reading or beyond 30 cm -> all LEDs off
    for (int i = 0; i < 6; i++) {
      analogWrite(pwmPins[i], 0);
    }
    return;
  }

  // Calculate brightness inversely proportional to distance
  // Closer = brighter. 0cm = 255, 30cm = 0
  int brightness = map(constrain(distance, 0, 30), 0, 30, 255, 0);

  // Apply brightness to each color with gradual escalation
  analogWrite(green1, brightness);
  analogWrite(green2, brightness);

  if (distance <= 20) {
    analogWrite(yellow1, brightness);
    analogWrite(yellow2, brightness);
  } else {
    analogWrite(yellow1, 0);
    analogWrite(yellow2, 0);
  }

  if (distance <= 10) {
    analogWrite(red1, brightness);
    analogWrite(red2, brightness);
  } else {
    analogWrite(red1, 0);
    analogWrite(red2, 0);
  }
}

void loop() {
  Serial.println("Loop running..."); // Debug, to verify loop is working
  float distance_cm = measureDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  setLEDFade(distance_cm);

  delay(500);
}
