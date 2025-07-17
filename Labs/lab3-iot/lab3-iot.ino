// HC-SR04 Pins
const int trigPin = 7;
const int echoPin = 8;

// LED Pins
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

  long duration = pulseIn(echoPin, HIGH, 10000); // Short timeout for responsiveness
  if (duration == 0) {
    return -1.0; // No reading
  }
  return (duration * 0.0343) / 2.0;
}

void setLEDZones(float distance) {
  int pins[] = {green1, green2, yellow1, yellow2, red1, red2};
  
  // Turn everything off first
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }

  if (distance < 0) {
    return; // No reading, keep LEDs off
  }

  if (distance > 30) {
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
  }
  else if (distance > 15) {
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
  }
  else {
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
  }
}

void loop() {
  Serial.println("Loop running..."); // Debug, to verify loop is working
  float distance_cm = measureDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  setLEDZones(distance_cm);

  delay(500);
}
