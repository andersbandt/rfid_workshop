/*
Code for a workshop on RFID technology given by Anders Bandt
This code turns a servo when the correct RFID card is read
*/
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SERVO_PIN 3
Servo myservo;  // create servo object to control a servo
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Arduino RFID lock");
  Serial.println("");

  myservo.attach(SERVO_PIN);
  myservo.write( 0 );

}

void loop(){
  //Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent() ){
    return;
  }
  //Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  String content= "";
  byte letter;
  for( byte i = 0; i < mfrc522.uid.size; i++ ){
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     if( i < mfrc522.uid.size-1 ) content+="-";
  }
  content.toUpperCase();
  Serial.println();
  Serial.println("UID tag :'" + content + "'");

  if( content == "XX-XX-XX-XX" ){                  // PLACE YOUR UID HERE
    Serial.println("Authorized access");
    myservo.write( 90 );

 
    
    delay(1000);
    myservo.write( 0 );

  }else{
    Serial.println("Access denied");
   
  }
  
  delay(1000);
} 
