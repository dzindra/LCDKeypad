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
  
  lcd.print("LCDKeypad");
  lcd.setCursor(0,1);
  lcd.print("Blocking buttons");
  
  delay(2000);
  lcd.clear();
  lcd.print("Counter:");
}

static int counter = 0;

void loop() {
  // use buttonBlocking in menus or other cases
  // when you need repeated and debounced key presses
  // key direction will be returned once only for each blocking period (default 500ms)
  
  switch (lcd.buttonBlocking()) {
    case KEYPAD_LEFT:
      counter -= 10;
      break;
    case KEYPAD_RIGHT:
      counter += 10;
      break;
    case KEYPAD_DOWN:
      counter += 1;
      break;
    case KEYPAD_UP:
      counter -= 1;
      break;
    case KEYPAD_SELECT:
      counter = 0;
      break;
  }

  lcd.setCursor(9,0);  
  lcd.print(counter);
  lcd.print("   ");
}
