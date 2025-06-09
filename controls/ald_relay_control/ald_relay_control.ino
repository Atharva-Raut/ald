// Calculations for timer 1 with period 2000ms
// 2000ms corresponds to a CTC frequency of 0.5 Hz
// For prescaler 1024, OCR1A = 16000000/(2*1024*0.5) - 1 = 15624

bool relay_state = false;

void setup()
{
  pinMode(12, OUTPUT);  // Set pin 12 (LED) as output
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B = bit(CS12) | bit(CS10);             // Set prescalar of timer 1 to 1024  
  TIMSK1 = bit(OCIE1A);                       // Enable compare match A on timer 1
  OCR1A = 15624;
  sei();  // Enable back the interrupts
}

void loop() {
  // Do nothing in the loop function
}

// With the settings above, this ISR will trigger each 1000ms.
ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;  // Reset the counter
  relay_state = !relay_state;
  digitalWrite(12,relay_state); // Write new state to the LED on pin 12
}