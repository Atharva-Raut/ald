// ald_control_systems.ino
// This file reads thermocouple values and uses them to actuate relays connected to heating elements in order to maintain them at a predetermined setpoint using bang-bang controls.
// It also actuates ALD valves based on set intervals.
// It reads user input to execute a "job", which is defined as follows:

// ALD job is defined as:
// Number of pulses for each valve (whole number)
// Duration of pulses for each valve (milliseconds)
// Temperature set points for each heating element (celsius)
// An example command looks like the following:
// 8,500.0,12,200.0,4,1200.0,300.0,180.0,120.0,250.0
// This would mean:
// Eight 500ms pulses for ALD valve 1.
// Twelve 200ms pulses for ALD valve 2.
// Four 1200ms pulses for ALD valve 3.
// (IMPORTANT! The pulses will continue one after another,
// so we will see valve 1 -> valve 2 -> valve 3 with purging in between each.)
// Then, thermocouple 1 is set at 300.0C. TC2 at 180.0C. TC3 at 120.0C. And TC4 at 250.0C.
// Note that a job must have data for every field.

// CMU Hacker Fab 2025
// Joel Gonzalez, Haewon Uhm

// toggle this if you want the system to do nothing
#define DO_NOTHING 1
// relay pins to control relays for heating elements
#define RELAY1_PIN 2
#define RELAY2_PIN A0
#define RELAY3_PIN A1
#define RELAY4_PIN A2
// relay pins to control relays for ALD valves
#define RELAY6_PIN A3
#define RELAY7_PIN A4
#define RELAY8_PIN A5

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
float temp_sp1 = 0.0;
float temp_sp2 = 0.0;
float temp_sp3 = 0.0;
float temp_sp4 = 0.0;

int num_pulse1 = 0;
unsigned long previousMillis_1 = 0;
long pulse_time1 = 0; // Interval for toggling the pin (in milliseconds)
bool outputState_1 = LOW;

int num_pulse2 = 0;
unsigned long previousMillis_2 = 0;
long pulse_time2 = 0; // Interval for toggling the pin (in milliseconds)
bool outputState_2 = LOW;

int num_pulse3 = 0;
unsigned long previousMillis_3 = 0;
long pulse_time3 = 0; // Interval for toggling the pin (in milliseconds)
bool outputState_3 = LOW;

unsigned int JOB_IN_PROGRESS = 0;

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

  // Serial.println(String(tc1_avg) + "; " + String(tc2_avg) + "; " + String(tc3_avg) + "; " + String(tc4_avg) + ";" + String(tc5_avg) + ";" + String(tc6_avg) + ";" + String(tc7_avg) + ";" + String(tc8_avg) + ";");
}

void actuateHeatingElements()
{
  // select whichever thermocouple/relay pairs you want to actuate
  if (tc2_avg > temp_sp1)
    digitalWrite(RELAY1_PIN, HIGH);
  else
    digitalWrite(RELAY1_PIN, LOW);

  if (tc3_avg > temp_sp2)
    digitalWrite(RELAY2_PIN, HIGH);
  else
    digitalWrite(RELAY2_PIN, LOW);

  if (tc4_avg > temp_sp3)
    digitalWrite(RELAY3_PIN, HIGH);
  else
    digitalWrite(RELAY3_PIN, LOW);

  if (tc5_avg > temp_sp4)
    digitalWrite(RELAY4_PIN, HIGH);
  else
    digitalWrite(RELAY4_PIN, LOW);
}

void precursorValveActuation()
{
  // valve actuation
  unsigned long currentMillis = millis();

  // valve 1
  if ((currentMillis - previousMillis_1 >= pulse_time1) && (num_pulse1 > 0)) {
    // Save the last time you toggled the pin
    previousMillis_1 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_1 == LOW) {
      outputState_1 = HIGH;
    } else {
      outputState_1 = LOW;
      num_pulse1--;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY6_PIN, outputState_1);
  }

  // valve 2
  if ((currentMillis - previousMillis_2 >= pulse_time2) && (num_pulse2 > 0)) {
    // Save the last time you toggled the pin
    previousMillis_2 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_2 == LOW) {
      outputState_2 = HIGH;
    } else {
      outputState_2 = LOW;
      num_pulse2--;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY7_PIN, outputState_2);
  }

  // valve 3
  if ((currentMillis - previousMillis_3 >= pulse_time3) && (num_pulse3 > 0)) {
    // Save the last time you toggled the pin
    previousMillis_3 = currentMillis;

    // If the output is currently LOW, make it HIGH
    // and vice-versa
    if (outputState_3 == LOW) {
      outputState_3 = HIGH;
    } else {
      outputState_3 = LOW;
      num_pulse3--;
    }

    // Set the output pin to the new state
    digitalWrite(RELAY8_PIN, outputState_3);
  }
}

void loop()
{
  // check if all ALD pulses have finished
  if (JOB_IN_PROGRESS && (num_pulse1 == 0) && (num_pulse2 == 0) && (num_pulse3 == 0))
    {
      JOB_IN_PROGRESS = 0;
      Serial.println("Job is done!");
    }

  // job parsing code
  if ((Serial.available() > 0) && (!JOB_IN_PROGRESS))
  {
    Serial.println("Got job!");
    char s[100] = {0};
    String inputString = Serial.readStringUntil('\n'); // Read until newline character
    strcpy(s, inputString.c_str());
    
    // s = "8,500.0,12,200.0,4,1200.0,300.0,180.0,120.0,250.0"; // example job

    int result = sscanf(s, "%u,%ld,%u,%ld,%u,%ld,%f,%f,%f,%f", &num_pulse1, &pulse_time1, &num_pulse2, &pulse_time2, &num_pulse3, &pulse_time3, &temp_sp1, &temp_sp2, &temp_sp3, &temp_sp4);

    // unable to parse command-line input properly
    if (result != 10)
    {
      Serial.println("BAD JOB!");
      return;
    } else {
      JOB_IN_PROGRESS = 1;
    }
  }

  if (JOB_IN_PROGRESS)
  {
    // heating control loop
    readThermocouples();
    actuateHeatingElements();

    // ALD valve control
    precursorValveActuation();
  }
}