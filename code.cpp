// C++ code
//
int r1 = 12;
int pir1 = 6;
int blue = 4;
int interrupt_pin1 = 2;
int pir1stat = 0;
bool interrupt1_ON = false;
int orange = 9;
int timer_led = 8;
void setup()
{
  pinMode(r1, OUTPUT);
  pinMode(pir1, INPUT);
  pinMode(interrupt_pin1, INPUT);
  pinMode(timer_led,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin1),int1_function,CHANGE);
  Serial.begin(9600);
  
  
  PCICR |= 0b00000100; // enabling the port group from D0 to D7
  PCMSK2 |= 0b00100000; //making D5 as the port for the interrupt
  
  
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 62499;
  
  TCCR1B |= (1<<CS12) | (1<<CS10);
  
  TIMSK1 |= (1<<OCIE1A);
  
  TCCR1B |= (1<< WGM12);
  sei();

}

void loop()
{
  pir1stat = digitalRead(pir1);
  if(pir1stat == HIGH)
  {
    Serial.println("Motion detected in the pir motion sensor");
    digitalWrite(r1,HIGH);
    delay(500);
    digitalWrite(r1,LOW);
  }
  
}

void int1_function()
{
  Serial.println("Interrupt 1");
  digitalWrite(blue,!digitalRead(blue));
}


ISR(PCINT2_vect)
{
  Serial.println("Interrupt 2");
  digitalWrite(orange, !(digitalRead(orange)));
}

ISR(TIMER1_COMPA_vect)
{
  Serial.println("Timer Interrupt");
  digitalWrite(timer_led, digitalRead(timer_led)^1);
}