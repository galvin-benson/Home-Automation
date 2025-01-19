#include <Servo.h>
#define TRIG_PIN 5
#define ECHO_PIN 4
#define SERVO_PIN 0
#define PIR_PIN 14
#define FAN_PIN 16
#define LED_PIN 13
#define BUZZER_PIN 15
#define LDR_PIN A0
#define MQ2_PIN 12
Servo servo;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  servo.attach(SERVO_PIN);
  servo.write(0); 
}

void loop() {
  long duration;
  int distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100); 
  if (distance <= 20) {
    servo.write(180);
    Serial.println("Door Open");
  } else {
    servo.write(0); 
  }
  delay(100);

  int pirState = digitalRead(PIR_PIN); 
  Serial.println(pirState);
  if (digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(FAN_PIN, HIGH); 
    Serial.println("Motion detected! Fan is ON.");
  } else {
    digitalWrite(FAN_PIN, LOW); 
  }
  delay(100);

  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  if (ldrValue < 500) { 
    digitalWrite(LED_PIN, HIGH); 
    Serial.println("Dark detected! LED is ON.");
  } else {
    digitalWrite(LED_PIN, LOW); 
  }
  delay(100);

  int mq2Value = digitalRead(MQ2_PIN);
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value);
  if (mq2Value > 300) { 
    digitalWrite(BUZZER_PIN, HIGH); 
    Serial.println("Smoke detected! Buzzer is ON.");
  } else {
    digitalWrite(BUZZER_PIN, LOW); 
  }
  delay(100); 
}
