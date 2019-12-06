//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2017-03-29 papa Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
// 2018-08-03 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef __RGBLEDXX_H__
#define __RGBLEDXX_H__

#include <MultiChannelDevice.h>
#include <Register.h>
#include <FastLED.h>
#define LOGIC_INACTIVE 0
#define LOGIC_OR 1
#define LOGIC_AND 2
#define LOGIC_XOR 3
#define LOGIC_NOR 4
#define LOGIC_NAND 5
#define LOGIC_ORINVERS 6
#define LOGIC_ANDINVERS 7
#define LOGIC_PLUS 8
#define LOGIC_MINUS 9
#define LOGIC_MUL 10
#define LOGIC_PLUSINVERS 11
#define LOGIC_MINUSINVERS 12
#define LOGIC_MULINVERS 13
#define LOGIC_INVERSPLUS 14
#define LOGIC_INVERSMINUS 15
#define LOGIC_INVERSMUL 16

#ifdef ENABLE_RGBW
CRGBW leds[WSNUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];
#else
CRGB leds[WSNUM_LEDS];
#endif

#include "RGBPrograms.h"

namespace as {

DEFREGISTER(DimmerReg1, CREG_AES_ACTIVE, CREG_TRANSMITTRYMAX, CREG_OVERTEMPLEVEL,
            CREG_REDUCETEMPLEVEL, CREG_REDUCELEVEL, CREG_POWERUPACTION, CREG_STATUSINFO,
            CREG_CHARACTERISTIC, CREG_LOGICCOMBINATION)

class DimmerList1 : public RegList1<DimmerReg1> {
  public:
    DimmerList1 (uint16_t addr) : RegList1<DimmerReg1>(addr) {}
    void defaults () {
      clear();
      // aesActive(false);
      transmitTryMax(6);
      // powerUpAction(false);
      statusInfoMinDly(4);
      statusInfoRandom(1);

      overTempLevel(80);
      reduceTempLevel(75);
      reduceLevel(80);
      characteristic(true);
      logicCombination(LOGIC_OR);
    }
};

DEFREGISTER(DimmerReg3, PREG_CTRAMPONOFF, PREG_CTDELAYONOFF, PREG_CTONOFF,
            PREG_CONDVALUELOW, PREG_CONDVALUEHIGH, PREG_ONDELAYTIME, PREG_ONTIME,
            PREG_OFFDELAYTIME, PREG_OFFTIME, PREG_ACTIONTYPE, PREG_JTONOFF,
            PREG_JTDELAYONOFF, PREG_JTRAMPONOFF, PREG_DELAYMODE, PREG_OFFLEVEL,
            PREG_ONMINLEVEL, PREG_ONLEVEL, PREG_RAMPSTARTSTEP, PREG_RAMPONTIME,
            PREG_RAMPOFFTIME, PREG_DIMMINLEVEL, PREG_DIMMAXLEVEL, PREG_DIMSTEP,
            PREG_OFFDELAYSTEP, PREG_OFFDELAYNEWTIME, PREG_OFFDELAYOLDTIME,
            PREG_ELSEACTIONTYPE, PREG_ELSEJTONOFF, PREG_ELSEJTDELAYONOFF,
            PREG_ELSEJTRAMPONOFF)

typedef RegList3<DimmerReg3> DimmerPeerList;

class DimmerList3 : public ShortLongList<DimmerPeerList> {
  public:
    DimmerList3 (uint16_t addr) : ShortLongList<DimmerPeerList>(addr) {}
    void defaults() {
      DimmerPeerList ssl = sh();
      ssl.clear();
      //    ssl.ctRampOn(0);
      //    ssl.ctRampOff(0);
      //    ssl.ctDlyOn(0);
      //    ssl.ctDlyOff(0);
      //    ssl.ctOn(0);
      //    ssl.ctOff(0);
      ssl.ctValLo(0x32);
      ssl.ctValHi(0x64);
      //    ssl.onDly(0);
      ssl.onTime(0xff);
      //    ssl.offDly(0);
      ssl.offTime(0xff);
      ssl.actionType(AS_CM_ACTIONTYPE_JUMP_TO_TARGET);
      //    ssl.offTimeMode(false);
      //    ssl.onTimeMode(false);
      ssl.offDelayBlink(true);
      //    ssl.offLevel(0);
      ssl.onMinLevel(20);
      ssl.onLevel(200); // 201 ???
      ssl.rampStartStep(10);
      //    ssl.rampOnTime(0);
      //    ssl.rampOffTime(0);
      //    ssl.dimMinLevel(0);
      ssl.dimMaxLevel(200);
      ssl.dimStep(5);
      ssl.offDelayStep(10);
      ssl.offDelayNewTime(5);
      ssl.offDelayOldTime(5);
      ssl.elseActionType(AS_CM_ACTIONTYPE_INACTIVE);
      //    ssl.elseOffTimeMode(false);
      //    ssl.elseOnTimeMode(false);
      ssl.elseJtOn(AS_CM_JT_ONDELAY);
      ssl.elseJtOff(AS_CM_JT_ONDELAY);
      ssl.elseJtDlyOn(AS_CM_JT_ONDELAY);
      ssl.elseJtDlyOff(AS_CM_JT_ONDELAY);
      ssl.elseJtRampOn(AS_CM_JT_ONDELAY);
      ssl.elseJtRampOff(AS_CM_JT_ONDELAY);

      ssl = lg();
      ssl.clear();
      //    ssl.ctRampOn(0);
      //    ssl.ctRampOff(0);
      //    ssl.ctDlyOn(0);
      //    ssl.ctDlyOff(0);
      //    ssl.ctOn(0);
      //    ssl.ctOff(0);
      ssl.ctValLo(0x32);
      ssl.ctValHi(0x64);
      //    ssl.onDly(0);
      ssl.onTime(0xff);
      //    ssl.offDly(0);
      ssl.offTime(0xff);
      ssl.actionType(AS_CM_ACTIONTYPE_JUMP_TO_TARGET);
      ssl.multiExec(true);
      //    ssl.offTimeMode(false);
      //    ssl.onTimeMode(false);
      ssl.offDelayBlink(true);
      //    ssl.offLevel(0);
      ssl.onMinLevel(20);
      ssl.onLevel(200); // 201 ???
      ssl.rampStartStep(10);
      //    ssl.rampOnTime(0);
      //    ssl.rampOffTime(0);
      //    ssl.dimMinLevel(0);
      ssl.dimMaxLevel(200);
      ssl.dimStep(5);
      ssl.offDelayStep(10);
      ssl.offDelayNewTime(5);
      ssl.offDelayOldTime(5);
      ssl.elseActionType(AS_CM_ACTIONTYPE_INACTIVE);
      //    ssl.elseOffTimeMode(false);
      //    ssl.elseOnTimeMode(false);
      ssl.elseJtOn(AS_CM_JT_ONDELAY);
      ssl.elseJtOff(AS_CM_JT_ONDELAY);
      ssl.elseJtDlyOn(AS_CM_JT_ONDELAY);
      ssl.elseJtDlyOff(AS_CM_JT_ONDELAY);
      ssl.elseJtRampOn(AS_CM_JT_ONDELAY);
      ssl.elseJtRampOff(AS_CM_JT_ONDELAY);
    }

