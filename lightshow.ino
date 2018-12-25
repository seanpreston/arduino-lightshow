#include "IRremote.h"
#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    50
// #define NUM_LEDS    1
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver
}


void loop() {

  if (irrecv.decode(&results)) {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}


void translateIR() {
  Serial.println("translateIR");

  random_palette();

  // switch(results.value) {
  //   case 0xFF30CF: Serial.println(" 1");    break;
  //   case 0xFF18E7: Serial.println(" 2");    break;
  //   case 0xFF7A85: Serial.println(" 3");    break;
  //   // case 0xFF629D: Serial.println(" FORWARD"); break;
  //   // case 0xFF22DD: Serial.println(" LEFT");    break;
  //   // case 0xFF02FD: Serial.println(" -OK-");    break;
  //   // case 0xFFC23D: Serial.println(" RIGHT");   break;
  //   // case 0xFFA857: Serial.println(" REVERSE"); break;
  //   // case 0xFF6897: Serial.println(" 1");    break;
  //   // case 0xFF9867: Serial.println(" 2");    break;
  //   // case 0xFFB04F: Serial.println(" 3");    break;
  //   // case 0xFF10EF: Serial.println(" 7");    break;
  //   // case 0xFF38C7: Serial.println(" 8");    break;
  //   // case 0xFF5AA5: Serial.println(" 9");    break;
  //   // case 0xFF42BD: Serial.println(" *");    break;
  //   // case 0xFF4AB5: Serial.println(" 0");    break;
  //   // case 0xFF52AD: Serial.println(" #");    break;
  //   // case 0xFFFFFFFF: Serial.println(" REPEAT");break;
  //
  //   default:
  //     Serial.println("unknown input");
  // }
}


void random_palette() {
  Serial.println("random_palette");
  FastLED.clear();

  // CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  // CRGB green  = CHSV( HUE_GREEN, 255, 255);
  // CRGB black  = CRGB::Black;
  //
  // currentPalette = CRGBPalette16(
  //                                green,  green,  black,  black,
  //                                purple, purple, black,  black,
  //                                green,  green,  black,  black,
  //                                purple, purple, black,  black );
  //
  // for(int i = 0; i < 16; i++) {
  //     currentPalette[i] = CHSV( random8(), 255, random8());
  // }
  //
  // static uint8_t startIndex = 0;
  // startIndex = startIndex + 1; /* motion speed */
  //
  // FillLEDsFromPaletteColors(startIndex);
  //
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 255);
  }
  FastLED.show();
  // FastLED.delay(1000 / UPDATES_PER_SECOND);
}


void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  Serial.println("FillLEDsFromPaletteColors");
  uint8_t brightness = 255;

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
