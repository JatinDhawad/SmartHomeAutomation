#define BLYNK_TEMPLATE_ID "TMPL3PTQu5LSQ"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "cb7Vq6n83V1X5xQCYsLG6fgfz66ge3-I"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "Jatin22";
const char* pass = "12345678";

BlynkTimer timer;

String inputString = "";  // Stores incoming serial line

void sendSensorData() {
  while (Serial.available()) {
    char c = Serial.read();

    // End of line
    if (c == '\n') {
      inputString.trim();  // Remove whitespace
      if (inputString.length() > 0) {
        // Split CSV string
        int gasValue, flameValue, motionValue, distanceValue, panicValue;
        sscanf(inputString.c_str(), "%d,%d,%d,%d,%d", 
               &gasValue, &flameValue, &motionValue, &distanceValue, &panicValue);

        // Debug Print
        Serial.println("=== Data from UNO ===");
        Serial.println("Gas: " + String(gasValue));
        Serial.println("Flame: " + String(flameValue));
        Serial.println("Motion: " + String(motionValue));
        Serial.println("Distance: " + String(distanceValue));
        Serial.println("Panic: " + String(panicValue));
        Serial.println("=====================");

        // Send to Blynk
        Blynk.virtualWrite(V0, gasValue);
        Blynk.virtualWrite(V1, flameValue);      // 1 if flame detected
        Blynk.virtualWrite(V2, motionValue);     // 1 if motion
        Blynk.virtualWrite(V3, distanceValue);   // in cm
        Blynk.virtualWrite(V4, panicValue);      // 1 if panic triggered
      }

      // Clear for next line
      inputString = "";
    } else {
      inputString += c;
    }
  }
}

void setup() {
  Serial.begin(9600);  // Serial from Arduino Uno

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected. IP: " + WiFi.localIP().toString());

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connecting to Blynk...");

  // Timer checks for incoming data every 500ms
  timer.setInterval(500L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
