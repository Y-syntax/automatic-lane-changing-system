#include <Servo.h>
// Declaration of components
Servo servo1;

int trigf = 6;
int trigl = 9;
int trigr = 8; // Changed to avoid Serial pin conflict
int echof = 7;
int echol = 10;
int echor = 11; // Changed to avoid Serial pin conflict

long durationf, durationl, durationr;
long disf, disl, disr;

void setup() {
  Serial.begin(9600);

  servo1.attach(3); // Attaching Servo Motor to pin 3
  
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);
  pinMode(trigl, OUTPUT);
  pinMode(echol, INPUT);
  pinMode(trigr, OUTPUT);
  pinMode(echor, INPUT);
}

void steerl() {
  servo1.write(30);
  delay(750);
  servo1.write(90);
}

void steerr() {
  servo1.write(150);
  delay(500);
  servo1.write(90);
}

void loop() {
  servo1.write(90);

  // Front Distance Measurement
  digitalWrite(trigf, LOW);
  delayMicroseconds(2);
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);

  durationf = pulseIn(echof, HIGH);
  disf = (durationf / 2) * 0.0344;
  Serial.print("Front Distance: ");
  Serial.println(disf);

  if (disf < 10) { // Front obstacle detected
    // Left Distance Measurement
    digitalWrite(trigl, LOW);
    delayMicroseconds(2);
    digitalWrite(trigl, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigl, LOW);

    durationl = pulseIn(echol, HIGH);
    disl = (durationl / 2) * 0.0344;
    Serial.print("Left Distance: ");
    Serial.println(disl);

    // Right Distance Measurement
    digitalWrite(trigr, LOW);
    delayMicroseconds(2);
    digitalWrite(trigr, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigr, LOW);

    durationr = pulseIn(echor, HIGH);
    disr = (durationr / 2) * 0.0344;
    Serial.print("Right Distance: ");
    Serial.println(disr);

    if (disl > 10 && disr > 10) {
      if (disl > disr) {
        steerl();
      } else {
        steerr();
      }
    } else {
      Serial.println("No clear path, stopping.");
      servo1.write(90); // Neutral position
    }
  }

  delay(500); // Reduced delay for faster response
}
