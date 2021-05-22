//Code for prototype A of the Traffic Light with countdown timer
//In this prototype,Arduino controls both the lights and the countdown
#include <LiquidCrystal_I2C.h>

const int green_pin=8;
const int yellow_pin=9;
const int red_pin=10;
//constant value of light duration
const int green_delay=9000;
const int yellow_delay=4000;
const int red_delay=9000;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void green()
//countdown from 9. For each iteration, make the pulse for green light HIGH
//to turn it on, and make LOW pulses for the other lights to keep them turn off.
//Then print the iteration value to get the countdown value
{
  for(int time1=9;time1>0;time1--)
  {
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, LOW);  
    lcd.print(time1);
    delay(1000);
    lcd.clear();
  }
}
void yellow()
{  
  for(int time2=4;time2>0;time2--)
  {
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, HIGH);
    digitalWrite(red_pin, LOW);  
    lcd.print(time2);
    delay(1000);
    lcd.clear();
  }
}
void red()
{
  for(int time3=9;time3>0;time3--)
  {
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, HIGH);  
    lcd.print(time3);
    delay(1000);
    lcd.clear();
   }
}
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  //Initialize the lights as outputs of the code
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
}
void loop()
{
  green();
  yellow();
  red(); 
}
