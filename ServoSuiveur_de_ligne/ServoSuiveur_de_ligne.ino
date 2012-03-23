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
    extremeGauche = A0, val_EG,
    MaxValeur,
    MinValeur,
    ValeurNoire,
    ValeurBlanche,
    servo;

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
  
  ValeurNoire=(analogRead(centreDroite)+analogRead(centreGauche))/2;
  MaxValeur=ValeurNoire;
  ValeurBlanche=(analogRead(droite)+analogRead(gauche))/2;
  MinValeur=ValeurBlanche;
  
  Serial.begin(9600);
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
void loop()
{
//  int val_ED = analogRead(extremeDroite);
//  int val_D = analogRead(droite);
  int val_CD = analogRead(centreDroite);
  int val_CG = analogRead(centreGauche);
//  int val_G = analogRead(gauche);
//  int val_EG = analogRead(extremeGauche);
  
  ValeurNoire=(analogRead(centreDroite)+analogRead(centreGauche))/2;  
  ValeurBlanche=(analogRead(droite)+analogRead(gauche))/2;
    
     if(MinValeur>ValeurBlanche)
       {
         MinValeur=ValeurBlanche;
       }
       
    if(MaxValeur<ValeurNoire)
      {
        MaxValeur=ValeurNoire;
      }
   
   
//  Serial.print("ED = "); Serial.print(val_ED);
//  Serial.print("D = "); Serial.print(val_D);
//  Serial.print("CD = "); Serial.print(val_CD);
//  Serial.print("CG = "); Serial.print(val_CG);
//  Serial.print("G = "); Serial.print(val_G);
//  Serial.print("EG = "); Serial.println(val_EG);

   Serial.print("Lecture du MaxValeur");
   Serial.print(MaxValeur);
   Serial.print("  ");
   Serial.print("Lecture du MinValeur");
   Serial.println(MinValeur);
   
   if(ValeurNoire > MaxValeur-50)
     {
       servo = map(ValeurNoire, MaxValeur-50, MaxValeur, 85, 95);//attention kevin, la nom de variable servo n'est pas recommande
       benwoodServo.write(servo);
      delay(150); 
     }
     
     
}
