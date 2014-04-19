/*

  LCDKeypad Arduino library
  https://github.com/dzindra/LCDKeypad
  
  Copyright 2014 Jindřich Doležy (jindrich@dolezy.cz)
  based on the code by fj604 from http://forum.arduino.cc/index.php?topic=38061.0


  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
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
