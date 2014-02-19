 //==========================================================
// line_follower.pde
// Author: Austin Duff - June 24, 2009
// Code adapted by: benwoodrobotics - 2012
// ==========================================================

#include <Servo.h> 

// Car configuration:
Servo benwoodServo; 
#define left 3 
#define right 4
#define motor 5 

int mid = 0;
int mn = 0;
int mx = 0;

int startTime;
int ellapsedTime;

int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;

int FWD = 85;
int EX = 92;
int SHP = 60;
int FWDW = 75;
int BACKW = 53;
int MIL = 230;


void setup()
{
  benwoodServo.attach(6); 
  benwoodServo.write(97);
  
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(motor, OUTPUT);

  analogWrite(motor, 0);
  
  for(int i=0; i<5000; i++)
  {
    int val = 0;
    for(int j=0; j<=5; j++)
    {
      val = analogRead(j);
      if(val >= mx)
          mx = val;
      if(val <= mn)
        mn = val;
    }
    delay(1);
  }
  
  mid = ((mx + mn)/2);
  
  // Serial.begin(9600);
}
void loop()
{
  Out:;
  
  s0 = 0;
  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;
  s5 = 0;

  s0 = analogRead(A0);
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4 = analogRead(A4);
  s5 = analogRead(A5);
    
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
  analogWrite(motor,FWD);
  
  if((((s0+s1+s2)/3)>(((s3+s4+s5)/3)+250))&&(!((s0 > mid)&&(s5 > mid))))
  {
    digitalWrite(left, HIGH);
    digitalWrite(right, LOW);
    analogWrite(motor,SHP);
  }
  if((((s0+s1+s2)/3)<(((s3+s4+s5)/3)-250))&&(!((s0 > mid)&&(s5 > mid))))
  {
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH);
    analogWrite(motor,SHP);
  }
  if((s0 > mid)&&(s5 > mid))
  {
    analogWrite(motor, 0);
  }
  if((s0 < mid)&&(s1 < mid)&&(s2 < mid)&&(s3 < mid)&&(s4 < mid)&&(s5 < mid))
  {
    digitalWrite(left, HIGH);
    digitalWrite(right, HIGH);
    analogWrite(motor,FWDW);
    startTime = 0;
    ellapsedTime = 0;
    startTime = millis();
    do 
    {
      ellapsedTime = millis() - startTime;
     }while(ellapsedTime < MIL);

    if((s0 > mid)||(s1 > mid)||(s2 > mid)||(s3 > mid)||(s4 > mid)||(s5 > mid))
    {
      goto Out;
    }
    Start:;
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
    analogWrite(motor,BACKW);
    s0 = analogRead(A0);
    s1 = analogRead(A1);
    s2 = analogRead(A2);
    s3 = analogRead(A3);
    s4 = analogRead(A4);
    s5 = analogRead(A5);
    if((s0 < mid)&&(s1 < mid)&&(s2 < mid)&&(s3 < mid)&&(s4 < mid)&&(s5 < mid))
    {
      goto Start;
    }
    goto Out;
  }
  if((s0 < mid)&&(s1 < mid)&&(s2 < mid)&&(s3 < mid)&&(s4 < mid)&&(s5 > mid))
  {
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH);
    analogWrite(motor,EX);
  }
  if((s0 > mid)&&(s1 < mid)&&(s2 < mid)&&(s3 < mid)&&(s4 < mid)&&(s5 < mid))
  {
    digitalWrite(left, HIGH);
    digitalWrite(right, LOW);
    analogWrite(motor,EX);
  }
}

