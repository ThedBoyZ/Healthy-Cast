#include <SPI.h>
#include <Wire.h>
#include <DHT.h>;
////////=Neopixel=///////////
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
//////////=======///////////
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// 'Healthy Cast_oled', 128x32px
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x30, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x47, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x10, 0x08, 0x04, 0x02, 0x26, 0xc4, 0x23, 0xf4, 0x5f, 0x80, 0x6c, 0x42, 0x5d, 0xf2, 0x00, 
  0x04, 0x00, 0x08, 0x02, 0x02, 0x20, 0xc2, 0x20, 0x44, 0x51, 0x00, 0x40, 0x64, 0x01, 0x00, 0x00, 
  0x04, 0x08, 0x38, 0x02, 0x02, 0x29, 0x0a, 0x20, 0x44, 0x49, 0x00, 0x00, 0xa2, 0x01, 0x00, 0x00, 
  0x00, 0x01, 0x8e, 0x00, 0x03, 0xea, 0x0a, 0x20, 0x47, 0xc9, 0x00, 0x00, 0x81, 0xc1, 0x00, 0x00, 
  0x08, 0x06, 0x01, 0x01, 0x02, 0x28, 0x11, 0x20, 0x44, 0x4a, 0x00, 0x01, 0x10, 0x21, 0x00, 0x00, 
  0x08, 0x00, 0x00, 0x81, 0x02, 0x24, 0x11, 0x20, 0x44, 0x46, 0x00, 0x41, 0x10, 0x21, 0x00, 0x00, 
  0x08, 0x0a, 0x00, 0x41, 0x02, 0x27, 0xef, 0xbc, 0x44, 0x44, 0x00, 0x7c, 0xff, 0xc1, 0x00, 0x00, 
  0x08, 0x09, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x08, 0x01, 0x08, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x10, 0xf0, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x10, 0x30, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x10, 0x10, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x10, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x1c, 0x08, 0xc4, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x1e, 0x07, 0x08, 0x00, 0x00, 0x0c, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x1e, 0x00, 0x08, 0x00, 0x00, 0x70, 0x7f, 0xff, 0xf4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0x00, 0x10, 0x00, 0x01, 0x40, 0x1f, 0xfc, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x80, 0x3f, 0x7f, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x18, 0x00, 0x80, 0x00, 0x0a, 0x00, 0x3e, 0xbf, 0xff, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0x0e, 0x00, 0x00, 0x04, 0x00, 0x7c, 0x7f, 0xdf, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xf0, 0x00, 0x00, 0x1c, 0x00, 0x7e, 0xff, 0x9e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x00, 0xff, 0xff, 0xbe, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00
};
//==============================Neopixel====================================
#define PIN 14
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 20 // Time (in milliseconds) to pause between pixels
int x, y, z;
long randNumber=0,rand_Rotation=0;
int ar_x[50]={0},ar_y[50]={0},ar_z[50]={0};
int check_gyro=0;
//==========================================================================
//Constants
#define DHTPIN 27     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//=============================== DHT22 =====================================
const int potPin = 13;
int potValue = 0,lastpotValue = 0;
//Variables
int nub_hudi=0,Detime=0;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float nub_temp=0,coll=0,coll2=0;
//////////////////----Encoder----//////////////////
int counter = 0; //// Value 
int currentStateCLK;
int lastStateCLK;
String currentDir =""; ////
unsigned long lastButtonPress = 0;
////////////////////////////////////////////////////
#define Delaybutton 50
int check=0;
int runn=0;
bool reading;
bool ButtonState = LOW;
bool lastButtonState = LOW;
unsigned long long int lastDebounceTime;
unsigned long period_2 = 50; //ระยะเวลาที่ต้องการรอ
unsigned long cooldown = 0,cooldown2 = 0,cooldown3 = 0; //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop
int check_L=1; 
unsigned long period_time = 1000; //ระยะเวลาที่ต้องการรอ
unsigned long last_time = 0; //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop
///////////////--Heartbeat--//////////////////
int sensorPin = 12, check_H = 0;
double alpha = 0.75;
int period = 100;
double change = 0;
double minval = 0;
/////////////////////////////////////////////
void setup() {
  pinMode(5,INPUT);
  Serial.begin(9600);
  pixels.begin();
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(0, 0, myBitmap, 128, 32, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  // Clear the buffer
}
///////////// DebounceTime /////////////
void debounce(){
  reading = digitalRead(5);
  if(reading != ButtonState && runn==0){
    lastDebounceTime = millis();
    runn=1;
  }
  if(millis() - lastDebounceTime > Delaybutton && runn==1){
    if(ButtonState!=reading){
      lastButtonState=ButtonState;
      ButtonState=reading;
    }
    runn=0;
  }
}
//////////////////////////////////////////
int key=0,key_L=1,i=4,j=59,Mode=0;
int rawValue[50]={0},state_heart=60,sum=0,nub=1;
int Blue=255,change_N=0;
void loop() {
  if(check==0){
  delay(5000);
  }
  debounce(); 
  Serial.println(digitalRead(5));
  if(digitalRead(5) == LOW && key==0){
    Mode++;
    if(Mode>3){
      Mode=1;
    }
    key=1;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(Mode==1){
   static double oldValue = 0;
  static double oldChange = 0;
  Neopixel_Heart();
   if((analogRead(sensorPin)-50 >= state_heart) && (analogRead(sensorPin)-50<=120)){
  for(int i=0;i<40;i++){
    rawValue[i] = analogRead(sensorPin)-60;
  Serial.print("raw[");
  Serial.print(i);
  Serial.print("] = ");
  Serial.println(rawValue[i]);
    delay(70);
  if(i>1){
   if(((rawValue[i]-rawValue[i-1])<=10 ) && ((rawValue[i]-rawValue[i-1])>=-10)){
       sum = sum + rawValue[i];
       nub++;
    }
   else if(rawValue[i]-rawValue[i-1]>20){
      Serial.println("==================================");
      Serial.print("Posi");
      Serial.println("==================================");
 //    state_heart = 60+(rawValue[i]-rawValue[i-1])/2;
       sum = 0;
       nub = 1;
   }
   else if((rawValue[i]-rawValue[i-1]<-20)){
      Serial.println("==================================");
      Serial.print("Nega");
      Serial.println("==================================");
       state_heart = 60;
       sum = 0;
       nub = 1;
   }
  }
 }
 j = j-1;
  sum = sum/nub;
  pixels.clear();
  if(sum>=60 && sum <=120){
      Serial.println("==================================");
      Serial.print("sum = ");
      Serial.println(sum);
      Serial.println("==================================");
      pixels.setBrightness(0);
      pixels.show();
      delay(3000);
      j = j-3;
  }
  nub=1;
  state_heart = 60; 
 }
 delay(100);
 check_H++;
 if(check_H==10){
  check_H = 0;
  j--;
 }
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(70, 24);
    display.print(" : ");
    display.print(sum);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else if(Mode==2){
  if(Detime==4000){
   Thermo();
   j = j-3;
   Detime=0;
  }
  potValue = analogRead(potPin);
  Serial.println(potValue); 
  if(potValue >= 0 && potValue <= 2047){
      pixels.setBrightness(0);
      pixels.show();
      if ((potValue - lastpotValue > 100) && nub_hudi>=-20 ){
        nub_hudi = nub_hudi - (potValue - lastpotValue)/100;     //////// Humidity_decrese
      } 
      else if((lastpotValue - potValue > 70) && nub_hudi<0){
        nub_hudi = nub_hudi + (lastpotValue - potValue)/100;     //////// Humidity_increse
      }
    if(potValue<=20 && lastpotValue<=28){
      nub_hudi = 0;     //////// Humidity_increse
      pixels.setBrightness(0);
      pixels.show();
    }
    if(nub_hudi>=0){
      nub_hudi=0;
    }
      nub_temp = 0;
  }
  else if(potValue > 2047 && potValue <= 4095){
      pixels.setBrightness(8);
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(255, 140, 0));
        pixels.show();
      }
      coll=potValue;
      coll2=lastpotValue;
       if ((potValue - lastpotValue > 68) && nub_temp>=-3){
          nub_temp = nub_temp - ((coll - coll2)/680);     //////// Humidity_decrese
        } 
       else if((lastpotValue - potValue > 35) && nub_temp<0){
          nub_temp = nub_temp + ((coll2 - coll)/680);     //////// Humidity_increse
        }
    if(nub_temp<=-3 || potValue >= 4094){
      nub_temp=-3;
    }
  }
      Serial.print("Hudi = ");
      Serial.print(nub_hudi);
      Serial.print(" ||  Temp = ");
      Serial.println(nub_temp);
      delay(200);
     lastpotValue = potValue; ///// laststate = state
      Detime+=200;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else if(Mode==3){
 if(randNumber == 0 && rand_Rotation ==0){
        pixels.setBrightness(0);
        pixels.show();
    randNumber = random(1, 4);
    rand_Rotation = random(1, 3);
    Serial.print("rand = ");
    Serial.print(randNumber);
    Serial.print("|| Ro = ");
    Serial.println(rand_Rotation);
  }  
  if(randNumber == 1){  //===============> Mode X Rotation
    if(rand_Rotation == 1){   // ไปด้านซ้าย
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.println(">");
    Serial.print("accelerations is (Left) : ");
    x = analogRead(15); 
    z = analogRead(4);
    Serial.print(x, DEC); 
    Serial.print(" , ");
    Serial.println(z, DEC); 
       if((x >= 1400 && x<=1720) && (z >=1600 && z<=2000)){
      for(int i=0;i<30;i++){
        x = analogRead(15);
        z = analogRead(4);
        ar_x[i] = x;
        ar_z[i] = z;
        Serial.print("ar_x[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_x[i]);
        Serial.print(" # , # ");
        Serial.println(ar_z[i]);
        delay(100);
      if(i>=0){
        if((x >= 1400 && x<=1720) && (z >=1600 && z<=2000)){
          check_gyro++;
        }     
   }
 }
 j = j-3;
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_x_left");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
      pixels.clear();
      pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
        delay(3000);
        j = j-3;
    }
   }
    check_gyro=0;
  }
    if(rand_Rotation == 2){ // ไปด้านขวา
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.println("<");
    Serial.print("accelerations is (Right) : ");
    x = analogRead(15); 
    z = analogRead(4);
    Serial.print(x, DEC); 
    Serial.print(" , ");
    Serial.println(z, DEC); 
       if((x >= 2150 && x<=2300) && (z >=1700 && z<=1900)){
      for(int i=0;i<30;i++){
        x = analogRead(15);
        z = analogRead(4);
        ar_x[i] = x;
        ar_z[i] = z;
        Serial.print("ar_x[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_x[i]);
        Serial.print(" # , # ");
        Serial.println(ar_z[i]);
        delay(100);
      if(i>=0){
        if((x >= 2150 && x<=2300) && (z >=1700 && z<=1900)){
          check_gyro++;
        }     
   }
 }
 j = j-3;
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_x_right");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
    pixels.clear();
    pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
        delay(3000);
        j = j-3;
    }
   }
    check_gyro=0;
  }
 }
  if(randNumber == 2){   //===============> Mode Y Rotation
    if(rand_Rotation == 1){ // ขึ้นบน
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.println("A");
    Serial.print("accelerations is (Up) : ");
    y = analogRead(2);
    Serial.print(y, DEC); 
    Serial.println(" ");
       if(y >= 300 && y <= 340){
      for(int i=0;i<30;i++){
        y = analogRead(2);
        ar_y[i] = y;
        Serial.print("ar_y[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_y[i]);
        delay(100);
      if(i>=0){
        if(ar_y[i] >= 300 && ar_y[i] <=350){
          check_gyro++;
        }     
   }
 }
 j = j-3;
  if(check_gyro>=15){ 
      Serial.println("==================================");
      Serial.println("Success_y_Up");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
      pixels.clear();
      pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
        delay(3000);
        j = j-3;
    }
   }
    check_gyro=0;
  }
    if(rand_Rotation == 2){ // ลงล่าง
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.println("V"); 
    Serial.print("accelerations is (Down) : ");
    y = analogRead(2);
    Serial.print(y, DEC); 
    Serial.println(" ");
       if(y >= 450 && y <= 600){
      for(int i=0;i<30;i++){
        y = analogRead(2);
        ar_y[i] = y;
        Serial.print("ar_y[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_y[i]);
        delay(100);
      if(i>=0){
        if(ar_y[i] >= 450 && ar_y[i] <=600){
          check_gyro++;
        }     
   }
 }
 j = j-3;
  if(check_gyro>=15){ 
      Serial.println("==================================");
      Serial.println("Success_y_Down");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
      pixels.clear();
      pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
        delay(3000);
        j = j-3;
    }
   }
    check_gyro=0;
  }
}
  if(randNumber == 3){ // =============> Mode Z Rotation
    if(rand_Rotation == 1){  // เฉียงซ้าย
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.println("/"); 
   display.display();      // Show initial text 
    Serial.print("accelerations is (Slant to left) : ");
    x = analogRead(15); 
    y = analogRead(2);  
    Serial.print(x, DEC); 
    Serial.print(" , ");
    Serial.println(y, DEC); 
       if((y >= 420 && y <= 490) && (x >= 1470 && x<=1650)){
      for(int i=0;i<30;i++){
        x = analogRead(15);
        y = analogRead(2);
        ar_x[i] = x;
        ar_y[i] = y;
        Serial.print("ar_z =[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_x[i]);
        Serial.print(" ^ , ^ ");
        Serial.println(ar_y[i]);
        delay(100);
      if(i>=0){
        if((y >= 420 && y <= 490) && (x >= 1470 && x<=1650)){
          check_gyro++;
        }     
   }
 }
   j = j-3;
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_z_(Slant&left)");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
      pixels.clear();
      pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
       delay(3000);
       j = j-3;
    }
   }
    check_gyro=0;
  }  
   if(rand_Rotation == 2){
   display.setTextSize(2); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(100, 12);
   display.print("\\"); 
    Serial.print("accelerations is (Slant to Right): ");  // เฉียงขวา
    x = analogRead(15); 
    y = analogRead(2);  
    Serial.print(x, DEC); 
    Serial.print(" , ");
    Serial.println(y, DEC); 
       if((y >= 300 && y <= 370) && (x >= 2000 && x<=3000)){
      for(int i=0;i<30;i++){
        x = analogRead(15);
        y = analogRead(2);
        ar_x[i] = x;
        ar_y[i] = y;
        Serial.print("ar_z =[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(ar_x[i]);
        Serial.print(" ^ , ^ ");
        Serial.println(ar_y[i]);
        delay(100);
      if(i>=0){
        if((y >= 300 && y <= 370) && (x >= 2000 && x<=3000)){
          check_gyro++;
        }     
   }
 }
 j = j-3;
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_z_(Slant&Right)");
      display.clearDisplay(); //for Clearing the display
      Serial.println("==================================");
      randNumber = 0;
      rand_Rotation = 0;
      pixels.clear();
      pixels.setBrightness(10);
      for(int i=0; i<8; i++) {
        pixels.setPixelColor(i, pixels.Color(240, 0, 40));
      }
        pixels.show();
        delay(3000);
        j = j-3;
    }
   }
    check_gyro=0;
  }
 } 
}  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 if( millis() - last_time > period_time && key_L==1) {
     Oled_show();
     last_time = millis(); //เซฟเวลาปัจจุบันไว้เพื่อรอจนกว่า millis() จะมากกว่าตัวมันเท่า period
     key_L=0;
 }
 if(check_L==0){
if( millis() - cooldown > 1000 && key_L==0) { 
   display.display();      // Show initial text
   display.invertDisplay(true);
   Serial.println("Right");
   cooldown = millis();
}
 if( millis() - cooldown2 > 1500) {
   display.display();      // Show initial text 
   display.invertDisplay(false);
   key_L=1;
   check_L=1;
   cooldown2 = millis();
      if(j<=0){
       i--;
       j=59;
      }
     else{
       j--;
    }
  }
 }
 Serial.print("Mode = ");
 Serial.println(Mode);
if(digitalRead(5) == HIGH && key==1){
  key=0;
 }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void Oled_show(){
unsigned long period_3 = 50; //ระยะเวลาที่ต้องการรอ
unsigned long cooldown3 = 0; //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop
   display.clearDisplay(); //for Clearing the display
   display.setTextSize(1); // Draw 2X-scale text
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(12, 24);
  if(Mode==1){
   display.println("Heartbeat"); 
  }
  else if(Mode==2){
   display.println("Temp");
  }
  else if(Mode==3){
   display.println("Gyro");     
  }
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 8);
  if((j>=10 && j<=60)&& check!=0){
     display.print(i);
     display.print(F(" : "));
     display.println(j);
  }
  else if(j<10 && check!=0){
     display.print(i);
     display.print(F(" : 0"));    
     display.println(j);
  }
  if(check==0){
      display.clearDisplay(); //for Clearing the display
      display.print(i+1);
      display.println(F(" : 00"));      
       j++;
       check=1;
  }
  if(i<=0 && j<=0){
    i=4;
    j=59;
    check=0;
  }  
 check_L=0;
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

void Thermo(){
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    display.clearDisplay(); //for Clearing the display
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(50, 0);
    display.print("T : ");
    display.setCursor(70, 0);
    display.print(temp+nub_temp);
    display.setCursor(0, 24);
    display.print("H : ");
    display.setCursor(30, 24);
    display.print(hum+nub_hudi);
    display.display();
    delay(3000); //Delay 1.5 sec.
}
