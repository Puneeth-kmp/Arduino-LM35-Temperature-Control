/*****************************************************************************************************
Author: Puneeth K
Date: 03-03-2024
Purpose: Control an onboard LED blinking based on temperature readings from an LM35 temperature sensor.
******************************************************************************************************/

#include <SoftTimers.h> // Including the SoftTimers library to create non-blocking timer delays 

#define LED_PIN 13 // Defining the pin connected to the onboard LED
#define LM35TEMPSENSOR_PIN A0 // Defining the pin connected to the LM35 temperature sensor to A0 as mentioned in Problem statement

SoftTimer blinkTimer; // softTimer object to for the LED blinking

void setup() {
  pinMode(LED_PIN, OUTPUT); // setting onboard Led pin as output
  blinkTimer.setTimeOutTime(1000); // setting blink timer to expire every 1000ms initially
  blinkTimer.reset(); // start the timer
  Serial.begin(9600); // Serial communication for debugging
}

void loop() {
  // temperature from LM35 sensor
  int sensorinalue = analogRead(LM35TEMPSENSOR_PIN); // Reading the analog value from the LM35 sensor
  float voltage = (sensorinalue / 1023.0) * 5.0; // Converting the raw value to voltage considering 10bit adc 0-1023
  float temperatureinC = (voltage - 0.5) * 100.0; // Convert the voltage to temperature in Celsius

  // Check temperature and adjust LED blink interval
  if (temperatureinC < 30) {
    blinkTimer.setTimeOutTime(250); // If temperature is below 30°C, the onboardLED will blink every 250ms
  } else {
    blinkTimer.setTimeOutTime(500); // If temperature is above 30°C, he onboardLED will blink every  500ms
  }

  if (blinkTimer.hasTimedOut()) {
    // toggle LED state
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // state toggle of the LED

    // timer reseting for next cycle
    blinkTimer.reset();
  }

  // Printing temperature for debugging
  Serial.print("Temperature (°C): "); // label for the temperature reading
  Serial.println(temperatureinC); // actual temperature reading from lm35 assumeing it is calibrated.

  // Rest of loop code executes without blocking
}