    void odd() {
      defaults();
      DimmerPeerList ssl = sh();
      ssl.jtOn(AS_CM_JT_OFFDELAY);
      ssl.jtOff(AS_CM_JT_OFF);
      ssl.jtDlyOn(AS_CM_JT_RAMPOFF);
      ssl.jtDlyOff(AS_CM_JT_RAMPOFF);
      ssl.jtRampOn(AS_CM_JT_RAMPOFF);
      ssl.jtRampOff(AS_CM_JT_OFF);
      ssl = lg();
      ssl.actionType(AS_CM_ACTIONTYPE_DOWNDIM);
    }

    void even() {
      defaults();
      DimmerPeerList ssl = sh();
      ssl.jtOn(AS_CM_JT_ON);
      ssl.jtOff(AS_CM_JT_ONDELAY);
      ssl.jtDlyOn(AS_CM_JT_RAMPON);
      ssl.jtDlyOff(AS_CM_JT_RAMPON);
      ssl.jtRampOn(AS_CM_JT_ON);
      ssl.jtRampOff(AS_CM_JT_RAMPON);
      ssl = lg();
      ssl.actionType(AS_CM_ACTIONTYPE_UPDIM);
    }

    void single() {
      defaults();
      DimmerPeerList ssl = sh();
      ssl.jtOn(AS_CM_JT_OFFDELAY);
      ssl.jtOff(AS_CM_JT_ONDELAY);
      ssl.jtDlyOn(AS_CM_JT_RAMPON);
      ssl.jtDlyOff(AS_CM_JT_RAMPOFF);
      ssl.jtRampOn(AS_CM_JT_ON);
      ssl.jtRampOff(AS_CM_JT_OFF);
      ssl = lg();
      ssl.actionType(AS_CM_ACTIONTYPE_TOGGLEDIM_TO_COUNTER);
    }

};


class DimmerStateMachine {

#define DELAY_NO 0x00
#define DELAY_INFINITE 0xffffffff

