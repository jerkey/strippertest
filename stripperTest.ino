int inByte = 0;         // incoming serial byte
#define STEPPIN 11     
#define DIRPIN 12      
int dir = 0;
int steps = 200;  // 1000 steps = 63mm of wire
int delayTime = 10;
#define FWD HIGH // which way is DIR wired?
#define BACK LOW
#define OPEN 50 // position of stripper servo
#define CLOSE 170
#define CHOPCLOSED 170
#define CHOPOPEN 40
#define STRIPPIN 9 // what pin is it on
#define CHOPPIN 10

#include <Servo.h> 
Servo chopServo;  // create servo object to control a servo 
Servo stripServo;  // create servo object to control a servo 

void setup() {
  pinMode(STEPPIN, OUTPUT);      
  pinMode(DIRPIN, OUTPUT);
  pinMode(CHOPPIN,OUTPUT);
  chopServo.attach(CHOPPIN);
  pinMode(STRIPPIN,OUTPUT);
  stripServo.attach(STRIPPIN);
  Serial.begin(9600);
  Serial.println("hello");
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    switch (inByte) {
    case 'f':
      Serial.println("forward 100");
      stepper(FWD,100);
      break;
    case 'b':
      Serial.println("back 50");
      stepper(BACK,50);
      break;
    case 'o':
      Serial.println("open");
      stripper(OPEN);
      break;
    case 'c':
      Serial.println("close");
      stripper(CLOSE);
      break;
    case 'x':
      Serial.println("xchop!");
      chop();
      break;
    }
  }
}

void stepper(boolean dir, unsigned int distance) {
  digitalWrite(DIRPIN, dir);
  for(int i=0; i <distance ;  i++){
    digitalWrite(STEPPIN, HIGH);
    delay(5);
    digitalWrite(STEPPIN, LOW);
    delay(delayTime);
  }
}

void stripper(int angle) {
  stripServo.write(angle);              // tell servo to go to position in variable 'angle'
  delay(750);                       // waits one second for the servo to reach the position 
}

void chop() {
  chopServo.write(CHOPCLOSED);
  delay(500);
  chopServo.write(CHOPOPEN);
  delay(500);
}
