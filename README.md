The Sonoff S31 Lite Smart Plug is re-purposed to operate as a remote smart relay controlled by a companion sender unit with a single PB (push button) switch. A connectionless WiFi communications link between the smart relay and the PB sender unit is based on the Espressif ESP NOW communications protocol. This link operates independently of an Access Point to a Local Area Network. The smart relay and the PB sender unit operate independently of any other software programs, making them very easy to deploy.

Two software modules are provided, the 8266-recv module and the S2mini-send module. Both modules use the ESP NOW library for managing the required WiFi peripherals and to implement the various communications protocol layers and functions. The 8266-recv module is compiled and flashed to the ESP8266 MCU in the S31 smart plug device. The S2mini-send module is compiled and flashed to the ESP32-S2 mini controller board in the PB sender unit. Both software modules are written in C++ language.





