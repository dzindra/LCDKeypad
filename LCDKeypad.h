/*

  LCDKeypad Arduino library
  https://github.com/dzindra/LCDKeypad
  
  written by Jindrich Dolezy (jindrich@dolezy.cz)
  based on the code by fj604 from http://forum.arduino.cc/index.php?topic=38061.0


  some lcd boards have issue with backlight frying output pins
  see http://forum.arduino.cc//index.php?topic=96747 for discussion and solutions
  this code uses universal solution with pin input/output toggling, so it should be
  safe on all types of this board

*/

#ifndef LCDKeypad_h
#define LCDKeypad_h

#include <inttypes.h>


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

class LCDKeypad : public LiquidCrystal
{
  public:
    LCDKeypad();
    LCDKeypad(uint8_t bl_pin, uint8_t button_apin);

    void keypadInit(uint8_t bl_pin, uint8_t button_apin);
    
    uint8_t button();

    // use this method for menus and other things where repeated and filtered keypresses are needed
    uint8_t buttonBlocking(uint16_t block_delay = 500, uint16_t repeat_delay = 300);

    void backlight();
    void noBacklight();

  private:
  	uint8_t _bl_pin;
  	uint8_t _button_pin;

    unsigned long _block_time;
    uint8_t _last_button;

};

#endif

