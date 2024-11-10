#include <Servo.h>

Servo Servo1;
Servo Servo2;
int servo1Pin = 9;
int servo2Pin = 10;

int currentAngle1 = 90;  // Start Servo1 at the middle position
int currentAngle2 = 90;  // Start Servo2 at the middle position
int stepDelay = 20;      // Delay in milliseconds between steps
int stepSize = 1;        // Step size for smoother movement

void setup() {
  Serial.begin(9600);
  Servo1.attach(servo1Pin);
  Servo2.attach(servo2Pin);
  Servo1.write(currentAngle1);
  Servo2.write(currentAngle2);
}

void loop() {
  if (Serial.available() >= 5) {
    int fingers[5];
    bool validData = true;
    
    for (int i = 0; i < 5; i++) {
      int fingerState = Serial.read();
      if (fingerState == 0 || fingerState == 1) {
        fingers[i] = fingerState;
      } else {
        validData = false;
        break;
      }
    }
  
    if (validData) {
      if (fingers[1] == 1) {        // Index finger up: Move Servo1 left
        currentAngle1 -= stepSize * 2;
        if (currentAngle1 < 0) currentAngle1 = 0;
      }
      if (fingers[2] == 1) {        // Middle finger up: Move Servo1 right
        currentAngle1 += stepSize * 2;
        if (currentAngle1 > 180) currentAngle1 = 180;
      }

      if (fingers[3] == 1) {        // Ring finger up: Move Servo2 left
        currentAngle2 -= stepSize * 3;
        if (currentAngle2 < 0) currentAngle2 = 0;
      }
      if (fingers[4] == 1) {        // Pinky finger up: Move Servo2 right
        currentAngle2 += stepSize * 2;
        if (currentAngle2 > 180) currentAngle2 = 180;
      }

      Servo1.write(currentAngle1);
      Servo2.write(currentAngle2);
    }
    
    while (Serial.available() > 0) {
      Serial.read();
    }
  }

  delay(stepDelay);  // Delay between steps for smoother movement
}
