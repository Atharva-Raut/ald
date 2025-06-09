// Calculations for timer 1 with period 2000ms
// 2000ms corresponds to a CTC frequency of 0.5 Hz
// For prescaler 1024, OCR1A = 16000000/(2*1024*0.5) - 1 = 15624

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

// These define's must be placed at the beginning before #include "TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#define USE_TIMER_1     true
#define USE_TIMER_2     true

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TimerInterrupt.h"

#define RELAY1_INTERVAL_MS    1000
#define RELAY2_INTERVAL_MS    2000

#ifndef RELAY1_PIN
  #define RELAY1_PIN A0
#endif

#ifndef RELAY2_PIN A1
  #define RELAY2_PIN A1
#endif

void relay1_handler(void)
{
  static bool relay1_state = false;

  //timer interrupt toggles pin LED_BUILTIN
  digitalWrite(RELAY1_PIN, relay1_state);
  relay1_state = !relay1_state;
}

void relay2_handler(void)
{
  static bool relay2_state = false;
 
  //timer interrupt toggles outputPin
  digitalWrite(RELAY2_PIN, relay2_state);
  relay2_state = !relay2_state;
}

void setup()
{
	Serial.begin(9600);

	for (int i=0;i<4;i++)
		thermocouples[i].begin(i+3); // pins 3,4,5,6

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);

  Serial.print(F("\nStarting Argument_None on "));
  Serial.println(BOARD_TYPE);
  Serial.println(TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Timer0 is used for micros(), millis(), delay(), etc and can't be used
  // Select Timer 1-2 for UNO, 1-5 for MEGA, 1,3,4 for 16u4/32u4
  // Timer 2 is 8-bit timer, only for higher frequency
  // Timer 4 of 16u4 and 32u4 is 8/10-bit timer, only for higher frequency
  
  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,
  // For 16-bit timer 1, 3, 4 and 5, set frequency from 0.2385 to some KHz
  // For 8-bit timer 2 (prescaler up to 1024, set frequency from 61.5Hz to some KHz

  if (ITimer1.attachInterruptInterval(RELAY1_INTERVAL_MS, relay1_handler))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

  // Select Timer 1-2 for UNO, 0-5 for MEGA, 1,3,4 for 32u4
  // Timer 2 is 8-bit timer, only for higher frequency
  ITimer2.init();

  if (ITimer2.attachInterruptInterval(RELAY2_INTERVAL_MS, relay2_handler))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer2. Select another freq. or timer"));
}

void readThermocouples()
{
	for (int i=0; i<4; ++i)
	{
		current_reading[i] = thermocouples[i].readProbe() / 1000;
	}
	
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
	
	Serial.println(String(tc1_avg) + ";" + String(tc2_avg) + ";" + String(tc3_avg) + ";" + String(tc4_avg) + ";");
	//Serial.print(";");
	//Serial.print(tc2_avg);
	//Serial.print(";");
	//Serial.print(tc3_avg);
	//Serial.print(";");
	//Serial.print(tc4_avg);
	//Serial.println(";");

	delay(50);
}

void loop()
{
	// read incoming serial data:
  char inChar = Serial.read();

	if (inChar == 't')
		readThermocouples();
}