    class RampAlarm : public Alarm {
      public:
        DimmerStateMachine& sm;
        DimmerPeerList      lst;
        uint32_t            delay, tack;
        uint8_t             destlevel;
        uint8_t             dx;
        uint8_t             brightness;

        RampAlarm (DimmerStateMachine& m) : Alarm(0), sm(m), lst(0), delay(0), tack(0), destlevel(0), dx(5), brightness(0) {}
        void list (DimmerPeerList l) {
          lst = l;
          delay = tack = 0;
          destlevel = sm.status();
        }
        void init (uint8_t state, DimmerPeerList l) {
          uint8_t destlevel = state == AS_CM_JT_RAMPOFF ? 0 : 200;
          if ( l.valid() == true ) {
            destlevel = state == AS_CM_JT_RAMPOFF ? l.offLevel() : l.onLevel();
          }
          init(sm.getDelayForState(state, l), destlevel, l.valid() ? 0 : DELAY_INFINITE, l);
        }
        void init (uint32_t ramptime, uint8_t level, uint32_t dly, DimmerPeerList l = DimmerPeerList(0)) {
          // DPRINT("Ramp/Level: ");DDEC(ramptime);DPRINT("/");DDECLN(level);
          lst = l;
          destlevel = level == 201 ? sm.lastonlevel : level;
          delay = dly;
          sm.updateState(destlevel == 0 ? AS_CM_JT_RAMPOFF : AS_CM_JT_RAMPON);
          uint8_t curlevel = sm.status();
          uint32_t diff;
          if ( curlevel > destlevel ) { // dim down
            diff = curlevel - destlevel;
          }
          else { // dim up
            diff = destlevel - curlevel;
          }
          if ( ramptime > diff ) {
            dx = 1;
            tack = ramptime / diff;
          }
          else {
            tack = 1;
            dx = uint8_t(diff / (ramptime > 0 ? ramptime : 1));
          }
          //      DPRINT("Dx/Tack: ");DDEC(dx);DPRINT("/");DDECLN(tack);
        }
        virtual void trigger (AlarmClock& clock) {
          uint8_t curlevel = sm.status();
          //DHEX(curlevel); DPRINT("  "); DHEXLN(destlevel);

          if ( sm.status() != destlevel ) {
            if ( curlevel > destlevel ) { // dim down
              uint8_t rest = curlevel - destlevel;
              sm.updateLevel( curlevel - (rest < dx ? rest : dx));
            }
            else { // dim up
              uint8_t rest = destlevel - curlevel;
              sm.updateLevel( curlevel + (rest < dx ? rest : dx));
            }
          }
          // we catch our destination level -> go to next state
          if ( sm.status() == destlevel ) {
            uint8_t next = sm.getNextState();
            if ( delay == 0 && lst.valid() == true ) {
              delay = sm.getDelayForState(next, lst);
            }
            sm.setState(next, delay, lst);
          }
          else { // enable again for next ramp step
            set(tack);
            clock.add(*this);
          }

          // FastLED.setBrightness(  constrain(((curlevel * 1275L) / 1000) - ((destlevel == 0) ? 6 : 0), 0, 255) );

        }
    };

