#define LASERPIN 13

// Message we want to send is R
// Binary for R: 01010010


unsigned long previousMillis = 0;
unsigned long currentMillis;


void setup() {
    Serial.begin(9600);
    delay(1000);
    pinMode (LASERPIN, OUTPUT);
}

void loop() {
    //    R        e        d        s        t        o        n        e                 L        a        b        s
    //"01010010 01100101 01100100 01110011 01110100 01101111 01101110 01100101 00100000 01001100 01100001 01100010 01110011";
    // Remove spaces between bytes
    String bits = "01010010011001010110010001110011011101000110111101101110011001010010000001001100011000010110001001110011";
    // For each bit in the string bits, turn laser on for 1 and off for 0
    for(int i = 0; i < bits.length(); i++) {
        uint8_t laserOutput;
        if (bits[i] == '0') {
          Serial.println("zero");
          laserOutput = LOW;
        }
        else {
          Serial.println("one");
          laserOutput = HIGH;
        }
        Serial.println(bits[i]);
        digitalWrite(LASERPIN, laserOutput);
        currentMillis = millis();
        previousMillis = currentMillis;
        while (currentMillis - previousMillis < 100) //delay here
        { 
            currentMillis = millis();
        }
    }
  
    digitalWrite(LASERPIN, LOW);
  
   // delay(1000);
}