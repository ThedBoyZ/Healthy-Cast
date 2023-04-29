#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 14
#define NUMPIXELS 12


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int Green=140,Red=10,Blue=155;
void setup() {
pixels.begin();
}

void loop() {
pixels.clear();
pixels.setBrightness(10);
for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
pixels.setPixelColor(i, pixels.Color(Red, Green, Blue));
}
Red=+65;
Green-=40;
Blue-=25;
if(Green<=0){
   Green=255;
}
if(Red>=255){
  Green=255;
}
if(Blue<=0){
   Blue=255;
}
pixels.show();
delay(500);
}
/* #define PIN D2
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
pixels.begin();
}

void loop()
{
int delayval = 500;
for (int i = 0; i < NUMPIXELS; i++)
{
pixels.setPixelColor(i, pixels.Color(0, 255, 0));
pixels.show();
delay(delayval);
pixels.setPixelColor(i, pixels.Color(255, 0, 0));
pixels.show();
delay(delayval);
pixels.setPixelColor(i, pixels.Color(0, 0, 255));
pixels.show();
delay(delayval);
}
} */
