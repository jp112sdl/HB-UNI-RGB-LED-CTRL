void RGBProgramRainbow(uint8_t speed, uint8_t brightness) {
  static uint8_t startIndex = 0;
  static unsigned long lastmillis = millis();
  if (millis() - lastmillis > speed) {
    startIndex = startIndex + 1;
    for ( int i = 0; i < WSNUM_LEDS; i++) {
      leds[i] = ColorFromPalette( RainbowColors_p, startIndex, brightness, LINEARBLEND);
    }
    lastmillis = millis();
  }
}


void RGBProgramFire(uint8_t brightness) {
  static unsigned long lastmillis = millis();
  if (millis() - lastmillis > 15) {

    static byte heat[WSNUM_LEDS];

    for ( int i = 0; i < WSNUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((FIRE_PROGRAM_COOLING * 10) / WSNUM_LEDS) + 2));
    }

    for ( int k = WSNUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    if ( random8() < FIRE_PROGRAM_SPARKLING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160, 255) );
    }

    for ( int j = 0; j < WSNUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;

      pixelnumber = j;

      leds[pixelnumber] = color;
    }
    lastmillis = millis();
  }
}

void RGBProgramWaterfall (uint8_t brightness) {}

void RGBProgramTVSimulation (uint8_t brightness) {}

