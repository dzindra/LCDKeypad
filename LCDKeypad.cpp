/*

  LCDKeypad Arduino library
  https://github.com/dzindra/LCDKeypad
  
  written by Jindrich Dolezy (jindrich@dolezy.cz)
  based on the code by fj604 from http://forum.arduino.cc/index.php?topic=38061.0

*/

#include <Arduino.h>
#include <LiquidCrystal.h>
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
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return KEYPAD_NONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return KEYPAD_RIGHT; 
  if (adc_key_in < 195)  return KEYPAD_UP;
  if (adc_key_in < 380)  return KEYPAD_DOWN;
  if (adc_key_in < 555)  return KEYPAD_LEFT;
  if (adc_key_in < 790)  return KEYPAD_SELECT;  
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