    void updateLevel (uint8_t newlevel) {
      level = newlevel;
      //DPRINT("updateLevel(): "); DDECLN(newlevel);
      FastLED.setBrightness( constrain(((newlevel * 1275L) / 1000) - 1, 0, 255) );
      //    changed = true;
    }

    void updateState (uint8_t next) {
      if ( state != next ) {
        switchState(state, next);
        state = next;
        changed = true;
      }
    }

    void setState (uint8_t next, uint32_t delay, const DimmerPeerList& lst = DimmerPeerList(0), uint8_t deep = 0) {
      // check deep to prevent infinite recursion
      if ( next != AS_CM_JT_NONE && deep < 4) {
        // first cancel possible running alarm
        sysclock.cancel(alarm);
        // if state is different
        if (state != next) {
          updateState(next);
        }
        if ( state == AS_CM_JT_RAMPON || state == AS_CM_JT_RAMPOFF ) {
          alarm.init(state, lst);
          sysclock.add(alarm);
        }
        else {
          if (delay == DELAY_NO) {
            // go immediately to the next state
            next = getNextState();
            delay = getDelayForState(next, lst);
            setState(next, delay, lst, ++deep);
          }
          else if (delay != DELAY_INFINITE) {
            alarm.list(lst);
            alarm.set(delay);
            sysclock.add(alarm);
          }
        }
      }
    }

  protected:
    uint8_t    state : 4;
    bool       changed : 1;
    bool       toggledimup : 1;
    uint8_t    level, lastonlevel;
    RampAlarm  alarm;

  public:
    DimmerStateMachine() : state(AS_CM_JT_NONE), changed(false), toggledimup(true), level(0), lastonlevel(200), alarm(*this) {}
    virtual ~DimmerStateMachine () {}

    virtual void switchState(__attribute__ ((unused)) uint8_t oldstate, uint8_t newstate) {
      // DPRINT("Dimmer State: ");DHEX(oldstate);DPRINT(" -> ");DHEX(newstate);DPRINT("  Level: ");DHEXLN(level);
      if ( newstate == AS_CM_JT_ON ) {
        lastonlevel = level;
      }
    }

    void jumpToTarget(const DimmerPeerList& lst) {
      uint8_t next = getJumpTarget(state, lst);
      // DPRINT("Jmp: ");DHEX(state);DPRINT(" - ");DHEXLN(next);
      if ( next != AS_CM_JT_NONE ) {
        // get delay
        uint32_t dly = getDelayForState(next, lst);
        // switch to next
        setState(next, dly, lst);
      }
    }

    void toggleState () {
      if ( state == AS_CM_JT_OFF ) {
        setLevel(lastonlevel, 5, 0xffff);
      }
      else {
        setLevel(0, 5, 0xffff);
      }
    }

    uint8_t getNextState () {
      switch ( state ) {
        case AS_CM_JT_ONDELAY:  return AS_CM_JT_RAMPON;
        case AS_CM_JT_RAMPON:   return AS_CM_JT_ON;
        case AS_CM_JT_ON:       return AS_CM_JT_OFFDELAY;
        case AS_CM_JT_OFFDELAY: return AS_CM_JT_RAMPOFF;
        case AS_CM_JT_RAMPOFF:  return AS_CM_JT_OFF;
        case AS_CM_JT_OFF:      return AS_CM_JT_ONDELAY;
      }
      return AS_CM_JT_NONE;
    }

