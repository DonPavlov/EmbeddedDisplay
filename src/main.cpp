/******************************************************************************/
/* Paul Hein                                                                  */
/*                                                                            */
/* 3.3.2017                                                                   */
/* Pro Micro Test Code for i2c-Bus, 16x2 Display, and more                    */
/*                                                                            */
/******************************************************************************/
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* SDA Pin 2, SCL Pin 3 */
#define DS1621 0b1001000

/*
* The circuit:
* LCD RS pin to digital pin 9
* LCD Enable pin to digital pin 8
* LCD D4 pin to digital pin 7
* LCD D5 pin to digital pin 6
* LCD D6 pin to digital pin 5
* LCD D7 pin to digital pin 4
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3) (poti middlepin)
* Anode to 200 Ohm to ground
* Kathode to +5V
* VSS to ground
* VDD to +5V
* RW to ground
*/
LiquidCrystal lcd(9, 8, 4, 5, 6, 7);

char meh[100];

void setup()
{
 lcd.begin(16, 2);
 Serial.begin(9600);
 Wire.begin();
 Wire.beginTransmission(DS1621);
 Wire.write((uint8_t) 0xA);
 Wire.write((uint8_t) 0xC);       // 0xAC = Config Command senden
 Wire.write((uint8_t) 0x0);
 Wire.write((uint8_t) 0x2);       // Commando ist: Continous Conversion
 Wire.beginTransmission(DS1621);  // restart
 Wire.write((uint8_t) 0xE);
 Wire.write((uint8_t) 0xE);       // start conversions
 Wire.endTransmission();
 // write 0xAC should also work
 }

void loop()
{
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}
