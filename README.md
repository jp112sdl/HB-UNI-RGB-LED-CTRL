# HB-UNI-RGB-LED-CTRL
HomeMatic kompatibler RGB Controller für adressierbare RGB LEDs (WS28xx, Neopixel,...)


**Bis ca. 144 LEDs ist ein Arduino Pro Mini (3.3V / 8 MHz) ausreichend:**
![wiring_ProMini](Images/wiring_ProMini.png)

**Bei > 144 LEDs ist ein Arduino Mega 2560 erforderlich:**
![wiring_2560](Images/wiring_2560.png)

Um Platz zu sparen, kann man die [Mega2560 Core](https://de.aliexpress.com/item/Mega-2560-PRO-Embed-CH340G-ATmega2560-16AU-NO-pinheaders-Compatible-for-Arduino-Mega-2560/32802420999.html) Variante einsetzen:<br>
_Auf dem abgebildeten Foto habe ich die Reset-Leiterbahn durchtrennt, so dass ich den Taster an Pin13 als Config-Taster verdrahten konnte._<br>
<img src=Images/mega2560_core_front.jpg /><img src=Images/mega2560_core_back.jpg /><br>
**Achtung: anders als abgebildet, muss - um dauerhafte Beschädigungen am CC1101 zu vermeiden - ein [LevelShifter](https://www.ebay.de/itm/252797529930) in die Datenleitungen eingebunden werden.**




**Benötigte Libs:**
 - [FastLED](https://github.com/FastLED/FastLED)
 - [AskSinPP](https://github.com/pa-pa/AskSinPP)
   - sowie die dort aufgeführten [zusätzlichen Bibliotheken](https://github.com/pa-pa/AskSinPP#required-additional-arduino-libraries)

sowie auf der Zentrale (CCU2 / CCU3 / RaspberryMatic) das [JP-HB-Devices](https://github.com/jp112sdl/JP-HB-Devices-addon) Addon.
 
**Demo:**
![demo](Images/sample.png)
