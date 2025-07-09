// RGB LED 1 (Pins 3, 5, 6)
const int red1 = 3;
const int green1 = 5;
const int blue1 = 6;

// RGB LED 2 (Pins 11, 9, 10)
const int red2 = 11;
const int green2 = 9;
const int blue2 = 10;

void setup() {
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(blue1, OUTPUT);
  
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
}

void loop() {
  // Fade LED1: Red → Green, LED2: Blue → Purple
  fadeBoth(
    255, 0, 0,   0, 255, 0,   // LED1: red → green
    0, 0, 255,   128, 0, 128  // LED2: blue → purple
  );

  // Fade LED1: Green → Blue, LED2: Purple → Yellow
  fadeBoth(
    0, 255, 0,   0, 0, 255,   // LED1: green → blue
    128, 0, 128, 255, 255, 0  // LED2: purple → yellow
  );

  // Fade LED1: Blue → Off, LED2: Yellow → Aqua
  fadeBoth(
    0, 0, 255,   0, 0, 0,     // LED1: blue → off
    255, 255, 0, 0, 255, 255  // LED2: yellow → aqua
  );
}

// Fade both RGB LEDs simultaneously between two colors
void fadeBoth(
  int r1a, int g1a, int b1a, int r1b, int g1b, int b1b,
  int r2a, int g2a, int b2a, int r2b, int g2b, int b2b
) {
  int steps = 100;
  int delayTime = 20;

  for (int i = 0; i <= steps; i++) {
    float t = i / float(steps);

    // LED 1 interpolation
    int r1 = (1 - t) * r1a + t * r1b;
    int g1 = (1 - t) * g1a + t * g1b;
    int b1 = (1 - t) * b1a + t * b1b;

    // LED 2 interpolation
    int r2 = (1 - t) * r2a + t * r2b;
    int g2 = (1 - t) * g2a + t * g2b;
    int b2 = (1 - t) * b2a + t * b2b;

    // Write to LED 1
    analogWrite(red1, r1);
    analogWrite(green1, g1);
    analogWrite(blue1, b1);

    // Write to LED 2
    analogWrite(red2, r2);
    analogWrite(green2, g2);
    analogWrite(blue2, b2);

    delay(delayTime);
  }
}
