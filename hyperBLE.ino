
bool lightsON = false;
int freq = 220;

void setup() {
  Serial.begin(115200);               //initial the Serial
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  while (Serial.available() > 0 ) {
    String str = Serial.readString();
    if (str.indexOf("#1") > -1) {
      lightsON = true;
    }

    if (str.indexOf("#0") > -1) {
      lightsON = false;
    }

    if (str.indexOf("#f") > -1) {
      String xval = getValue(str, ':', 1);
      //      xval = "x:"+xval;
      //      const char* s;
      //        s= xval.c_str();
      //       Serial.write(s);
      freq = xval.toInt();
    }
  }

  if (lightsON) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(freq);
    digitalWrite(LED_BUILTIN, LOW);
    delay(freq);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

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
