#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
int counter = 0;
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line displayLiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.backlight();
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    lcd.setCursor(1, 0);
    lcd.print(" DHT11 Error! ");
    lcd.setCursor(5, 1);
    lcd.print(counter++);
    Serial.println("DHT11 Error!");
    Serial.print(counter);
    delay(2000);
    lcd.clear();
    return;
  }
  counter = 0;
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(F("Temp: "));
  lcd.print(t);
  delay(1000);
  // set cursor to first column, second row
  lcd.setCursor(0, 1);
  lcd.print(F("Hum : "));
  lcd.print(h);
  delay(2000);
  lcd.clear();
}
