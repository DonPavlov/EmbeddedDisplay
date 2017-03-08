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
  /* Switch on the backlight */
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);

  Serial.begin(9600);
  delay(5000); /* Security Delay to Start everything */
  Serial.println("Began Serial");
  lcd.begin(16,2);
  Serial.println("Began LCD");
  Wire.begin();
  Serial.println("Began Wire");

  /* Quick 3 blinks of backlight */
  for(int i = 0; i< 3; i++){
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
  /* Init the DS1621 */
  Wire.beginTransmission(DS1621);
  Wire.write(0xAC);                /* Send commando */
  Serial.println("Init Kommando");

  Wire.write(0x02);                /* Commando ist: Continous Conversion */
  Serial.println("0x02 send");
  Wire.beginTransmission(DS1621);  /* restart */

  Wire.write(0xEE);       /* start conversions */
  Serial.println("Start Conversion");

  Wire.endTransmission();

}

void loop()
{
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

  delay(1000);    // give time for measurement

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
}
