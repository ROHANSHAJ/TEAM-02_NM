#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial Gsm(6, 7);
String phone_no = "+917904915518";
TinyGPS gps;
int state;
String textMessage;

void setup() {
  Serial.begin(9600);
  Gsm.begin(9600);
  Serial.print("AT+CMGF=1\r");
  delay(100);
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  pinMode(10, INPUT);
}

void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis();
       millis() - start < 1000;) {
    while (Serial.available()) {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c))
        newData = true;
    }
  }
  if (Gsm.available() > 0) {
    textMessage = Gsm.readString();
    textMessage.toUpperCase();
    delay(10);
  }
 /* //Prateek
  //www.justdoelectronics.com
  Serial.println(failed);
}*/
state = digitalRead(10);
Serial.print(state);
if (state == 1)
//Prateek
//www.justdoelectronics.com

{
  //float flat, flon;
  //unsigned long age;
  //gps.f_get_position(&flat, &flon, &age);
  Gsm.println("AT+CMGF=1");
  //Gsm.print("AT+CMGS=\"");
  Gsm.println("AT+CMGS=\"+917904915518\"\r");
  Gsm.println(phone_no);
  Gsm.println("\"");
  Gsm.println("Alert I need help.............");
  Gsm.print("http://maps.google.com/maps?q=loc:");
  //Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Gsm.print(",");
  //Gsm.print(flon == TinyGPS ::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  delay(2000);
  Gsm.println((char)26);
  //Prateek
  //www.justdoelectronics.com

  delay(200);
  Gsm.println();

  Serial.println("SMS Sent");

  Serial.println("Call");
  delay(20000);
  Gsm.println("ATD+917904915518;");
  delay(15000);
  Gsm.println("ATH");
  delay(1000);

} else {
  delay(10);
}
}