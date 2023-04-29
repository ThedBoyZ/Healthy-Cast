#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 14
#define NUMPIXELS 8


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 80 // Time (in milliseconds) to pause between pixels
int Green=255,Red=0,Blue=255,change_N=0;
int sensorPin = 12;
double alpha = 0.75;
int period = 100;
double change = 0;
double minval = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin();
}
int rawValue[50]={0},state_heart=60,sum=0,nub=1;
void loop() {
  static double oldValue = 0;
  static double oldChange = 0;
  Neopixel_Heart();
   if((analogRead(sensorPin)-10 >= state_heart) && (analogRead(sensorPin)-10<=120)){
  for(int i=0;i<50;i++){
    rawValue[i] = analogRead(sensorPin)-40;
  Serial.print("raw[");
  Serial.print(i);
  Serial.print("] = ");
  Serial.println(rawValue[i]);
    delay(100);
  if(i>1){
   if(((rawValue[i]-rawValue[i-1])<=10 ) && ((rawValue[i]-rawValue[i-1])>=-10)){
       sum = sum + rawValue[i];
       nub++;
    }
   else if(rawValue[i]-rawValue[i-1]>5){
      Serial.println("==================================");
      Serial.print("Posi");
      Serial.println("==================================");
 //    state_heart = 60+(rawValue[i]-rawValue[i-1])/2;
       sum = 0;
       nub = 1;
   }
   else if((rawValue[i]-rawValue[i-1]<-5)){
      Serial.println("==================================");
      Serial.print("Nega");
      Serial.println("==================================");
       state_heart = 60;
       sum = 0;
       nub = 1;
   }
  }
 }
  sum = sum/nub;
  pixels.clear();
  if(sum>=60 && sum <=120){
      Serial.println("==================================");
      Serial.print("sum = ");
      Serial.println(sum);
      Serial.println("==================================");
      pixels.setBrightness(0);
      pixels.show();
      delay(4000);
  }
  sum=0;  
  nub=1;
  state_heart = 60; 
 }
 delay(100);
}

void Neopixel_Heart(){
pixels.setBrightness(10);
pixels.setPixelColor(0, pixels.Color(change_N, 0, Blue));
pixels.setPixelColor(1, pixels.Color(change_N-74, 0, Blue));
pixels.setPixelColor(2, pixels.Color(change_N-141, 0, Blue));
pixels.setPixelColor(3, pixels.Color(change_N-208, 0, Blue));
pixels.setPixelColor(4, pixels.Color(change_N-270, 0, Blue));
pixels.setPixelColor(5, pixels.Color(change_N-333, 0, Blue));
pixels.setPixelColor(6, pixels.Color(change_N-421, 0, Blue));
pixels.setPixelColor(7, pixels.Color(change_N-225, 0, Blue));
change_N+=51;
if(change_N>=255){
  change_N=0;
}
pixels.show();
}
