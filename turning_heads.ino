#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servonum = 0;
long servo1rand;
long servo2rand;
long servo3rand;
long servo4rand;
int stareTime = 500;
const int pingPin = 7;
const int stare0 = 200;
const int stare1 = 200;
const int stare2 = 200;
const int stare3 = 200;

long checkProximity(int pingPin)
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  delay(100);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void setup()
{
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}

int currentPos0 = SERVOMIN;
int currentPos1 = SERVOMIN;
int currentPos2 = SERVOMIN;
int currentPos3 = SERVOMIN;
uint16_t speed0 = 2;
uint16_t speed1 = 4;
uint16_t speed2 = 6;
uint16_t speed3 = 8;

void loop() {
  long proximity = checkProximity(pingPin);

  if (proximity <= 30)
  {
    // set to stare
    pwm.setPWM(0, 0, stare0);
    pwm.setPWM(1, 0, stare1);
    pwm.setPWM(2, 0, stare2);
    pwm.setPWM(3, 0, stare3);
  }
  else {
    if (currentPos0 + speed0 > SERVOMAX || currentPos0 + speed0 < SERVOMIN)
    {
      speed0 *= -1;
    }
    if (currentPos1 + speed1 > SERVOMAX || currentPos1 + speed1 < SERVOMIN)
    {
      speed1 *= -1;
    }
    if (currentPos2 + speed2 > SERVOMAX || currentPos2 + speed2 < SERVOMIN)
    {
      speed2 *= -1;
    }
    if (currentPos3 + speed3 > SERVOMAX || currentPos3 + speed3 < SERVOMIN)
    {
      speed3 *= -1;
    }

    if (currentPos0 - currentPos1 < 40)
    {
      currentPos0 = 0;
      currentPos1 = 0;
    }

    currentPos0 += speed0;
    currentPos1 += speed1;
    currentPos2 += speed2;
    currentPos3 += speed3;
    pwm.setPWM(0, 0, currentPos0);
    pwm.setPWM(1, 0, currentPos1);
    pwm.setPWM(2, 0, currentPos2);
    pwm.setPWM(3, 0, currentPos3);
    delay(5);
  }

}
