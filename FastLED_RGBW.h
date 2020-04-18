/* FastLED_RGBW
 * 
 * Hack to enable SK6812 RGBW strips to work with FastLED.
 *
 * Original code by Jim Bumgardner (http://krazydad.com).
 * Modified by David Madison (http://partsnotincluded.com).
 * 
*/

#ifndef FastLED_RGBW_h
#define FastLED_RGBW_h

struct CRGBW  {
  union {
    struct {
      union {
        uint8_t g;
        uint8_t green;
      };
      union {
        uint8_t r;
        uint8_t red;
      };
      union {
        uint8_t b;
        uint8_t blue;
      };
      union {
        uint8_t w;
        uint8_t white;
      };
    };
    uint8_t raw[4];
  };

  CRGBW(){}


CRGBW(uint8_t rd, uint8_t grn, uint8_t blu){ 
w = min(rd, grn);
w = min(w, blu); 

r = rd - w;
g = grn - w;
b = blu - w;
}

inline void operator = (const CRGB c) __attribute__((always_inline)){ 
uint8_t w = min(c.r, c.g);
w = min(w, c.b); 
this->r = c.r - w;
this->g = c.g - w;
this->b = c.b - w;
this->w = w;
}

};

inline uint16_t getRGBWsize(uint16_t nleds){
  uint16_t nbytes = nleds * 4;
  if(nbytes % 3 > 0) return nbytes / 3 + 1;
  else return nbytes / 3;
}

#endif
