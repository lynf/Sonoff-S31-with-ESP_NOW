/*
  S2mini-send

  Send Push Button switch input binary data to Responder

  Uniplex transmit binary data to receiver on dedicated channel
  Add switch input on transmitter, LED output on receiver

  Don't forget to change the MAC address to match the responder

  Status: OK code is working

  2024-03-20
  ==========
1. Modify switch handler to perform debouncing to eliminate the
   erratic switching due to switch contact chattering. OK
  
  2024-08-29
  ==========
2. Revise switch processing to use ezButton library, remove interrupt
   handler code.  OK code is working

*/

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ezButton.h>

// Variables
bool ledOn = false;
bool switchState = true; // Normally open switch

bool switchTrailEdge = false; // Normally open switch

// Define LED and pushbutton pins. Change to suite final application
#define STATUS_LED 15      // s2 mini LED
#define STATUS_BUTTON 17   // s2 mini use GP07 as EN not available on pad
//#define STATUS_BUTTON 0   // s2 mini EN switch
#define WIFI_CHANNEL 0     // Define channel to use

// Create ezButton object
ezButton button(STATUS_BUTTON);    // Attached to GPIO 17

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x08, 0xf9, 0xe0, 0x5d, 0x79, 0xcf}; // Sonoff S21 Smart Plug



// Define a data structure
typedef struct struct_message {
  bool d;
} struct_message;

// Create a structured object
struct_message myData;


// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void sentCallback(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nPacket Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Transmit callback Success" : "Transmit callback Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.println("===<< S2 Mini Send for Sonoff relay RLS1 >>=="); 

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init failed"); 
    return;
  }

  // Pushbutton uses built-in pullup resistor
  pinMode(STATUS_BUTTON, INPUT_PULLUP);

  // Debounce time
  button.setDebounceTime(10);   // 10 ms 
 
  // LED Output
  pinMode(STATUS_LED, OUTPUT);

  // Register the send callback
  esp_now_register_send_cb(sentCallback);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = WIFI_CHANNEL;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

} 


void loop()
{
// Check for switch pressed event and send to receiver if true

  button.loop();    // Must call loop() function first
  int switchState = button.getState();
  if(button.isPressed()) {

    ledOn = !ledOn;         // Toggle the LED state
    digitalWrite(STATUS_LED, ledOn);

      // Format structured data
      myData.d = ledOn;

      // Send toggle command message via ESP-NOW
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
          if (result == ESP_OK) {
          Serial.print("Toggle command: ");
          Serial.println(myData.d);
          }
          else {
          Serial.println("Sending error");
          }

  }
    
}