    uint8_t getJumpTarget(uint8_t stat, const DimmerPeerList& lst) const {
      switch ( stat ) {
        case AS_CM_JT_ONDELAY:  return lst.jtDlyOn();
        case AS_CM_JT_RAMPON:   return lst.jtRampOn();
        case AS_CM_JT_ON:       return lst.jtOn();
        case AS_CM_JT_OFFDELAY: return lst.jtDlyOff();
        case AS_CM_JT_RAMPOFF:  return lst.jtRampOff();
        case AS_CM_JT_OFF:      return lst.jtOff();
      }
      return AS_CM_JT_NONE;
    }

    uint8_t getConditionForState(uint8_t stat, const DimmerPeerList& lst) const {
      switch ( stat ) {
        case AS_CM_JT_ONDELAY:  return lst.ctDlyOn();
        case AS_CM_JT_RAMPON:   return lst.ctRampOn();
        case AS_CM_JT_ON:       return lst.ctOn();
        case AS_CM_JT_OFFDELAY: return lst.ctDlyOff();
        case AS_CM_JT_RAMPOFF:  return lst.ctRampOff();
        case AS_CM_JT_OFF:      return lst.ctOff();
      }
      return AS_CM_CT_X_GE_COND_VALUE_LO;
    }

    uint32_t getDelayForState(uint8_t stat, const DimmerPeerList& lst) const {
      if ( lst.valid() == false ) {
        return getDefaultDelay(stat);
      }
      uint8_t value = 0;
      switch ( stat ) {
        case AS_CM_JT_ONDELAY:  value = lst.onDly(); break;
        case AS_CM_JT_RAMPON:   value = lst.rampOnTime(); break;
        case AS_CM_JT_ON:       value = lst.onTime(); break;
        case AS_CM_JT_OFFDELAY: value = lst.offDly(); break;
        case AS_CM_JT_RAMPOFF:  value = lst.rampOffTime(); break;
        case AS_CM_JT_OFF:      value = lst.offTime(); break;
      }
      return AskSinBase::byteTimeCvt(value);
    }

    uint32_t getDefaultDelay(uint8_t stat) const {
      switch ( stat ) {
        case AS_CM_JT_ON:
        case AS_CM_JT_OFF:
          return DELAY_INFINITE;
        case AS_CM_JT_RAMPON:
        case AS_CM_JT_RAMPOFF:
          return decis2ticks(5);
      }
      return DELAY_NO;
    }

    bool delayActive () const {
      return sysclock.get(alarm) > 0;
    }

    void dimUp (const DimmerPeerList& lst) {
      uint8_t dx = lst.dimStep();
      uint8_t newlevel = level + dx;
      if ( newlevel > lst.dimMaxLevel() ) {
        newlevel = lst.dimMaxLevel();
      }
      updateState(AS_CM_JT_RAMPON);
      updateLevel(newlevel);
      updateState(AS_CM_JT_ON);
    }

    void dimDown (const DimmerPeerList& lst) {
      uint8_t dx = lst.dimStep();
      uint8_t newlevel = level - (dx < level ? dx : level);
      if ( newlevel < lst.dimMinLevel() ) {
        newlevel = lst.dimMinLevel();
      }
      updateState(newlevel > lst.onMinLevel() ? AS_CM_JT_RAMPON : AS_CM_JT_RAMPOFF);
      updateLevel(newlevel);
      updateState(newlevel > lst.onMinLevel() ? AS_CM_JT_ON : AS_CM_JT_OFF);
    }

