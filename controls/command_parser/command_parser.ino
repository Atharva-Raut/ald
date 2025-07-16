// command_parser.ino
// This interprets command-line arguments as "jobs" for the ALD.
// CMU Hacker Fab 2025
// Joel Gonzalez

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
  // 8,500.0,12,200.0,4,1200.0,300.0,180.0,120.0,250.0
  // This would mean:
  // Eight 500ms pulses for ALD valve 1.
  // Twelve 200ms pulses for ALD valve 2.
  // Four 1200ms pulses for ALD valve 3.
  // (IMPORTANT! The pulses will continue one after another,
  // so we will see valve 1 -> valve 2 -> valve 3 with purging in between each.)
  // Then, thermocouple 1 is set at 300.0C. TC2 at 180.0C. TC3 at 120.0C. And TC4 at 250.0C.
  // Note that a job must have data for every field.

  if (Serial.available() > 0) { // Check if data is available in the serial buffer
    char s[100] = {0};
    String inputString = Serial.readStringUntil('\n'); // Read until newline character
    strcpy(s, inputString.c_str());
    
    // s = "8,500.0,12,200.0,4,1200.0,300.0,180.0,120.0,250.0";

    float f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;

    int result = sscanf(s, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &f1, &f2 ,&f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10);

    // unable to parse command-line input
    if (result != 10)
    {
      Serial.println("BAD JOB");
      return;
    }

    Serial.print("You entered: ");
    Serial.println(s);
  }

}
