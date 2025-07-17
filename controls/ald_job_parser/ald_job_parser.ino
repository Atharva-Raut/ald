// command_parser.ino
// This interprets command-line arguments as "jobs" for the ALD.
// CMU Hacker Fab 2025
// Joel Gonzalez

// set temperature setpoints for heating elements
int temp_sp1 = 0;
int temp_sp2 = 0;
int temp_sp3 = 0;
int temp_sp4 = 0;

unsigned int num_pulse1 = 0; // number of pulses for ald valve 1
unsigned long pulse_time1 = 0; // Interval for toggling the pin (in milliseconds)

unsigned int num_pulse2 = 0; // number of pulses for ald valve 2
unsigned long pulse_time2 = 0; // Interval for toggling the pin (in milliseconds)

unsigned int num_pulse3 = 0; // number of pulses for ald valve 3
unsigned long pulse_time3 = 0; // Interval for toggling the pin (in milliseconds)

void setup()
{
  Serial.begin(9600);
  Serial.println("Waiting for job...");
}

void loop()
{
  // ALD job is defined as:
  // Number of pulses for each valve (whole number)
  // Duration of pulses for each valve (milliseconds)
  // Temperature set points for each heating element (celsius)
  
  // An example command looks like the following:
  // "8,500,12,200,4,1200,300,180,120,250"
  // This would mean:
  // Eight 500ms pulses for ALD valve 1.
  // Twelve 200ms pulses for ALD valve 2.
  // Four 1200ms pulses for ALD valve 3.
  // (IMPORTANT! The pulses will continue one after another,
  // so we will see valve 1 -> valve 2 -> valve 3 with purging in between each.)
  // Then, thermocouple 1 is set at 300C. TC2 at 180C. TC3 at 120C. And TC4 at 250C.
  // Note that a job must have data for every field.

  int JOB_IN_PROGRESS = 0;

  // job parsing code
  if ((Serial.available() > 0) && (!JOB_IN_PROGRESS))
  {
    Serial.println("Got job!");
    char s[100] = {0};
    String inputString = Serial.readStringUntil('\n'); // Read until newline character
    strcpy(s, inputString.c_str());
    
    // s = "8,500,12,200,4,1200,300,180,120,250"; // example job

    Serial.println(s);
    int result = sscanf(s, "%u,%lu,%u,%lu,%u,%lu,%d,%d,%d,%d", &num_pulse1, &pulse_time1, &num_pulse2, &pulse_time2, &num_pulse3, &pulse_time3, &temp_sp1, &temp_sp2, &temp_sp3, &temp_sp4);

    // unable to parse command-line input properly
    if (result != 10)
    {
      Serial.println("BAD JOB! sscanf result: ");
      Serial.println(result);
      return;
    } else {
      Serial.println("Starting job!");
      JOB_IN_PROGRESS = 1;
    }
  }

}