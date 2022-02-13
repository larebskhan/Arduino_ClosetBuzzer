#include <LiquidCrystal.h>

/*GLOBAL VARIABLES*/

//Buzzer Pin Definitions
#define trigPin 9
#define echoPin 8
#define buzzer1 10
long duration; // variable for the duration of sound wave travel
int sensDistance; // variable for the distance measurement

//LCD Pin Definitons
int reg0 = 3;
int reg1 = 11;
int reg2 = 12;
int reg3 = 13;
int en = 7;
int rs = 6;
int contPin = 5;
int contVal = 80;

//Create LCD object
LiquidCrystal lcd(rs, en, reg0, reg1, reg2, reg3);

void setup() {
  // Buzzer Setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer1, OUTPUT); //Sets buzzer1 as an OUTPUT
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed

  // LCD Setup
  analogWrite(contPin, contVal);
  lcd.begin(16,2);
}
void loop() {
  sensDistance = sensorDistance();
  
  //clear lcd
  lcd.clear();

  if(sensDistance < 25)
  {
    tone(buzzer1, 1800);
    delay(100);
    lcd.print("ENOUGH!");
    noTone(buzzer1);
    delay(100);
  }
  else if(sensDistance < 50)
  {
    tone(buzzer1, 1800);
    delay(250);
    lcd.print("STOP!");
    noTone(buzzer1);
    delay(250);
  }
  else if(sensDistance < 100)
  {
    tone(buzzer1, 1800);
    delay(500);
    lcd.print("GO AWAY PLEASE!");
    noTone(buzzer1);
    delay(500);
  }
}

int sensorDistance()
{
  int distance = -1;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds to tell the echo pin to gather data
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  long actualTime = duration/2;
  
  // Calculating the distance
  float speedSound = 0.034; //cm/us
  distance = actualTime * speedSound; // Speed of sound wave divided by 2 (go and back)
  
  return distance;
}
