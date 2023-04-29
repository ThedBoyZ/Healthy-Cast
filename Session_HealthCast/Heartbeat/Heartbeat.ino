int sensorPin = A0;
double alpha = 0.75;
int period = 100;
double change = 0;
double minval = 0;

void setup() {
  Serial.begin(9600);
}
int rawValue[50]={0},state_heart=60,sum=0,nub=1;
void loop() {
  static double oldValue = 0;
  static double oldChange = 0;
   if((analogRead(sensorPin) >= state_heart) && (analogRead(sensorPin)<=120)){
  for(int i=0;i<50;i++){
    rawValue[i] = analogRead(sensorPin);
  Serial.print("raw[");
  Serial.print(i);
  Serial.print("] = ");
  Serial.println(rawValue[i]);
    delay(50);
  if(i>1){
   if(((rawValue[i]-rawValue[i-1])<=5 ) && ((rawValue[i]-rawValue[i-1])>=-5)){
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
}
