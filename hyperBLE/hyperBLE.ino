

//Data expected:
// #1 ... tuns ON
// #2 ... turns oFF
// #f:340 ... FREQ to 340 

bool lightsON = false;
float freq = 17;
int ledPin = 4;


void setup() {
  Serial.begin(115200);                
  pinMode(ledPin, OUTPUT);
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

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  
  while (Serial.available() > 0 ) {

    String str = Serial.readString();

    
    if (str.indexOf("#1") > -1) {
      lightsON = true;
      Serial.write("lightsON");
    }

    if (str.indexOf("#0") > -1) {
      lightsON = false;
      Serial.write("lightsOFF");
    }

    if (str.indexOf("#f") > -1) {
      String xval = getValue(str, ':', 1);
      //      xval = "x:"+xval;
      //      const char* s;
      //        s= xval.c_str();
      //       Serial.write(s);
      freq = xval.toInt();
      Serial.write("freq set");
    }

  }

  if (lightsON) {
      blinkus();
  } else {
    digitalWrite(ledPin, HIGH);
  }

}
