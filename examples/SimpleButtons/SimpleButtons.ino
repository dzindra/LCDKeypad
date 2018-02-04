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

  lcd.setCursor(0,1);
  lcd.print("ADC lvl: ");
  lcd.print(analogRead(0));
  lcd.print("   ");

  delay(100);
}
