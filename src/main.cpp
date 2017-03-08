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
 Serial.println("Init i2c");
 Wire.begin();
 Wire.beginTransmission(DS1621);
 Wire.write(0xAC);                // Send commando
 Serial.println("Init Kommando");

 Wire.write(0x02);                // Commando ist: Continous Conversion
 Serial.println("0x02 send");
 Wire.beginTransmission(DS1621);  // restart

 Wire.write(0xEE);       // start conversions
 Serial.println("Start Conversion");

 Wire.endTransmission();
 }

void loop()
{
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

  delay(1000);                                // give time for measurement

  Wire.beginTransmission(DS1621);
  Wire.write(0xAA);                            // read temperature command
  Wire.endTransmission();
  Wire.requestFrom(DS1621, 2);		// request two bytes from DS1621 (0.5 deg. resolution)

  firstByte = Wire.read();		        // get first byte
  secondByte = Wire.read();		// get second byte

  temp = firstByte;

  if (secondByte)			        // if there is a 0.5 deg difference
      temp += 0.5;

  Serial.println(temp);
  lcd.clear();
}
