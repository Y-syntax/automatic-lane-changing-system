#include<Servo.h>

// Initialize servo and distance variables
Servo s;
int distf=0,distl=0,distr=0;

void setup() {
  s.attach(6);              // Attach the servo motor to pin 6
  Serial.begin(9600);       // Start serial communication at 9600 baud
  pinMode(3,OUTPUT);        // Trigger pin for ultrasonic sensor
  pinMode(2,INPUT);         // Echo pin for ultrasonic sensor
  s.write(90);              // Set servo to center (90 degrees)
  delay(1000);              // Wait for servo to stabilize
}

void loop() {
  // Get front distance
  distf = getDistance();

  if(distf<20) { // Obstacle detected in front
    // Check left side
    s.write(0);  
    delay(1000);              
    distl = getDistance(); // Get left distance

    // Check right side
    s.write(180);           
    delay(1000);
    distr = getDistance();  // Get right distance

    s.write(90); // Reset to front
    delay(1000);

    // Decide lane change direction
    if(distl>distr && distl>15) {
      Serial.println("Turn Left");
    }
    else if(distr>distl && distr>15) {
      Serial.println("Turn Right");
    }
    else {
      Serial.println("Brake");
    }
  } else {
    Serial.println("Move Forward");
  }

  delay(1000); // Wait before next loop
}

// Function to calculate distance using ultrasonic sensor
int getDistance() {
  digitalWrite(3,LOW);
  delayMicroseconds(2);
  digitalWrite(3,HIGH);
  delayMicroseconds(10);
  digitalWrite(3,LOW);

  // Calculate duration of echo pulse
  int duration = pulseIn(2,HIGH);
  
  // Convert to distance in cm (sound speed: 343 m/s)
  return duration*0.034/2;
}
