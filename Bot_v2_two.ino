//motor A connected between A01 and A02
//motor B connected between B01 and B02
// http://opensource.org/licenses/mit-license.php

#include <WiFly.h>
#include <SPI.h>

int STBY = 10; //standby
//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction
//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

int infoled = 13;

//char ssid[] = "Chua Family";
//char passphrase[] = "chua2680";
WiFlyServer server(44);

String readString = "";
String dir;

void setup(){
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  WiFly.setUart(&Serial);
  WiFly.begin(true);

//  if (!WiFly.join(ssid, passphrase)) {
  if (!WiFly.createAdHocNetwork("wifly")) {
    while (1) {
      // Hang on failure.
      digitalWrite(infoled, HIGH);
      delay(300);
      digitalWrite(infoled, LOW);
      delay(500);
    }
  }
  Serial.println(WiFly.ip());
  
  server.begin();
  
}

void loop() {
  WiFlyClient client = server.available();
  if (client) {
    digitalWrite(infoled, HIGH);
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
//        if (readString.length() < 100) {
//          readString += c;
//        }
        String d = (String) c;
        parseanddo(d);
//        client.println("LEEEEEEL: " + d);
      }
    }
    // give the web browser time to receive the data
//    delay(200);
    readString = "";
    client.stop();
    digitalWrite(infoled, LOW);
  }
}

void parseanddo(String incar) {
  if (incar == "g") {
    move(1, 220, 0);
    move(2, 140, 0);
  }
  else if (incar == "h") {
    move(1, 180, 1);
    move(2, 180, 1);
  }
  else {
    stop();
  }
}

//void blink() {
//  
//            digitalWrite(infoled, HIGH);
//            delay(300);
//            digitalWrite(infoled, LOW);
//            delay(500);
//            digitalWrite(infoled, HIGH);
//            delay(300);
//            digitalWrite(infoled, LOW);
//            delay(500);
//            digitalWrite(infoled, HIGH);
//            delay(300);
//            digitalWrite(infoled, LOW);
//            delay(500);
//            digitalWrite(infoled, HIGH);
//            delay(300);
//            digitalWrite(infoled, LOW);
//            delay(500);
//            digitalWrite(infoled, HIGH);
//            delay(300);
//            digitalWrite(infoled, LOW);
//            delay(500);
//            
//}

void move(int motor, int speed, int direction){
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
  //enable standby  
  digitalWrite(STBY, LOW); 
}

