const int trigger = 9; //Assign trig pin of ultrasound sensor
const int echo = 8; //Assign echo pin of ultrasound sensor
const int Red = 11; //Assign R pin of RGB LED
const int Green = 12; //Assign G pin of RGB LED
#include <LiquidCrystal.h> //Import the LCD(Liquid Crystal Display) library
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Create an instance of the LiquidCrystal class and set the pins that RS, E & DB4-7 are in as parameters
int duration, cm; //Declare the object's duration from sensor and the cm conversion variables 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Accept 9600 bytes of data to display in the serial moniter for validation
  pinMode(trigger, OUTPUT); //Set the trigger pin as an output pin
  pinMode(echo, INPUT); //Set the echo pin as an input pin
  pinMode(Red, OUTPUT); //Set the R pin as an output pin
  pinMode(Green, OUTPUT); //Set the G pin as an output pin
  lcd.begin(16, 2); //Use 16 columns and 2 rows of the LCD display
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigger, LOW); //Turn off the trigger pin
  delay(0.005); //delay for 5 micro seconds
  
  digitalWrite(trigger, HIGH); //Turn on the trigger pin
  delay(0.01); //delay for 10 micro seconds
  
  digitalWrite(trigger, LOW); //Turn off the trigger pin again

  duration = pulseIn(echo, HIGH); //use the pulseIn method to return a value to the duration variable
  
  cm = (duration/2)/29.1; //Convert to cm, divide by 2 since we're not counting the return trip
  
  if(cm < 100) //Create an if-else statement for different ranges, when the object is < 1m away from the sensor, turn on the R pin exclusively
  {
    digitalWrite(Green, LOW);
    digitalWrite(Red, HIGH);
  }
  else if(cm >= 100 && cm <= 200) //When the object is >= 1m & <= 2m away from the sensor, turn on both the R & G pins
  {
    digitalWrite(Red, HIGH);
    digitalWrite(Green, HIGH);
  }
  else //When the object is > 2m away from the sensor, turn on the G pin exclusively
  {
    digitalWrite(Red, LOW);
    digitalWrite(Green, HIGH);
  }

  lcd.setCursor(0, 1); //Use the setCursor method to have the LCD put in the messages in the 1st and 2nd rows

  lcd.clear(); //Clear away prior messages
  lcd.print(cm); //Print the distance
  lcd.print(" cm");

  Serial.print(cm); //Print the same message to the serial monitor
  Serial.print(" cm");
  Serial.println();

  delay(250); //Delay the loop by 250 milliseconds
}
