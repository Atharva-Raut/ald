
#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXCS  6
#define MAXCLK 7
#define MAXDO1 8
#define MAXDO2 9
#define MAXDO3 10
#define MAXDO4 11

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCLK, MAXCS, MAXDO1);
Adafruit_MAX31855 thermocouple2(MAXCLK, MAXCS, MAXDO2);
Adafruit_MAX31855 thermocouple3(MAXCLK, MAXCS, MAXDO3);
Adafruit_MAX31855 thermocouple4(MAXCLK, MAXCS, MAXDO4);

double tc1_avg = 0.0;
double tc2_avg = 0.0;
double tc3_avg = 0.0;
double tc4_avg = 0.0;

void setup() {
  Serial.begin(9600);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensors...");
  if (!thermocouple1.begin() || !thermocouple2.begin() || !thermocouple3.begin() || !thermocouple4.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  Serial.println("DONE.");
}

void loop() {
  // read data and average past 50 samples; 100 Hz sample rate
   double tc1 = thermocouple1.readInternal();
   double tc2 = thermocouple2.readInternal();
   double tc3 = thermocouple3.readInternal();
   double tc4 = thermocouple4.readInternal();

   // send data once per second
   Serial.print("Temps:");
   Serial.print(tc1);
   Serial.print(";");
   Serial.print(tc2);
   Serial.print(";");
   Serial.print(tc3);
   Serial.print(";");
   Serial.println(tc4);

   delay(50);
}