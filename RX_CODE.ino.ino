#include <VirtualWire.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#define RX_PIN 11 // Pin connected to the RF receiver
const int LED_PIN =  3; 
const int LED_PIN1 =  5; 
const int LED_PIN12 =  6; 




void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(RX_PIN, INPUT); // Set the receiver pin as input
  vw_set_rx_pin(RX_PIN); // Set the RX pin for VirtualWire library
  vw_setup(2000); // Bits per second
  vw_rx_start(); // Start the receiver
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN12, OUTPUT);


}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Buffer to store received data
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Length of the buffer
  if (vw_get_message(buf, &buflen)) { // If a message is received
    int receivedData;
    memcpy(&receivedData, buf, sizeof(receivedData)); // Extract the data from the buffer
    Serial.println(receivedData); // Print the received data
    if(receivedData==1){
      Serial.println("high"); 
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(LED_PIN1, LOW);
      digitalWrite(LED_PIN12, LOW);


      text();
   
    }
    else{
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN1, HIGH);
    delay(600);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN12, HIGH);
    delay(600);
    digitalWrite(LED_PIN12, LOW);
     

    text11();
    


    }
  }
}

void text() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) ;
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Ambulance incomming!");
  display.display();
  
}
void text11() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) ;
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Normal      Traffic");
  display.display();
  
}


