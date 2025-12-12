// Arduino Nano TRX Mic and CW Switch V0.1
// LCD 16x2 
// Stéphane F4BIT/N4BIT
// stephane@mangeolle.fr
// Copyleft@2025 for Hamradio

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int switchSSB = 2;
const int switchCW = 3;

void setup() {
  pinMode(switchSSB, INPUT_PULLUP); // interrupteur connecté à la masse
  pinMode(switchCW, INPUT_PULLUP);

// Message d'accueil sur le LCD

lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(" Master Station");
lcd.setCursor(0, 1);
lcd.print("  v0.1 - F4BIT");
delay(4000);
}

void loop() {
  int etatSSB = digitalRead(switchSSB);
  int etatCW = digitalRead(switchCW);

  // comme INPUT_PULLUP → LOW = appuyé / ON
  lcd.setCursor(0, 0);
  lcd.print("IC-7300 : ");
  lcd.print(etatSSB == LOW ? "SSB " : "    ");
  lcd.print(etatCW == LOW ? "CW " : "    ");
  
  lcd.setCursor(0, 1);
  lcd.print("IC-9700 : ");
  lcd.print(etatSSB == LOW ? "   " : "SSB ");
  lcd.print(etatCW == LOW ? "   " : "CW ");

  delay(200); // mise à jour douce
}