    void remote (const DimmerPeerList& lst, uint8_t counter) {
      // perform action as defined in the list
      switch (lst.actionType()) {
        case AS_CM_ACTIONTYPE_JUMP_TO_TARGET:
          jumpToTarget(lst);
          break;
        case AS_CM_ACTIONTYPE_TOGGLE_TO_COUNTER:
          setState((counter & 0x01) == 0x01 ? AS_CM_JT_RAMPON : AS_CM_JT_RAMPOFF, DELAY_INFINITE, lst);
          break;
        case AS_CM_ACTIONTYPE_TOGGLE_INVERSE_TO_COUNTER:
          setState((counter & 0x01) == 0x01 ? AS_CM_JT_RAMPON : AS_CM_JT_RAMPOFF, DELAY_INFINITE, lst);
          break;
        case AS_CM_ACTIONTYPE_UPDIM:
          dimUp(lst);
          break;
        case AS_CM_ACTIONTYPE_DOWNDIM:
          dimDown(lst);
          break;
        case AS_CM_ACTIONTYPE_TOGGLEDIM:
          if ( toggledimup == true ) dimUp(lst);
          else dimDown(lst);
          toggledimup = ! toggledimup;
          break;
        case AS_CM_ACTIONTYPE_TOGGLEDIM_TO_COUNTER:
          (counter & 0x01) == 0x01 ? dimUp(lst) : dimDown(lst);
          break;
        case AS_CM_ACTIONTYPE_TOGGLEDIM_TO_COUNTER_INVERSE:
          (counter & 0x01) == 0x00 ? dimUp(lst) : dimDown(lst);
          break;
      }

    }

    void sensor (const DimmerPeerList& lst, uint8_t counter, uint8_t value) {
      uint8_t cond = getConditionForState(state, lst);
      bool doit = false;
      switch ( cond ) {
        case AS_CM_CT_X_GE_COND_VALUE_LO:
          doit = (value >= lst.ctValLo());
          break;
        case AS_CM_CT_X_GE_COND_VALUE_HI:
          doit = (value >= lst.ctValHi());
          break;
        case AS_CM_CT_X_LT_COND_VALUE_LO:
          doit = (value < lst.ctValLo());
          break;
        case AS_CM_CT_X_LT_COND_VALUE_HI:
          doit = (value < lst.ctValHi());
          break;
        case AS_CM_CT_COND_VALUE_LO_LE_X_LT_COND_VALUE_HI:
          doit = ((lst.ctValLo() <= value) && (value < lst.ctValHi()));
          break;
        case AS_CM_CT_X_LT_COND_VALUE_LO_OR_X_GE_COND_VALUE_HI:
          doit = ((value < lst.ctValLo()) || (value >= lst.ctValHi()));
          break;
      }
      if ( doit == true ) {
        remote(lst, counter);
      }
      else {
        // TODO use else jump table
      }
    }

    void setLevel (uint8_t level, uint16_t ramp, uint16_t delay) {
      DPRINT("SetLevel: "); DHEX(level); DPRINT(" "); DHEX(ramp); DPRINT(" "); DHEXLN(delay);
      if ( ramp == 0 ) {
        alarm.destlevel = level;
        updateLevel(level);
        setState(level == 0 ? AS_CM_JT_OFF : AS_CM_JT_ON, AskSinBase::intTimeCvt(delay));
        FastLED.setBrightness(  level );
      }
      else {
        sysclock.cancel(alarm);
        alarm.init(AskSinBase::intTimeCvt(ramp), level, AskSinBase::intTimeCvt(delay));
        sysclock.add(alarm);
      }
    }

    uint8_t status () const {
      return level;
    }

    uint8_t flags () const {
      uint8_t f = delayActive() ? 0x40 : 0x00;
      if ( alarm.destlevel < level) {
        f |= AS_CM_EXTSTATE_DOWN;
      }
      else if ( alarm.destlevel > level) {
        f |= AS_CM_EXTSTATE_UP;
      }
      return f;
    }
};

static uint8_t physical(0);
static uint8_t brightness(0);
static uint8_t currentProgram(0);
static uint8_t currentColor(0);

template <class HalType, int PeerCount, class List0Type>
class RGBLEDChannel : public Channel<HalType, DimmerList1, DimmerList3, EmptyList, PeerCount, List0Type>, public DimmerStateMachine {

    uint8_t lastmsgcnt;

  protected:
    typedef Channel<HalType, DimmerList1, DimmerList3, EmptyList, PeerCount, List0Type> BaseChannel;

  public:
    RGBLEDChannel () : BaseChannel(), lastmsgcnt(0xff) {}
    virtual ~RGBLEDChannel() {}

