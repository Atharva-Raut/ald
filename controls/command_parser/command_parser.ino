// command_parser.ino
// This interprets command-line arguments as "jobs" for the ALD.
// CMU Hacker Fab 2025
// Joel Gonzalez

void setup()
{
  Serial.begin(9600);
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

  // This files is responsible for parsing commands appropriately as described above.
}
