8266-recv
=========
The 8266-recv module code is designed to replace the Sonoff S31 Smart Plug factory firmware.

The Sonoff S31 with the 8266-recv replacement firmware now functions as a receiver in a
one-to-one connectionless WIFI link to a companion PB (push-button) switch sender using the
Espressif ESP-NOW communications protocol. This direct radio link between the modified SONOFF
S31 and the PB switch sender does not need to establish a connection via a local area network
access point (AP).

There are two tasks you need to do when installing the 8266-recv module to the S31 device.
Follow the instructions in the documentation to attach temporarily to the small daughter
board a USB to serial adapter using four connecting wires. Then perform the two tasks below,
in any order.

Task 1.
Connect the USB to serial adapter via a USB cable to the host PC, pressing the reset
button while plugging in the cable to the PC. This ensures the ESP8266 MCU boots up in
the bootloader mode.

Invoke the bash script 'mac_addr' to read and display the MAC address for this particular
ESP8266 MCU device. The MAC address will be displayed on the terminal screen if the
operation was successful. Record this information for later use. You can run the script in
PlatformIO by opening up a terminal screen.

Task 2.
Make sure the ESP8266 MCU is still connected in the boot loader mode. Under PlatformIO IDE,
run the build command. The run the upload command to flash the new code to the ESP8266. If
all is successful, remove the USB to serial converted and the interconnecting wires, and
re-assemble the ciruit board of the S31 into its case.



