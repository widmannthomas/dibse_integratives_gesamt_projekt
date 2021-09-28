#include <INA219.h>

INA219 monitor;

float shunt_r_ohm = 2.2;

void setup() 
{
  Serial.begin(115200);
  monitor.begin();
  monitor.configure(INA219::RANGE_16V, 
                    INA219::GAIN_8_320MV, 
                    INA219::ADC_128SAMP, 
                    INA219::ADC_4SAMP, 
                    INA219::CONT_SH);
  monitor.calibrate(shunt_r_ohm, 0.1);
}

void loop() 
{
  float voltage_mv = monitor.shuntVoltage() * 1000;
  float current_ma = voltage_mv / shunt_r_ohm;
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(current_ma, 5);
}
