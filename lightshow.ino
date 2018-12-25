#include "IRremote.h"
#include <FastLED.h>

#define NUM_LEDS 60
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
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


bool on = false;


void translateIR() {

  if (on) {
    set_black();
  } else {
    set_white();
  }

  on = !on;

  // switch(results.value) {
  //   case 0xFF30CF: Serial.println(" 1");    break;
  //   case 0xFF18E7: Serial.println(" 2");    break;
  //   case 0xFF7A85: Serial.println(" 3");    break;
  //
  //   default:
  //     Serial.println("unknown input");
  // }
}


void set_black() {
  for(int led = 0; led < NUM_LEDS; led = led + 1) {
     leds[led] = CRGB::Black;
  }

  FastLED.show();
}


void set_white() {
  for(int led = 0; led < NUM_LEDS; led = led + 1) {
     leds[led] = CRGB::White;
  }

  FastLED.show();
}


void set_blue() {

}


void set_red() {

}


void set_green() {

}
