#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <FastLED.h>

char auth[] = "QhAo_OlGEAEiRgyTfFAY0AAmCbfWJcJg"; //Unique Blynk Application Code
char ssid[] = "****"; //SSID
char pass[] = "****"; //WiFi Password

#define LED_PIN     13
#define NUM_LEDS    220

CRGB leds[NUM_LEDS];

int IS_ON = 0;
int RED = 10;
int GREEN = 10;
int BLUE = 10;
int BRIGHTNESS = 255;
int MODE = 0;
int SPEED = 8;

void setup()
{
  delay(4000);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  Blynk.begin(auth, ssid, pass);
  
}
uint8_t gHue = 0;
void loop()
{
    Blynk.run();

    if(MODE == 1){
      rainbow();
    }
    else if(MODE == 2){
      rainbowWithGlitter();
    }
    else if(MODE == 3){
      confetti();
    }
    else if(MODE == 4){
      juggle();
    }
    else{
      setAll(RED, GREEN, BLUE);
    }
    
    FastLED.show();
    
    EVERY_N_MILLISECONDS( 20 ) { gHue++; }
    delay(SPEED);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void setAll(int r, int g, int b){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

BLYNK_WRITE(V0){
  //ON OFF
  IS_ON = param.asInt();
  if(IS_ON == 0){
    FastLED.setBrightness(0);
  }
  else{
    FastLED.setBrightness(100);
  }
}

BLYNK_WRITE(V5){
  //Red Slider
  RED = param.asInt() / 4;
}
BLYNK_WRITE(V6){
  //Green Slider
  GREEN = param.asInt() / 4;
}
BLYNK_WRITE(V7){
  //Blue Slider
  BLUE = param.asInt() / 4;
}

BLYNK_WRITE(V9){
  //Brightness Slider
  BRIGHTNESS = param.asInt() / 4;
  FastLED.setBrightness(BRIGHTNESS);
}

BLYNK_WRITE(V2){
  //Mode Selector
  MODE = param.asInt();
}
BLYNK_WRITE(V10){
  //Speed Slider
  SPEED = param.asInt();
}
