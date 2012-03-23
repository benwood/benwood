//----Initialisation du servo----
#include <Servo.h> 
Servo benwoodServo;
//----Initialisation des pins moteurs----
int fowardWheel = 2;
int backwardWheel = 3;
int motor = 6;
//----Initialisation des sensors + valeurs----
int extremeDroite = A5, val_ED,
    droite = A4, val_D,
    centreDroite = A3, val_CD,
    centreGauche = A2, val_CG,
    gauche = A1, val_G,
    extremeGauche = A0, val_EG;
//----------------------------------
void setup()
{ 
  //----servo----
  benwoodServo.attach(10);
  benwoodServo.write(90);
  //----motor----
  pinMode(fowardWheel, OUTPUT);
  pinMode(backwardWheel, OUTPUT);
  pinMode(motor, OUTPUT);
  //----sensors----
  pinMode(extremeDroite , INPUT);
  pinMode(droite, INPUT);
  pinMode(centreDroite, INPUT);
  pinMode(centreGauche, INPUT);
  pinMode(gauche, INPUT);
  pinMode(extremeGauche, INPUT);
}
//----------------------------------
void foward() //avant
{  
  digitalWrite(fowardWheel, HIGH);
  digitalWrite(backwardWheel, LOW);
  return;
}
void backward() //arriere
{
  digitalWrite(backwardWheel, HIGH);
  digitalWrite(fowardWheel, LOW);
  return;
}
void sensorRead() //lecture des sensors
{
  val_ED = analogRead(extremeDroite);
  val_D = analogRead(droite);
  val_CD = analogRead(centreDroite);
  val_CG = analogRead(centreGauche);
  val_G = analogRead(gauche);
  val_EG = analogRead(extremeGauche);
  return;
}
//-------------------------------Code above should never change----------------------------
void loop()
{
  //----lecture des sensors----
  sensorRead();
  if (val_ED < 400 && val_EG < 400 && (val_D > 400 || val_CD > 400 || val_CG > 400 || val_G > 400))
  {
    foward();
    analogWrite(motor, 100); 
    benwoodServo.write(90);
  }
  if (val_CD < 400 || val_CG < 400)
  {
    backward();
    do
    {
      analogWrite(motor, 100);
      sensorRead();
    }while(val_ED > 400 && val_EG > 400 && (val_D < 400 || val_CD < 400 || val_CG < 400 || val_G < 400));
  }
}
