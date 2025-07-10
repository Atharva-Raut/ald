// ald_valve_control.ino
// This file actuates ALD valves based on set intervals.
// CMU Hacker Fab 2025
// Joel Gonzalez, Haewon Uhm

#define RELAY6_PIN A3
#define RELAY7_PIN A4
#define RELAY8_PIN A5

unsigned long previousMillis_1 = 0;
const long interval_1 = 1000; // Interval for toggling the pin (in milliseconds)
bool outputState_1 = LOW;

unsigned long previousMillis_2 = 0;
const long interval_2 = 2000; // Interval for toggling the pin (in milliseconds)
bool outputState_2 = LOW;

unsigned long previousMillis_3 = 0;
const long interval_3 = 500; // Interval for toggling the pin (in milliseconds)
bool outputState_3 = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY6_PIN, OUTPUT);
  pinMode(RELAY7_PIN, OUTPUT);
  pinMode(RELAY8_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // valve 1
  if (currentMillis - previousMillis_1 >= interval_1) {
    // Save the last time you toggled the pin
    previousMillis_1 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_1 == LOW) {
      outputState_1 = HIGH;
    } else {
      outputState_1 = LOW;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY6_PIN, outputState_1);
  }

  // valve 2
  if (currentMillis - previousMillis_2 >= interval_2) {
    // Save the last time you toggled the pin
    previousMillis_2 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_2 == LOW) {
      outputState_2 = HIGH;
    } else {
      outputState_2 = LOW;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY7_PIN, outputState_2);
  }

  // valve 3
  if (currentMillis - previousMillis_3 >= interval_3) {
    // Save the last time you toggled the pin
    previousMillis_3 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_3 == LOW) {
      outputState_3 = HIGH;
    } else {
      outputState_3 = LOW;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY8_PIN, outputState_3);
  }

}
