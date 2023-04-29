/*int sensorPin = A0; // select the input pin for the potentiometer
int ledPin = 12; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() {
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}
void loop() {
sensorValue = analogRead(sensorPin); // read the value from the sensor:
Serial.println(sensorValue); // turn the ledPin on
digitalWrite(ledPin, HIGH);
// stop the program for <sensorValue> milliseconds:
delay(100);
// turn the ledPin off:
digitalWrite(ledPin, LOW);
// stop the program for for <sensorValue> milliseconds:
delay(50);
}
*/
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = A0;

int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(50);
}
