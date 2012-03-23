#include <Servo.h>

Servo myservo; 

int extremeDroite = A5,
    droite = A4,
    centreDroite = A3,
    centreGauche = A2,
    gauche = A1,
    extremeGauche = A0 ,
    MaxValeur,
    MinValeur,
    ValeurNoire,
    ValeurBlanche,
    servo;


void setup()
{
  pinMode(extremeDroite , INPUT);
  pinMode(droite, INPUT);
  pinMode(centreDroite, INPUT);
  pinMode(centreGauche, INPUT);
  pinMode(gauche, INPUT);
  pinMode(extremeGauche, INPUT);
  
  myservo.attach(10);
  
  ValeurNoire=(analogRead(centreDroite)+analogRead(centreGauche))/2;
  MaxValeur=ValeurNoire;
  ValeurBlanche=(analogRead(droite)+analogRead(gauche))/2;
  MinValeur=ValeurBlanche;
  
  Serial.begin(9600);
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
       myservo.write(servo);
      delay(150); 
     }
     
     
}
