#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // construct LCD object

void setup() {
  // put your setup code here, to run once:
// Serial monitoring on PC (debug only)
  Serial.begin(9600);
  
  // LCD initialisieren
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Erste Zeile");
  lcd.setCursor(0,1);
  lcd.print("Zweite Zeile");

}