    void setup(Device<HalType, List0Type>* dev, uint8_t number, uint16_t addr) {
      BaseChannel::setup(dev, number, addr);
    }

    bool changed () const {
      return DimmerStateMachine::changed;
    }

    void changed (bool c) {
      DimmerStateMachine::changed = c;
    }

    void patchStatus (Message& msg) {
      switch (this->number()) {
        case 1:
          if ( msg.length() == 0x0e ) {
            msg.length(0x0f);
            msg.data()[3] = physical;
          }
          break;
        case 2:
          if ( msg.length() == 0x0e ) {
            msg.data()[0] = currentColor;
          }
          break;
        case 3:
          if ( msg.length() == 0x0e ) {
            msg.data()[0] = currentProgram;
          }
          break;
      }
    }

    bool process (const Message& msg) {
      DPRINTLN("process Message");
      return true;
    }

    bool process (const ActionSetMsg& msg) {
      DPRINT("process() "); DDECLN(this->number());
      DPRINT("msg.value = "); DDECLN(msg.value());
      DPRINT("msg.ramp = "); DDECLN(msg.ramp());
      DPRINT("msg.delay= "); DDECLN(msg.delay());
      switch (this->number()) {
        case 1:
          brightness = msg.value();
          setLevel( msg.value(), msg.ramp(), msg.delay() );
          break;
        case 2:
          currentColor = msg.value();
          setColor (currentColor);
          break;
        case 3:
          currentProgram = msg.value();
          runProgram (currentProgram);
          break;
        default:
          break;
      }
      return true;
    }

    bool process (const RemoteEventMsg& msg) {
      bool lg = msg.isLong();
      Peer p(msg.peer());
      uint8_t cnt = msg.counter();
      typename BaseChannel::List3 l3 = BaseChannel::getList3(p);
      if ( l3.valid() == true ) {
        // l3.dump();
        typename BaseChannel::List3::PeerList pl = lg ? l3.lg() : l3.sh();
        // pl.dump();
        if ( cnt != lastmsgcnt || (lg == true && pl.multiExec() == true) ) {
          lastmsgcnt = cnt;
          remote(pl, cnt);
        }
        return true;
      }
      return false;
    }

    void setColor(uint8_t val) {
      for (int i = 0; i < WSNUM_LEDS; i++) {
        leds[i] = CHSV((val * 1275L) / 1000, (val <  200) ? 255 : 0, 255);
      }
    }

    void runProgram(uint8_t val) {
      switch (val) {
        case 0:
          setColor(currentColor);
          break;
        case 1:
          RGBProgramRainbow(SLOW_PROGRAM_TIMER, brightness);
          break;
        case 2:
          RGBProgramRainbow(NORMAL_PROGRAM_TIMER, brightness);
          break;
        case 3:
          RGBProgramRainbow(FAST_PROGRAM_TIMER, brightness);
          break;
        case 4:
          RGBProgramFire(brightness);
          break;
        case 5:
          RGBProgramWaterfall(brightness);
          break;
        case 6:
          RGBProgramTVSimulation(brightness);
          break;
      }
    }

    bool process (const SensorEventMsg & msg) {
      bool lg = msg.isLong();
      Peer p(msg.peer());
      uint8_t cnt = msg.counter();
      uint8_t value = msg.value();
      typename BaseChannel::List3 l3 = BaseChannel::getList3(p);
      if ( l3.valid() == true ) {
        // l3.dump();
        typename BaseChannel::List3::PeerList pl = lg ? l3.lg() : l3.sh();
        // pl.dump();
        sensor(pl, cnt, value);
        return true;
      }
      return false;
    }
};



template<class HalType, class ChannelType, int ChannelCount, class List0Type>
class RGBLEDDevice : public MultiChannelDevice<HalType, ChannelType, ChannelCount, List0Type> {

  public:
    typedef MultiChannelDevice<HalType, ChannelType, ChannelCount, List0Type> DeviceType;

    RGBLEDDevice (const DeviceInfo& info, uint16_t addr) : DeviceType(info, addr) {}
    virtual ~RGBLEDDevice () {}

