#include <Arduino.h>

/*
  esp8266-recv
  
  Written for the ESP8266 in Sonoff S31 smart switch to
  replace the factory program with code to operate with
  a smarty type push-button remote controller. Forked
  from esp32c3-recv code.

  Note differences to ESP32 code:
  =====
  1. Include libraries are in the Arduino core, no need to
     specify external libraries.
  2. Change GPIO assignments to match Sonoff S32 I/O.
  3. Change the receiveCallback() to match the ESP8266
     <espnow.h> function definition.

  Receives toggle command (binary data) from transmitter
  Writes toggle command result to RELAY (output relay)
*/

// Include Libraries
#include <espnow.h>
#include <ESP8266WiFi.h>

// Variables
bool ledOn = false;       // ledOn is relay drive signal
bool switch_value = false;

// Define LED and pushbutton pins based on Sonoff S31 circuit.

#define STATUS_LED 13      // Onboard green LED, not used
#define RELAY 12           // Relay and red LED
#define STATUS_BUTTON 0    // BOOT switch (EN) on 8266
#define WIFI_CHANNEL 0     // Define channel to use

// Define a data structure
typedef struct struct_message {
  bool d;
} struct_message;

// Create a structured object
struct_message myData;

// Callback function executed when data is received
void receiveCallback(uint8_t *macAddr, uint8_t *IncomingData, uint8_t len) {
  memcpy(&myData, IncomingData, sizeof(myData));

  Serial.print("Toggle state: ");
  Serial.println(myData.d);
  ledOn = myData.d;
  digitalWrite(RELAY, ledOn); 
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.print("===<< Sonoff S31 relay >>===\n\r");  
  
  // Set ESP8266 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW Init error");
    return;
  }

  // Register receive callback function
  esp_now_register_recv_cb(receiveCallback);

  // LED Output
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, ledOn);
}
 
// Loop is empty, received data processed by recv callback function

void loop() {
}