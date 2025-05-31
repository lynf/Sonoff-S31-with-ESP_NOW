S2mini-send
===========

The esp32S2-mini-send code module for PB switch sender device. the 'main.cpp' file has a 6 byte
array declaration below the comment line "MAC Address of responder". You must edit values in this
array to match the MAC address of the ESP32 S2 MCU in the Sonoff S31 Lite Smart Plug device you will
be using. See the documentation for details on how to extract the MAC address from the MCU.

Save the edited main.cpp file and rebuild the code under the PlatformIO IDE. Connect the ESP32 S2
mini board to host PC running PlatformIO using a USB cable. Make sure you press the reset button
on the board while you are plugging in the cable to ensure the board boots up in the bootloader
mode. Release the reset button and proceed to upload the code to the S2 mini board.