    void firstinit () {
      DeviceType::firstinit();
      DeviceType::channel(1).getList1().logicCombination(LOGIC_OR);
      for ( uint8_t i = 2; i <= DeviceType::channels(); ++i ) {
        DeviceType::channel(i).getList1().logicCombination(LOGIC_INACTIVE);
      }
    }

    virtual void configChanged () {
      DeviceType::configChanged();
      DPRINTLN("* Config Changed       : List0");
      for (int i = 0; i < WSNUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();

#ifdef PWM_ENABLED
      static AnalogPWMController<PWM_RED_PIN, PWM_GREEN_PIN, PWM_BLUE_PIN, PWM_WHITE_PIN, PWM_WHITE_ONLY> controler;
      FastLED.addLeds(&controler, leds, 1);
#else
#ifdef ENABLE_RGBW
      FastLED.addLeds<WSLED_TYPE, WSLED_PIN, RGB>(ledsRGB, getRGBWsize(WSNUM_LEDS));
#else
      FastLED.addLeds<WSLED_TYPE, WSLED_PIN, WSCOLOR_ORDER>(leds, WSNUM_LEDS);
#endif
#endif

      DeviceType::channel(2).setColor(0);
    }

    bool handleLED() {
      DeviceType::channel(3).runProgram(currentProgram);
      FastLED.show();
    }

    void init (HalType& hal) {
      DeviceType::init(hal);
      //if ( DeviceType::channel(1).getList1().powerUpAction() == true ) {
      //  DeviceType::channel(1).setLevel(200, 5, 0xffff);
      // }
      //else {
      DeviceType::channel(1).setLevel(0, 0, 0xffff);
      DeviceType::channel(2).setLevel(0, 0, 0xffff);
      DeviceType::channel(3).setLevel(0, 0, 0xffff);
      // }
    }

    uint16_t combineChannels () {
      uint16_t value = 0;
      for ( uint8_t i = 1; i < DeviceType::channels(); ++i ) {
        uint8_t level = DeviceType::channel(i).status();
        switch ( DeviceType::channel(i).getList1().logicCombination() ) {
          default:
          case LOGIC_INACTIVE:
            break;
          case LOGIC_OR:
            value = value > level ? value : level;
            break;
          case LOGIC_AND:
            value = value < level ? value : level;
            break;
          case LOGIC_XOR:
            value = value == 0 ? level : (level == 0 ? value : 0);
            break;
          case LOGIC_NOR:
            value = 200 - (value > level ? value : level);
            break;
          case LOGIC_NAND:
            value = 200 - (value < level ? value : level);
            break;
          case LOGIC_ORINVERS:
            level = 200 - level;
            value = value > level ? value : level;
            break;
          case LOGIC_ANDINVERS:
            level = 200 - level;
            value = value < level ? value : level;
            break;
          case LOGIC_PLUS:
            value += level;
            if ( value > 200 ) value = 200;
            break;
          case LOGIC_MINUS:
            if ( level > value ) value = 0;
            else value -= level;
            break;
          case LOGIC_MUL:
            value = value * level / 200;
            break;
          case LOGIC_PLUSINVERS:
            level = 200 - level;
            value += level;
            if ( value > 200 ) value = 200;
            break;
            break;
          case LOGIC_MINUSINVERS:
            level = 200 - level;
            if ( level > value ) value = 0;
            else value -= level;
            break;
          case LOGIC_MULINVERS:
            level = 200 - level;
            value = value * level / 200;
            break;
          case LOGIC_INVERSPLUS:
            value += level;
            if ( value > 200 ) value = 200;
            value = 200 - value;
            break;
          case LOGIC_INVERSMINUS:
            if ( level > value ) value = 0;
            else value -= level;
            value = 200 - value;
            break;
          case LOGIC_INVERSMUL:
            value = value * level / 200;
            value = 200 - value;
            break;
        }
      }
      // DHEXLN(value);
      return value;
    }

};

}

#endif
