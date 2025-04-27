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

void setup()
{
	Serial.begin(9600);

	MAX31855 sensors[4] = {
		MAX31855(6),
		MAX31855(5),
		MAX31855(4),
		MAX31855(3)
	};

	for (int i = 0; i <1 ; ++i) {
		sensors[i].begin();
	}

	while(1){
				
		for (int i=0; i<1; ++i) {
			rawData = sensors[i].readRawData();
			current_reading[i] = sensors[i].getTemperature(rawData);
			//Serial.print(F("Chip No. "));
			//Serial.println(i);
			//Serial.print(F("Temperature"));
			//Serial.println(sensors[i].getTemperature(rawData));
		}
		tc1_readings[index] = current_reading[0];
		tc2_readings[index] = current_reading[1];
		tc3_readings[index] = current_reading[2];
		tc4_readings[index] = current_reading[3];
		
		index = (index + 1) % num_samples;
		
		if (count < num_samples){
			count = count + 1;
		}
		
		double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
		for (int i = 0; i<count; i= i+1){
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
	

		delay(1000);
	}
} 
