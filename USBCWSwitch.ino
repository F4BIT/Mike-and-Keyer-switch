// Arduino Nano TRX Mic and CW Switch V0.1
// LCD 16x2 
// Stéphane F4BIT/N4BIT
// stephane@mangeolle.fr
// Copyleft@2025 for Hamradio

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //  addresse du LCD en I2C sur A4-A5

// initialise les descriptions des antennes

char TRX1[16] =     "TRX 1";
char description1[16] = "IC 7300";
char TRX2[16] =     "TRX 2";
char description2[16] = "IC 9700";

// initialise les pins relais

const int relay1 = 12; // relais 1
const int relay2 = 11; // relais 2

// initialise les pins boutons

const int boutonUP = 2; // déclaration du bouton Haut
const int boutonDOWN = 3; // déclaration du bouton Bas

int boutonUPappui = 0; // variable lorsque j'appuie sur le bouton
int boutonDOWNappui = 0; // variable lorsque j'appuie sur le bouton

int etatboutonUP = 0; // etat dans lequel se trouve le bouton
int etatboutonDOWN = 0; // etat dans lequel se trouve le bouton

int Data = 0; // variable
int oldData; // variable

void setup()
{

  // initialise les pins relais 1,2,3,4,5,6 comme output

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  // initialise les relais à OFF

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

// initialise les pins bouttons à input

pinMode(boutonUP, INPUT_PULLUP);// déclaration du bouton en entrée avec la résistance pullup
pinMode(boutonDOWN, INPUT_PULLUP);// déclaration du bouton en entrée avec la résistance pullup

// initialise le moniteur serie

Serial.begin(9600);// mon port de communication
Serial.println ("TRX Mic and CW Switch V0.1 by F4BIT V0.1 11/2025");

// Message d'accueil sur le LCD

lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(" TRX Mic and CW Switch");
lcd.setCursor(0, 1);
lcd.print("  v0.1 - F4BIT");
delay(4000);

}
void loop()
{
  // test des boutons +-

  boutonUPappui = digitalRead(boutonUP);//etatbouton est égale à la lecture du bouton
  boutonDOWNappui = digitalRead(boutonDOWN);//etatbouton est égale à la lecture du bouton
  oldData = Data;
  if ((boutonUPappui == HIGH && etatboutonUP == LOW) && (Data >= 1 && Data <= 5 ) ) {
    Data = Data + 1;
    delay(100);
  }
  if (Data >= 6) {
    Data = 6;
  }
  else
  {
    Data = Data;
  }
  if ((boutonDOWNappui == HIGH && etatboutonDOWN == LOW) && (Data >= 1 && Data <= 6 ) ) {
    Data--;
  delay(100);
  }
  if (Data <= 1) {
    Data = 1;
  }
  else
  {
    Data = Data;
  }

  etatboutonUP = boutonUPappui ;
  etatboutonDOWN = boutonDOWNappui ;

  if (oldData != Data) {
    Serial.print(" Data : ");
    Serial.println(Data);

    if (Data == 1) {
      menu1();
    }
    else if (Data == 2) {
      menu2();
    }
  }
  else
  {
    oldData = Data ;
  }
}
// Menus pour chaque relais/antenne

void menu1()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(TRX1);
  lcd.setCursor(0, 1);
  lcd.print(description1);
  resetrelay();
  digitalWrite(relay1, LOW);
}

void menu2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(TRX2);
  lcd.setCursor(0, 1);
  lcd.print(description2);
  resetrelay();
  digitalWrite(relay2, LOW);
}


void resetrelay()
{
    // initialise les relais à OFF

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

}
