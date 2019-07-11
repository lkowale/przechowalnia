#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Keypad.h>

// wejscie
#define ONE_WIRE_BUS A7

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27


const byte wiersze= 4; //ilość wierszy
const byte kolumny= 4; //ilość kolumn
//definicja klawiszy (identycznie jak na klawiaturze)
char mapaklawiszy[wiersze][kolumny]=
{
  {'1', '2', '3', '<'},
  {'4', '5', '6', '>'},
  {'7', '8', '9', 'C'},
  {'.', '0', '#', 'D'}
};

//byte wiersze_piny[wiersze] = {0,1,2,3}; // wiersze 0-3
//byte kolumny_piny[kolumny]= {4,5,6,7}; // kolumny 0-3

byte wiersze_piny[wiersze] = {37,35,33,31}; // wiersze 0-3
byte kolumny_piny[kolumny]= {29,27,25,23}; // kolumny 0-3

Keypad customKeypad= Keypad(makeKeymap(mapaklawiszy), wiersze_piny, kolumny_piny,
wiersze, kolumny);

String msg;



OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


