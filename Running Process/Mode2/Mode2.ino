#include <DHT.h>;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 14
#define NUMPIXELS 8


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 80 // Time (in milliseconds) to pause between pixels
//Constants
#define DHTPIN 27     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

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
void setup()
{
  Serial.begin(9600);
  dht.begin();
  pixels.begin();
  delay(1000);
}

void loop()
{
  if(Detime==4000){
   Thermo();
   Detime=0;
  }
  potValue = analogRead(potPin);
  Serial.println(potValue); 
  if(potValue >= 10 && potValue <= 2047){
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

void Thermo(){
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(3000); //Delay 3 sec.
}
