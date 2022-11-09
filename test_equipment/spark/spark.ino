
/*
  sparkgap to simulate partial discharge
  supply_A to PCB with sparkgap, 9V
  supply_B to Arduino and relay, 8V
  use the low current supply
*/
 
//#define DEBUG_UART 9999

int adc_pin = A0;
int adc_val = 0;
int sig_pin = 7;
int rest_time = 3000;
int charge_time = 0;
int min_time = 1000;
int tdiv = 10;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sig_pin, OUTPUT);
  digitalWrite(sig_pin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  #ifdef DEBUG_UART
    Serial.begin(9600);
  #endif
}

void loop() 
{
  
  charge_time = min_time;
  adc_val = analogRead(adc_pin);
  charge_time = charge_time + tdiv * adc_val;
  #ifdef DEBUG_UART
    Serial.print("ADC= ");
    Serial.print(adc_val); 
    Serial.print("  ,  charge time= "); 
    Serial.print(charge_time/1000);
    Serial.print(" s");
    Serial.print("  ,  rest time= ");  
    Serial.print(rest_time/1000);
    Serial.print(" s\n");  
  #endif
  digitalWrite(sig_pin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(charge_time);
  digitalWrite(sig_pin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(rest_time);
}
