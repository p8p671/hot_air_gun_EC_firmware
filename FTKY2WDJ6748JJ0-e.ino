#include <Wire.h> 
#include <math.h>


const int thermistor_output = A1;
int dataPoint1;
int dataPoint2;
int dataPoint3;
int dataPoint4;
float max_temp = 400;
int chauffe; 
int vent;
int plus;
int moins;
int led;
int temperature;
int etatboutonplus;
int etatboutonmoins;
int reed;

void setup()
{
  Serial.begin(115200);  /* Define baud rate for serial communication */
  temperature=200;
  chauffe= 13;
  vent=12;
  plus=11;
  moins=7;
  led=3;
  reed=2;
  pinMode(chauffe, OUTPUT); 
  pinMode(vent, OUTPUT); 
  pinMode(plus, INPUT_PULLUP); 
  pinMode(moins, INPUT_PULLUP); 
  pinMode(led, OUTPUT);
  pinMode(reed, INPUT_PULLUP);
  
                   // initialize the lcd 

  // Serial.print("based on ");
  // Serial.print("Station a ");
  // Serial.println("air chaud ");
  // Serial.println("Marmotte 2017");
  // Serial.println("Version 1 ");
  // delay(500);
  // Serial.println("modified to Serial display edition in 2021 ");
  // delay(500 );
    
}


void loop()
{
  int thermistor_adc_val;
  double output_voltage, thermistor_resistance, therm_res_ln, temperaturemesure; 
  thermistor_adc_val = analogRead(thermistor_output);
  output_voltage = ( (thermistor_adc_val * 5.0) / 1023.0 );
  thermistor_resistance = ( ( 5 * ( 10.0 / output_voltage ) ) - 10 ); /* Resistance in kilo ohms */
  thermistor_resistance = thermistor_resistance * 1000 ; /* Resistance in ohms   */
  therm_res_ln = log(thermistor_resistance);
  /*  Steinhart-Hart Thermistor Equation: */
  /*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)   */
  /*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperaturemesure = ( 1 / ( 0.001129148 + ( 0.000234125 * therm_res_ln ) + ( 0.0000000876741 * therm_res_ln * therm_res_ln * therm_res_ln ) ) ); /* Temperature in Kelvin */
  temperaturemesure = temperaturemesure - 273.15; /* Temperature in degree Celsius */
  //Serial.print("Resistance in ohms = ");
  //Serial.println(thermistor_resistance);
   dataPoint1 = temperature;
   dataPoint2 = temperaturemesure;
   dataPoint3 = 0;
   dataPoint4 = 0;
   //Serial.print("SET: ");
   //Serial.print(temperature);
   //Serial.println(" C");
   //Serial.print("NOW: ");
   //Serial.print(temperaturemesure);
   //Serial.println(" C");
   Serial.print(dataPoint1);
   Serial.print(",");
   Serial.print(dataPoint2);
   Serial.print(",");
   Serial.print(dataPoint3);
   Serial.print(",");
   Serial.println(dataPoint4);

   delay(500);
{
 
  
  if (temperaturemesure <= temperature)
  {
  
  digitalWrite(chauffe, HIGH);
  digitalWrite(led, HIGH);
  digitalWrite(vent, HIGH);
  }
  else {
    digitalWrite(chauffe, LOW);
    digitalWrite(led, LOW);
    digitalWrite(vent, HIGH);
  }
  }
 

  
  if (digitalRead (11) == LOW)
  {
   
    temperature=temperature+10;
     if (temperature > max_temp)
    {
        temperature = max_temp;  
      }
  }
else {
 
  }

  if (digitalRead (7) == LOW)
 {
   
    temperature=temperature-10;
    
  }
else {

 }
  delay(100);

  
}
