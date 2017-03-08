#include <Arduino.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

/* Display */
#define I2C_ADDR_DISP 0x27 /* Define I2C Address for controller */
#define EN_P 2
#define RW_P 1
#define RS_P 0
#define D4_P 4
#define D5_P 5
#define D6_P 6
#define D7_P 7
#define BACKLIGHT 3

/* DS1621 Temperature Chip */
#define DS1621 0b1001000 /* SDA Pin 2, SCL Pin 3 */

LiquidCrystal_I2C lcd(I2C_ADDR_DISP, EN_P, RW_P, RS_P, D4_P, D5_P, D6_P, D7_P);

void setup()
{
lcd.begin (20,4); // initialize the lcd

/* Switch on the backlight */
lcd.setBacklightPin(BACKLIGHT,POSITIVE);
lcd.setBacklight(HIGH);

Serial.begin(9600);
lcd.begin(16,2);

/* Quick 3 blinks of backlight */
for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }

  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("hello Master!");
  delay(1000);
  lcd.setCursor(1,1);
  lcd.print("I <3 YOU");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("16x2 Display");
  lcd.setCursor(0,1);

  delay(8000);
  // Wait and then tell user they can start the Serial Monitor and type in characters to
  // Display. (Set Serial Monitor option to "No Line Ending")
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Start Serial Monitor");
  lcd.setCursor(0,1);
  lcd.print("Type chars 2 display");

}

void loop()
{
  // when characters arrive over the serial port...
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
