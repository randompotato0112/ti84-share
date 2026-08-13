# ti84-wifi-bridge

A hardware/software bridge to get a TI-84 calculator online. It uses an ESP8266 to read the 2.5mm link port and pushes the data to a GitHub repo, which acts as a makeshift cloud database.

## Hardware Setup
TI-84 Plus / CE
ESP8266 (NodeMCU / Wemos D1)
3.3V to 5V Logic Level Shifter
Cut 2.5mm audio cable

## Pinout
Tip (Red): TI Data -> Level Shifter -> ESP D1
Ring (White): TI Clock -> Level Shifter -> ESP D2
Sleeve (Copper): TI Ground -> ESP GND
