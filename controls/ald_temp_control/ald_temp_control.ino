// substrate heater control loop - bangbang controls

#include <MAX31855.h>

int32_t rawData = 0;

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

double current_reading[4];

MAX31855_Class thermocouples[4];

#define TEMP_SETPOINT 225.0
#define RELAY1_PIN A0

void setup()
{
	Serial.begin(9600);

	for (int i=3;i<7;i++)
		thermocouples[i-3].begin(i); // pins 3,4,5,6

  pinMode(RELAY1_PIN, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial)
    Serial.println("waiting");

  Serial.println("ready");
}

double readThermocouples()
{
	for (int i=0; i<4; ++i)
		current_reading[i] = thermocouples[i].readProbe() / 1000;
	
	tc1_readings[index] = current_reading[0];
	tc2_readings[index] = current_reading[1];
	tc3_readings[index] = current_reading[2];
	tc4_readings[index] = current_reading[3];
		
	index = (index + 1) % num_samples;
	
	if (count < num_samples)
		count = count + 1;
	
	double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	for (int i = 0; i<count; i= i+1)
	{
		sum1 = sum1 + tc1_readings[i];
		sum2 = sum2 + tc2_readings[i];
		sum3 = sum3 + tc3_readings[i];
		sum4 = sum4 + tc4_readings[i];
	}
	
	tc1_avg = sum1 / count;
	tc2_avg = sum2 / count;
	tc3_avg = sum3 / count;
	tc4_avg = sum4 / count;
	
	Serial.println(String(tc1_avg) + "; " + String(tc2_avg) + "; " + String(tc3_avg) + "; " + String(tc4_avg) + ";");
  // Serial.println(count);

	delay(500);

  return tc1_avg; // connected thermocouple
}

void loop()
{
	// read incoming serial data:
  // char inChar = Serial.read();

  // static int tc1_count = 0;
  // tc1_count++;
  // if (count %)
  // if (count % 2)
  //   digitalWrite(RELAY1_PIN, HIGH);
  // else
  //   digitalWrite(RELAY1_PIN, LOW);
  // delay(500);

  // if (inChar == 't')
  double tc_reading = readThermocouples();
  
  if (tc_reading < TEMP_SETPOINT)
    digitalWrite(RELAY1_PIN, HIGH);
  else
    digitalWrite(RELAY1_PIN, LOW);

  Serial.println("loop");
}