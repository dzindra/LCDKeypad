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

#include <Arduino.h>
#include "LCDKeypad.h"


LCDKeypad::LCDKeypad() : LiquidCrystal(KEYPAD_LCD_PINS)
{
  keypadInit(KEYPAD_BACKLIGHT_PIN, KEYPAD_BUTTON_ANALOG_PIN);
}

LCDKeypad::LCDKeypad(uint8_t bl_pin, uint8_t button_apin) : LiquidCrystal(KEYPAD_LCD_PINS)
{
  keypadInit(bl_pin,button_apin);
}

void LCDKeypad::keypadInit(uint8_t bl_pin, uint8_t button_apin)
{
  _bl_pin = bl_pin;
  _button_pin = button_apin;
  _block_time = 0;
  _last_button = KEYPAD_NONE;
  
  // set button pin as input
  pinMode(_button_pin, INPUT);

  // turn on backlight properly just to be sure we are not frying outputs
  backlight();
}

void LCDKeypad::backlight()
{
  // always try to keep the pin low
  digitalWrite(_bl_pin, LOW);
  pinMode(_bl_pin, INPUT);
}

void LCDKeypad::noBacklight()
{
  // always try to keep the pin low
  digitalWrite(_bl_pin, LOW);
  pinMode(_bl_pin, OUTPUT);
}

uint8_t LCDKeypad::button()
{
  // read the value from the sensor
  int adc_key_in = analogRead(_button_pin);
  
  if (adc_key_in > KEYPAD_TRESHOLD_NONE) return KEYPAD_NONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < KEYPAD_TRESHOLD_RIGHT)   return KEYPAD_RIGHT; // 0 on my board
  if (adc_key_in < KEYPAD_TRESHOLD_UP)  return KEYPAD_UP; // 133 on my board
  if (adc_key_in < KEYPAD_TRESHOLD_DOWN)  return KEYPAD_DOWN; // 308 on my board
  if (adc_key_in < KEYPAD_TRESHOLD_LEFT)  return KEYPAD_LEFT; // 480 on my board
  if (adc_key_in < KEYPAD_TRESHOLD_SELECT)  return KEYPAD_SELECT;  // 721 on my board
  return KEYPAD_NONE;  // when all others fail, return this...
}

uint8_t LCDKeypad::buttonBlocking(uint16_t block_delay, uint16_t repeat_delay)
{
  // if we are still blocked, return this status
  if (millis() < _block_time)
    return KEYPAD_BLOCKED;

  uint8_t current = button();

  // if some key is pressed, disable presses for block_delay or repeat_delay if button is kept down
  if (current != KEYPAD_NONE)
    _block_time = millis() + (current == _last_button ? repeat_delay : block_delay);

  _last_button = current;
  return current;
}
