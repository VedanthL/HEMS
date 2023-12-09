#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>
#define CURRENT_SENSOR_PIN A0
#define VOLTAGE_SENSOR_PIN 34
#define CURRENT_SENSOR_SENSITIVITY 0.185
#define VOLTAGE_SENSOR_VREF 5.0
#define VOLTAGE_SENSOR_DIVIDER_RATIO 11.0

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("HEMS");
}
void loop(){
  
  float power;
  float cost;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Power: ");
  lcd.print(power,2);
  lcd.print(" W ");
  lcd.setCursor(0,1);
  lcd.print("Cost: ");
  lcd.print(cost,2);
  lcd.print(" INR ");

  Serial.print("P: ");
  Serial.print(power, 2);
  Serial.print("C:");
  Serial.print(cost, 2);
  Serial.println();
  delay(5000);
}