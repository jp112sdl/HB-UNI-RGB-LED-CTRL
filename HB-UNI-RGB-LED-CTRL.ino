//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2018-08-03 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

// define this to read the device id, serial and device type from bootloader section
// #define USE_OTA_BOOTLOADER

#define EI_NOTEXTERNAL
#include <EnableInterrupt.h>
#include <SPI.h>
#include <AskSinPP.h>
#include <LowPower.h>
#include <Register.h>


#define WSNUM_LEDS    5          //Anzahl angeschlossener LEDs
#define WSLED_PIN     9          //GPIO Pin LED Anschluss 
#define WSLED_TYPE    WS2812B    //LED Typ
#define WSCOLOR_ORDER GRB        //Farbreihenfolge 

#define SLOW_PROGRAM_TIMER     30     //ms Wartezeit für den Übergang
#define NORMAL_PROGRAM_TIMER   15     //ms Wartezeit für den Übergang
#define FAST_PROGRAM_TIMER     0      //ms Wartezeit für den Übergang
#define FIRE_PROGRAM_COOLING   55     
#define FIRE_PROGRAM_SPARKLING 120

#define CONFIG_BUTTON_PIN 8
#define ONBOARD_LED_PIN 4

#include "RGBCtrl.h"

#define PEERS_PER_CHANNEL 4

using namespace as;

// define all device properties
const struct DeviceInfo PROGMEM devinfo = {
  {0xF3, 0x41, 0x01},     // Device ID
  "JPRGB00001",           // Device Serial
  {0xF3, 0x41},           // Device Model
  0x25,                   // Firmware Version
  as::DeviceType::Dimmer, // Device Type
  {0x01, 0x00}            // Info Bytes
};

/**
   Configure the used hardware
*/
#if defined __AVR_ATmega2560__
typedef AskSin<StatusLed<ONBOARD_LED_PIN>, NoBattery, Radio<LibSPI<53>, 2>> HalType;
#else
typedef AskSin<StatusLed<ONBOARD_LED_PIN>, NoBattery, Radio<LibSPI<10>, 2>> HalType;
#endif

DEFREGISTER(Reg0, MASTERID_REGS, 0x20, 0x21)
class Ws28xxList0 : public RegList0<Reg0> {
  public:
    Ws28xxList0(uint16_t addr) : RegList0<Reg0>(addr) {}

    void defaults () {
      clear();
    }
};

typedef RGBLEDChannel<HalType, PEERS_PER_CHANNEL, Ws28xxList0> ChannelType;
typedef RGBLEDDevice<HalType, ChannelType, 3, Ws28xxList0> RGBLEDType;

HalType hal;
RGBLEDType sdev(devinfo, 0x20);
ConfigButton<RGBLEDType> cfgBtn(sdev);

void setup () {
  DINIT(57600, ASKSIN_PLUS_PLUS_IDENTIFIER);
  sdev.init(hal);
  buttonISR(cfgBtn, CONFIG_BUTTON_PIN);
  sdev.initDone();
}

void loop() {
  bool worked = hal.runready();
  bool poll = sdev.pollRadio();
  if ( worked == false && poll == false ) {
    hal.activity.savePower<Idle<true> >(hal);
  }
  sdev.handleLED();
}
