// ald_temp_valve_control.ino
// This file reads thermocouple values and uses them to actuate relays connected to heating elements in order to maintain them at a predetermined setpoint using bang-bang controls.
// It also actuates ALD valves based on set intervals.
// CMU Hacker Fab 2025
// Joel Gonzalez, Haewon Uhm

// toggle this if you want the system to do nothing
#define DO_NOTHING 1

#include <Adafruit_MAX31855.h>

int32_t rawData = 0;

const int num_samples = 10;
double tc1_readings[num_samples];
double tc2_readings[num_samples];
double tc3_readings[num_samples];
double tc4_readings[num_samples];
double tc5_readings[num_samples];
double tc6_readings[num_samples];
double tc7_readings[num_samples];
double tc8_readings[num_samples];

int index = 0;
int count = 0;

double tc1_avg = 0.0;
double tc2_avg = 0.0;
double tc3_avg = 0.0;
double tc4_avg = 0.0;
double tc5_avg = 0.0;
double tc6_avg = 0.0;
double tc7_avg = 0.0;
double tc8_avg = 0.0;

double current_reading[8];

// pins 3-10
Adafruit_MAX31855 thermocouples[8] = {Adafruit_MAX31855(3), Adafruit_MAX31855(4), Adafruit_MAX31855(5), Adafruit_MAX31855(6), Adafruit_MAX31855(7), Adafruit_MAX31855(8), Adafruit_MAX31855(9), Adafruit_MAX31855(10)};

// set temperature setpoints for heating elements
#define TEMP_SETPOINT1 150.0
#define TEMP_SETPOINT2 30.0
#define TEMP_SETPOINT3 30.0
#define TEMP_SETPOINT4 150.0

// relay pins to control relays for heating elements
#define RELAY1_PIN 2
#define RELAY2_PIN A0
#define RELAY3_PIN A1
#define RELAY4_PIN A2

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

void setup()
{
  if (DO_NOTHING)
    while(1);

	Serial.begin(9600);

	// relay pins
	pinMode(RELAY1_PIN, OUTPUT);
	pinMode(RELAY2_PIN, OUTPUT);
	pinMode(RELAY3_PIN, OUTPUT);
	pinMode(RELAY4_PIN, OUTPUT);
  pinMode(RELAY6_PIN, OUTPUT);
  pinMode(RELAY7_PIN, OUTPUT);
  pinMode(RELAY8_PIN, OUTPUT);

	// K-type: pins 3,4,5,6
	// J-type: pins 7,8,9,10
	for (int i=0;i<7;i++)
		thermocouples[i].begin();
  
  Serial.begin(9600);
  while (!Serial)
    Serial.println("waiting");

  Serial.println("ready");
}

// takes moving average of thermocouple data
double readThermocouples()
{	
	for (int i=0; i<7; ++i)
		current_reading[i] = thermocouples[i].readCelsius();
	
	tc1_readings[index] = current_reading[0];
	tc2_readings[index] = current_reading[1];
	tc3_readings[index] = current_reading[2];
	tc4_readings[index] = current_reading[3];
	tc5_readings[index] = current_reading[4];
	tc6_readings[index] = current_reading[5];
	tc7_readings[index] = current_reading[6];
	tc8_readings[index] = current_reading[7];
		
	index = (index + 1) % num_samples;
	
	if (count < num_samples)
		count = count + 1;
	
	double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0, sum7 = 0, sum8 = 0;
	for (int i = 0; i<count; i= i+1)
	{
		sum1 += tc1_readings[i];
		sum2 += tc2_readings[i];
		sum3 += tc3_readings[i];
		sum4 += tc4_readings[i];
		sum5 += tc5_readings[i];
		sum6 += tc6_readings[i];
		sum7 += tc7_readings[i];
		sum8 += tc8_readings[i];
	}
	
	tc1_avg = sum1 / count;
	tc2_avg = sum2 / count;
	tc3_avg = sum3 / count;
	tc4_avg = sum4 / count;
	tc5_avg = sum5 / count;
	tc6_avg = sum6 / count;
	tc7_avg = sum7 / count;
	tc8_avg = sum8 / count;
	
	Serial.println(String(tc1_avg) + "; " + String(tc2_avg) + "; " + String(tc3_avg) + "; " + String(tc4_avg) + ";" + String(tc5_avg) + ";" + String(tc6_avg) + ";" + String(tc7_avg) + ";" + String(tc8_avg) + ";");
}

void loop()
{
	// thermocouple control loop
  readThermocouples();
  
	// select whichever thermocouple/relay pairs you want to actuate
  if (tc2_avg > TEMP_SETPOINT1)
    digitalWrite(RELAY1_PIN, HIGH);
  else
    digitalWrite(RELAY1_PIN, LOW);

	if (tc3_avg > TEMP_SETPOINT2)
    digitalWrite(RELAY2_PIN, HIGH);
  else
    digitalWrite(RELAY2_PIN, LOW);

	if (tc4_avg > TEMP_SETPOINT3)
    digitalWrite(RELAY3_PIN, HIGH);
  else
    digitalWrite(RELAY3_PIN, LOW);

	if (tc5_avg > TEMP_SETPOINT4)
    digitalWrite(RELAY4_PIN, HIGH);
  else
    digitalWrite(RELAY4_PIN, LOW);

  // valve actuation
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