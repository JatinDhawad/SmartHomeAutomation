#include <Servo.h>

// --- Pin Definitions ---
const int gasSensorPin   = A0;
const int flameSensorPin = 2;
const int irSensorPin    = 3;
const int trigPin        = 4;
const int echoPin        = 5;
const int buttonPin      = 6;
const int buzzerPin      = 7;
const int relayPin       = 8;
const int servoPin       = 9;
const int ledPin         = 10;
const int lightPin       = 12;

// --- Thresholds & Positions ---
int gasThreshold        = 1000;
int distanceThreshold   = 100;
int servoSafePosition   = 0;
int servoClosedPosition = 45;
int doorClosedPosition  = 90;

// --- Panic Mode ---
bool panicTriggered = false;
unsigned long panicStartTime = 0;
const unsigned long panicDuration = 5000;

Servo windowServo;

void setup() {
  Serial.begin(9600);  // For data transmission to ESP8266

  pinMode(gasSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  windowServo.attach(servoPin);
  windowServo.write(servoSafePosition);

  noTone(buzzerPin);
  digitalWrite(relayPin, LOW);
  digitalWrite(lightPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // --- Sensor Readings ---
  int gasValue = analogRead(gasSensorPin);
  int flameRaw = digitalRead(flameSensorPin);
  int flameValue = (flameRaw == HIGH) ? 0 : 1;
  int irRaw = digitalRead(irSensorPin); // HIGH = No Motion, LOW = Motion
  int buttonRaw = digitalRead(buttonPin);

  // --- Ultrasonic Distance ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // --- Panic Mode Check ---
  if (!panicTriggered && buttonRaw == LOW) {
    panicTriggered = true;
    panicStartTime = millis();
  }
  if (panicTriggered && millis() - panicStartTime > panicDuration) {
    panicTriggered = false;
  }

  // --- IR Motion Handling ---
  if (irRaw == LOW) {
    tone(buzzerPin, 1000);
    digitalWrite(ledPin, HIGH);
  } else {
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
  }

  // --- Hazard Actions ---
  bool hazard = gasValue > gasThreshold || flameValue == 1 || distance < distanceThreshold || panicTriggered;

  if (hazard) {
    tone(buzzerPin, 1000);
    digitalWrite(relayPin, HIGH);
    digitalWrite(lightPin, HIGH);
    digitalWrite(ledPin, HIGH);

    windowServo.write(panicTriggered ? doorClosedPosition : servoClosedPosition);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(lightPin, LOW);
    if (irRaw == HIGH) {
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
    }
    windowServo.write(servoSafePosition);
  }

  // --- Transmit Data to ESP8266 ---
  Serial.print(gasValue); Serial.print(",");
  Serial.print(flameValue); Serial.print(",");
  Serial.print(irRaw == LOW ? 1 : 0); Serial.print(",");
  Serial.print(distance); Serial.print(",");
  Serial.println(panicTriggered ? 1 : 0); // End line

  delay(500);
}
