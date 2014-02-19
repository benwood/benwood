//==========================================================
// Mario_Kart.pde
// Author: 
// Code adapted by: benwoodrobotics - 2012
// ==========================================================

#include <WiShield.h>
#include <Servo.h>

#define WIRELESS_MODE_INFRA   1
// #define WIRELESS_MODE_ADHOC   2

// Car configuration:
Servo benwoodServo;
#define left 3 
#define right 4
#define motor 5

// Wireless configuration parameters ----------------------------------------
byte local_ip[]    = {10,0,1,220};   // IP address of WiShield
byte gateway_ip[]  = {10,0,1,1};   // router or gateway IP address
byte subnet_mask[] = {255,255,255,0};   // subnet mask for the local network
prog_char ssid[] PROGMEM    = {"bibi"};      // max 32 bytes
unsigned char security_type = 0;   // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {};

// WEP 128-bit keys
prog_uchar wep_keys[] PROGMEM = {   
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,   // Key 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00,   // Key 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00,   // Key 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00   // Key 3
};
// setup the wireless mode
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
//---------------------------------------------------------------------------

//Client and server parameters
Server server(9000);
Client client;
char val[1];
unsigned long last_serial;


void setup()
{
  // Serial.begin(115200);
  benwoodServo.attach(6);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(motor, OUTPUT);
  WiFi.begin(local_ip, gateway_ip, subnet_mask);
  server.begin();
  // Serial.begin(115200);
  analogWrite(motor, 100); 
}

void loop()
{
  if(!client.connected()) 
  {
     server.available(&client);
  } 
  else 
  {
    while(client.available()) 
    {
      byte c = (byte)client.read();
      unsigned int cTest = map(c, 0, 255, 0, 255);
      if(cTest >= 200 && cTest <= 210)
      {
        delay(1);
        analogWrite(5, 0);
      }
      if(cTest <= 100)
      {
        delay(1);      
        benwoodServo.write(map(cTest,0,100,153,43));
      }
      //if(cTest == 100)
      //  //soulever le poid //digitalWrite( //HIGH
      //if(cTest == 101) 
      //  //relacher le poids //digitalWrite( //LOW
      //if(cTest > 101 && cTest < 155)
      //  // faire bouger le bras avec le servo //Servo.write(map(cTest,102,154,//?,//?));
      //
      if(cTest >=155 && cTest<205)
      {
        delay(1);
        digitalWrite(left, HIGH);
        digitalWrite(right, HIGH);
        analogWrite(motor, map(cTest,155,205,255,60));
      }
      if(cTest > 210)
      {
        delay(1);
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
        analogWrite(motor, map(cTest,211,255,60,255));
      }
    } 
  }
}
