#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 14
#define NUMPIXELS 8


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 20 // Time (in milliseconds) to pause between pixels
int x, y, z;
long randNumber=0,rand_Rotation=0;
int ar_x[50]={0},ar_y[50]={0},ar_z[50]={0};
int check_gyro=0;
void setup()
{
Serial.begin(9600);
pixels.begin();
}

void loop()
{
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
    Serial.print("accelerations is (Left) : ");
    x = analogRead(15); 
    z = analogRead(4);
    Serial.print(x, DEC); 
    Serial.print(" , ");
    Serial.println(z, DEC); 
       if((x >= 1470 && x<=1620) && (z >=1700 && z<=1900)){
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
        if((x >= 1470 && x<=1620) && (z >=1800 && z<=2000)){
          check_gyro++;
        }     
   }
 }
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_x_left");
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
    }
   }
    check_gyro=0;
  }
    if(rand_Rotation == 2){ // ไปด้านขวา
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
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_x_right");
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
    }
   }
    check_gyro=0;
  }
 }
  if(randNumber == 2){   //===============> Mode Y Rotation
    if(rand_Rotation == 1){ // ขึ้นบน
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
  if(check_gyro>=15){ 
      Serial.println("==================================");
      Serial.println("Success_y_Up");
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
    }
   }
    check_gyro=0;
  }
    if(rand_Rotation == 2){ // ลงล่าง
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
  if(check_gyro>=15){ 
      Serial.println("==================================");
      Serial.println("Success_y_Down");
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
    }
   }
    check_gyro=0;
  }
}
  if(randNumber == 3){ // =============> Mode Z Rotation
    if(rand_Rotation == 1){  // เฉียงซ้าย
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
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_z_(Slant&left)");
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
    }
   }
    check_gyro=0;
  }  
   if(rand_Rotation == 2){
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
  if(check_gyro>=15){
      Serial.println("==================================");
      Serial.println("Success_z_(Slant&Right)");
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
    }
   }
    check_gyro=0;
  }
 } 
delay(100); // หน่วงเวลา 100 มิลลิวินาที
}
