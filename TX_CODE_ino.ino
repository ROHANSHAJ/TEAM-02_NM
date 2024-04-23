#include <VirtualWire.h>

#define BUTTON_PIN 9 // Pin connected to the button
#define TX_PIN 12    // Pin connected to the RF transmitter

int buttonState = 0; // Variable to store the button state

void setup() {
    Serial.begin(9600); // Initialize serial communication

  pinMode(BUTTON_PIN, INPUT); // Set the button pin as input
  digitalWrite(BUTTON_PIN, HIGH); // Enable pull-up resistor
  pinMode(TX_PIN, OUTPUT); // Set the transmitter pin as output
  vw_set_tx_pin(TX_PIN);   // Set the TX pin for VirtualWire library
  vw_setup(2000);          // Bits per second
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN); // Read the state of the button

  if (buttonState == LOW) {
          Serial.println("low"); 
 // If button is presseda
    // Send '1' when button is pressed
    sendData(1);
    delay(100); // Debounce delay
  } else {
    // Send '2' when button is not pressed
    sendData(2);
          Serial.println("high"); 

    delay(100); // Debounce delay
  }
}

void sendData(int data) {
  vw_send((uint8_t *)&data, sizeof(data)); // Send data
  vw_wait_tx(); // Wait for transmission to complete
}