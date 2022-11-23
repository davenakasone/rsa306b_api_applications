
/*
  transformer, 120 VAC --> 2.1 kV  (RMS)
  don't keep it on too long, it will get hot
  always run on an isolation transformer
*/
 
//#define DEBUG_UART 9999

const int adc_pin = A0;
const int sig_pin = 7;
const int T_ac = 17;  // AC period @ 60 Hz ~ 17 ms
int on_time;
int off_time;
int adc_val;

void setup() 
{
  on_time = 0;
  off_time = 0;
  adc_val = 0;
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
  adc_val = analogRead(adc_pin);
  on_time = T_ac + (adc_val / 100) * T_ac;
  off_time = 2 * on_time;
  
  #ifdef DEBUG_UART
    Serial.print("ADC= ");
    Serial.print(adc_val); 
    Serial.print("  ,  on_time= "); 
    Serial.print(on_time);
    Serial.print(" ms");
    Serial.print("  ,  off_time= ");  
    Serial.print(off_time);
    Serial.print(" ms\n");  
  #endif
  
  digitalWrite(sig_pin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(on_time);
  digitalWrite(sig_pin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(off_time);
}
