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
    return -1.0;
  }
  return (duration * 0.0343) / 2.0;
}

void setIndividualZones(float distance) {
  int pins[] = {green1, green2, yellow1, yellow2, red1, red2};
  
  // Turn all LEDs OFF first
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }

  if (distance < 0 || distance > 35) {
    return; // No reading or too far, leave LEDs OFF
  }

  if (distance <= 35) digitalWrite(green1, HIGH);
  if (distance <= 30) digitalWrite(green2, HIGH);
  if (distance <= 25) digitalWrite(yellow1, HIGH);
  if (distance <= 20) digitalWrite(yellow2, HIGH);
  if (distance <= 15) digitalWrite(red1, HIGH);
  if (distance <= 10) digitalWrite(red2, HIGH);
}

void loop() {
  float distance_cm = measureDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  setIndividualZones(distance_cm);

  delay(200);
}
