#include <SoftTimers.h>

#define LED_PIN 13
#define TEMPERATURE_PIN A0

SoftTimer blinkTimer;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  blinkTimer.setTimeOutTime(1000); // Configure blink timer to expire every 1000ms
  blinkTimer.reset(); // Start timer
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Read temperature from LM35 sensor
  int rawValue = analogRead(TEMPERATURE_PIN);
  float voltage = (rawValue / 1023.0) * 5.0;
  float temperatureC = (voltage - 0.5) * 100.0;

  // Check temperature and adjust LED blink interval
  if (temperatureC < 30) {
    blinkTimer.setTimeOutTime(250); // Blink every 250ms
  } else {
    blinkTimer.setTimeOutTime(500); // Blink every 500ms
  }

  if (blinkTimer.hasTimedOut()) {
    // Toggle LED state
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));

    // Reset timer for next cycle
    blinkTimer.reset();
  }

  // Print temperature for debugging
  Serial.print("Temperature (°C): ");
  Serial.println(temperatureC);

  // Rest of loop code executes concurrently without blocking
}
