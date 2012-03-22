#include <Servo.h> 
 
Servo benwoodServo;

int fowardWheel = 2;
int backwardWheel = 3;

int motor = 6; //test

void setup()
{ 
  pinMode(fowardWheel, OUTPUT);
  pinMode(backwardWheel, OUTPUT);

  benwoodServo.attach(10);
}
void foward()
{  
  digitalWrite(fowardWheel, HIGH);
  digitalWrite(backwardWheel, LOW);
  return;
}
void backward()
{
  digitalWrite(fowardWheel, LOW);
  digitalWrite(backwardWheel, HIGH);
  return;
}
void loop()
{
  foward();
  analogWrite(motor, 200); 
  benwoodServo.write(50);
  delay(1000);
  
  backward();
  analogWrite(motor, 200);
  benwoodServo.write(120);
  delay(1000);
}
