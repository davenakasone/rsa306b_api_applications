
/*
  yk3000 @ 315 MHz
  toggles transmitting through the 4 channels
  select interval with ADC
*/
 
//#define DEBUG_UART 9999

int adc_pin = A0;
int adc_val = 0;
int chanA = 7;
int chanB = 6;
int chanC = 5;
int chanD = 4;
int min_time = 100;
int tdiv = 1;
int interval = 0;


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(chanA, OUTPUT);
  pinMode(chanB, OUTPUT);
  pinMode(chanC, OUTPUT);
  pinMode(chanD, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(chanA, LOW);
  digitalWrite(chanB, LOW);
  digitalWrite(chanC, LOW);
  digitalWrite(chanD, LOW);
  #ifdef DEBUG_UART
    Serial.begin(9600);
  #endif
}


void loop() 
{
  adc_val = analogRead(adc_pin);
  interval = min_time + (tdiv * adc_val);
  #ifdef DEBUG_UART
    Serial.print("ADC= ");
    Serial.print(adc_val); 
    Serial.print("  ,  interval= "); 
    Serial.print(interval);
    Serial.print(" ms\n");
  #endif
  
  digitalWrite(chanA, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(chanA, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval);

  digitalWrite(chanB, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(chanB, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval);

  digitalWrite(chanC, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(chanC, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval);

  digitalWrite(chanD, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(chanD, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(interval);
}
