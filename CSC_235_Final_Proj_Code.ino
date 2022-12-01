//Servo vars
#include <Servo.h>
Servo myServo;
int servoPin = 9;
//int angle = 135;

//NeoPixel vars
#include <Adafruit_NeoPixel.h>
int npPin = 5;
Adafruit_NeoPixel strip(10, npPin);
uint32_t orange = strip.Color(254, 80, 0);
uint32_t cyan = strip.Color(0, 255, 255); 
uint32_t yellow = strip.Color(255, 255, 0);

//LED vars
int redPin = 10;
int bluePin = 11;
int yellowPin = 12;

//Joystick vars
int VRxPin = A5;
int VRyPin = A4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  myServo.attach(servoPin);
  //angle = 0;
  strip.clear();
  strip.begin();
  strip.show();
  
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);

  pinMode(VRxPin, INPUT);
  pinMode(VRyPin, INPUT);

//  myServo.write(angle);
}

void loop() {
  // put your main code here, to run repeatedly:
  LED(redPin);
  LED(bluePin);
  LED(yellowPin);
  
  analogRead(VRyPin);
  analogRead(VRxPin);
  //Serial.println(analogRead(VRyPin));
  Serial.println(analogRead(VRxPin));

  pivot(VRxPin, VRyPin);
  evolve(VRxPin, VRyPin, yellow, orange, cyan); 
}



void LED (int aPin) {
  digitalWrite(aPin, HIGH);
}


void pivot (int xPin, int yPin) {
  static int anAngle = 0;
  if (analogRead(yPin) > 900) {
    anAngle = 135; 
  }
  if (analogRead(yPin) < 50) {
    anAngle = 45; 
  }
  if (analogRead(xPin) < 50) {
    anAngle = 90; 
  }

  myServo.write(anAngle);
  //Serial.println(anAngle);
}

void evolve (int xPin, int yPin, uint32_t c1, uint32_t c2, uint32_t c3) {
  if (analogRead(yPin) > 900) {
    for (int i = 0; i <= strip.numPixels(); i++) { 
      strip.setPixelColor(i, c1);
    }
  }
  if (analogRead(yPin) < 50) {
    for (int i = 0; i <= strip.numPixels(); i++) { 
      strip.setPixelColor(i, c2);
    } 
  }
  if (analogRead(xPin) < 50) {
    for (int i = 0; i <= strip.numPixels(); i++) { 
      strip.setPixelColor(i, c3);
    } 
  }
  strip.show();
  
}
