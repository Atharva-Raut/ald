
#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.

#define CS1 6
#define CS2 5
#define CS3 4
#define CS4 3

// initialize the Thermocouple
Adafruit_MAX31855 temp1(13, CS1, 12);  // SCK, CS, MISO
Adafruit_MAX31855 temp2(13, CS2, 12);
Adafruit_MAX31855 temp3(13, CS3, 12);
Adafruit_MAX31855 temp4(13, CS4, 12);

const int num_samples = 10;
double tc1_readings[num_samples];
double tc2_readings[num_samples];
double tc3_readings[num_samples];
double tc4_readings[num_samples];

int index = 0;
int count = 0;

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
  if (!temp1.begin() || !temp2.begin() || !temp3.begin() || !temp4.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  Serial.println("DONE.");
}

void loop() {
  // read data and average past 50 samples; 100 Hz sample rate
   double tc1 = temp1.readCelsius();
   double tc2 = temp2.readCelsius();
   double tc3 = temp3.readCelsius();
   double tc4 = temp4.readCelsius();

   tc1_readings[index] = tc1;
   tc2_readings[index] = tc2;
   tc3_readings[index] = tc3;
   tc4_readings[index] = tc4;

   index = (index + 1) % num_samples;

     if (count < num_samples) {
    count = count + 1;
  }

  double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
  for (int i = 0; i < count; i = i + 1) {
    sum1 = sum1 + tc1_readings[i];
    sum2 = sum2 + tc2_readings[i];
    sum3 = sum3 + tc3_readings[i];
    sum4 = sum4 + tc4_readings[i];
  }

  tc1_avg = sum1 / count;
  tc2_avg = sum2 / count;
  tc3_avg = sum3 / count;
  tc4_avg = sum4 / count;
   

   // send data once per second
   Serial.print(tc1_avg);
   Serial.print(";");
   Serial.print(tc2_avg);
   Serial.print(";");
   Serial.print(tc3_avg);
   Serial.print(";");
   Serial.print(tc4_avg);
   Serial.println(";");
   

   delay(1000);
}
