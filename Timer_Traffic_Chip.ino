//Code for prototype B of the Traffic Light with countdown timer.
//The idea is to read the pulse transferring from the output of IC4017 to the light
//If the pulse is HIGH, meaning that the light is turned on, the countdown timer
//starts counting. If there is a new pulse to another light, 
//then reset the current countdown timer back to its initial value, i.e green = red = 6 seconds, yellow = 3 seconds.
//To reduce incompatible counting and unstable receiving pulses due to the values of electrical components,
//we check the pulses by each 200 miliseconds to make sure that the clock is counting correctly according
//to the light pulse.
#include <LiquidCrystal_I2C.h>

const int green1_pin=8;
const int green2_pin=9;
const int yellow_pin=10;
const int red1_pin=11;
const int red2_pin=12;
//constant values of light duration (adjusted to reduce incompatible counting)
const int green = 6140;
const int yellow = 3070;
const int red = 6140;
const int check = 200;
int time_green = green;
int time_yellow = yellow;
int time_red = red;
int current_pin = 0;
int time_on_clock = 0;
unsigned long next_time = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);




void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  //initialize the pulse at the lights to be the input for the clock
  pinMode(green1_pin, INPUT);
  pinMode(green2_pin, INPUT);
  pinMode(yellow_pin, INPUT);
  pinMode(red1_pin, INPUT);
  pinMode(red2_pin, INPUT);

}

void loop() {
  //check clock pulse to prevent incorrect counting value and overlapped counting due to unstable pulses of lights.
  if (next_time - millis() >= check) {
    next_time = millis() + check;
    //if green light is turned on and there was a pulse transfer from a different color light to green light,
    //assign the counting varible with 6 seconds, and countdown after every 200 miliseconds.
    if (digitalRead(green1_pin)==HIGH){
      if (current_pin != green1_pin) {
        time_green = green;
        current_pin = green1_pin;
      }
      time_on_clock = time_green;
      time_green -= check;
    }
    //Since there are 2 diodes of green lights and the first one is already recognized to turn on, there is no need to reassign the
    //clock value; the next pin only needs to continue counting backwards to 1.
    if (digitalRead(green2_pin)==HIGH){
      time_on_clock = time_green;
      time_green -= check;
    }
    //Similar to how green light is depicted 
    if (digitalRead(yellow_pin)==HIGH){
      if (current_pin != yellow_pin) {
        time_yellow = yellow;
        current_pin = yellow_pin;
      }
      time_on_clock = time_yellow;
      time_yellow -= check;
    }
    //Red light
    if (digitalRead(red1_pin)==HIGH){
      if (current_pin != red1_pin) {
        time_red = red;
        current_pin = red1_pin;
      }
      time_on_clock = time_red;
      time_red -= check;
    }
    if (digitalRead(red2_pin)==HIGH){
      time_on_clock = time_red;
      time_red -= check;
    }
    //Print the counting value to the LCD screen. Because the value is in miliseconds, divide by 1000 to get
    //the second value. The +1 is for preventing unstable counting due to unstable pulse.
    lcd.clear();
    lcd.print(time_on_clock/1000+1);
  }
}
