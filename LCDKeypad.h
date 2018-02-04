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

#ifndef LCDKeypad_h
#define LCDKeypad_h

#include <inttypes.h>
#include <LiquidCrystal.h>


#define KEYPAD_NONE 0
#define KEYPAD_RIGHT 1
#define KEYPAD_UP 2
#define KEYPAD_DOWN 3
#define KEYPAD_LEFT 4
#define KEYPAD_SELECT 5
#define KEYPAD_BLOCKED 255

#define KEYPAD_BUTTON_ANALOG_PIN 0
#define KEYPAD_BACKLIGHT_PIN 10
#define KEYPAD_LCD_PINS 8, 9, 4, 5, 6, 7

// you can change tresholds for detecting key presses
#define KEYPAD_TRESHOLD_NONE 1000
#define KEYPAD_TRESHOLD_RIGHT 50
#define KEYPAD_TRESHOLD_DOWN 380
#define KEYPAD_TRESHOLD_UP 195
#define KEYPAD_TRESHOLD_LEFT 555
#define KEYPAD_TRESHOLD_SELECT 790

class LCDKeypad : public LiquidCrystal
{
  public:
    LCDKeypad();
    LCDKeypad(uint8_t bl_pin, uint8_t button_apin);

    void keypadInit(uint8_t bl_pin, uint8_t button_apin);
    
    uint8_t button();

    // use this method for menus and other things where repeated and filtered keypresses are needed
    uint8_t buttonBlocking(uint16_t block_delay = 500, uint16_t repeat_delay = 300);

    // some lcd boards have issue with backlight frying output pins
    // see http://forum.arduino.cc//index.php?topic=96747 for discussion and solutions
    // this code uses universal solution with pin input/output toggling, so it should be
    // safe on all types of this board
    void backlight();
    void noBacklight();

  private:
  	uint8_t _bl_pin;
  	uint8_t _button_pin;

    uint32_t _block_time;
    uint8_t _last_button;

};

#endif

