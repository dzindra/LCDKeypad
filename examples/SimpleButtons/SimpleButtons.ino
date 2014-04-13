/*

  LCDKeypad Arduino library
  https://github.com/dzindra/LCDKeypad
  
  written by Jindrich Dolezy (jindrich@dolezy.cz)
  based on the code by fj604 from http://forum.arduino.cc/index.php?topic=38061.0

*/

#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LCDKeypad lcd;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  
  lcd.print("LCDKeypad basics");
  
  delay(2000);
  lcd.clear();
  lcd.print("Button:");
}

void loop() {
  lcd.setCursor(8,0);
  
  switch (lcd.button()) {
    case KEYPAD_LEFT:
      lcd.print("LEFT  ");
      break;
    case KEYPAD_RIGHT:
      lcd.print("RIGHT ");
      break;
    case KEYPAD_DOWN:
      lcd.print("DOWN  ");
      break;
    case KEYPAD_UP:
      lcd.print("UP    ");
      break;
    case KEYPAD_SELECT:
      lcd.print("SELECT");
      break;
    default:
      lcd.print("NONE  ");
      break;
  }

  delay(100);
}
