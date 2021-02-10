int ledPin = 4;
float freq = 17;

void setup() {
  pinMode(ledPin, OUTPUT);
//  Serial.begin(115200);               
}

float periodo() {
//  float peri = 1/freq;
//  float halfer = peri/2;
//  float millisec = halfer*1000;
//  return millisec;

  return ((1/freq)/2)*1000;
}

float blinkus(){
  digitalWrite(ledPin, HIGH);    
  delay(periodo());                       
  digitalWrite(ledPin, LOW);     
  delay(periodo());   
}

void loop() {
  blinkus();        
}
