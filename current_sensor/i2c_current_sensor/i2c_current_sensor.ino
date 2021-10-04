#include <Wire.h>
#include <INA219.h>

INA219 monitor;

float shunt_r_ohm = 2.2;

void setup() 
{
  // Use high baud rate to decrease data transmission time.
  Serial.begin(230400);
  monitor.begin();

  Wire.setClock(1000000);
  
  monitor.configure(INA219::RANGE_16V, 
                    INA219::GAIN_8_320MV, 
                    INA219::ADC_12BIT, 
                    INA219::ADC_12BIT, // use ADC_2SAMP for more accurate sampling
                    INA219::CONT_SH);
  monitor.calibrate(shunt_r_ohm, 0.1);
}

void printCSV(float current_ma)
{
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(current_ma, 5);
}

void printForPlotter(float current_ma)
{
  Serial.print(0);
  Serial.print(" ");
  Serial.print(140);
  Serial.print(" ");
  Serial.println(current_ma, 5);
}

void loop() 
{
  float voltage_mv = monitor.shuntVoltage() * 1000;
  float current_ma = voltage_mv / shunt_r_ohm;
  
  //printForPlotter(current_ma);
  printCSV(current_ma);
}
