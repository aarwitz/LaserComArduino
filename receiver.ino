#define BUFFER_SIZE 384  
int BUFFER_WRITE_IDX = 0;           // Index of the next element of buff to write to 
int BUFFER_READ_IDX = 0;            // Index of the next element of buff to read from
int sensorPin = A0;                 // select the input pin for the PV cell
int sensorValue = 0;                // variable to store the value coming from the sensor
double average;

bool state;
bool cd = false;
//int buff[BUFFER_SIZE];
int count = 0;
/*
 
t = 0 starts at first 0 outputted by laser (the first 1 is an initialzier, so occurs at t=-1)

       ___     ___     ___         ___     ___ ___    
      |   |___|   |___|   |___ ___|   |___|       |
 tx = 1   0   1   0   1   0   0   1   0   1   1
 rx =   1   0   1   0   1   0   0   1   0   1   1
  t =   0   1   2   3   4   5   6   7   8   9  


       ___     ___     ___         ___     ___ ___    
      |   |___|   |___|   |___ ___|   |___|       |
 tx = 1   0   1   0   1   0   0   1   0   1   1
 rx =       0   1   0   1   0   0   1   0   1   1
  t =     0   1   2   3   4   5   6   7   8   9  


*/
//14201

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  // Get the initial reading for ambient light
  sensorValue = analogRead(sensorPin);
  average = sensorValue;
  delay(1000);

  wait_for_first_1_bit();   // This is Arduino startup (laser automatically lights up on startup)
  delay(1000);
  average = analogRead(sensorPin);  // get ambient lighting (laser off)
  delay(500);
  wait_for_first_1_bit();   // This is first 1 bit sent by laser
  delay(750);   // A cycle and a half, to read in the middle of each cycle
                  // "sample the waveform at intervals" in between the laser command
  Serial.println("L.");
}


//Read  1
//Write 1
void loop() {
    // put your main code here, to run repeatedly:
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    //Serial.println(sensorValue);
    // Serial.print("sensorValue: "); 
    //Serial.println(sensorValue);
    //Serial.print(" bit: ");
    bool isHigh = isSignalHigh(average, sensorValue);
    Serial.println(isHigh);
   // Serial.print(isHigh);
   // buff[BUFFER_WRITE_IDX] = isHigh ? 1 : 0;
    //Serial.println(BUFFER_WRITE_IDX);
    //Serial.println(buff[BUFFER_WRITE_IDX]);
    // Write 1 (symbolizing HIGH or the laser being in on state) into the buffer
        // Increment the index for writing to the buffer
//    BUFFER_WRITE_IDX++;
//  
//    if(count%7==0){
//      //Serial.println(count);
//      uint8_t byte =0;
//      for(int i = 0;i<8;i++){
//       // Serial.println(BUFFER_READ_IDX + i);
//       // Serial.println(buff[BUFFER_READ_IDX + i]);
//         byte |= buff[BUFFER_READ_IDX + i] << (7 - i);
//      }
     // Serial.println();
      
      //    print
         
     //     }
     //     Serial.println();
//          Serial.print("message = (char)byte: ");
       //   Serial.println((char)byte);
//      BUFFER_READ_IDX+=8;
//     }
//    count++;
    delay(500);   // the above delay in setup should be 1.5x of this
}


boolean isSignalHigh(double average, double sample) {
  /* 
    *  returns true if sensor reading is higher than rolling average,
    *  returns false otherwise
  */
    if (sample - average > 35)
       return true;
    return false; 
}

void wait_for_first_1_bit() {
  /* 
   *  While loop until laser strikes PV cpell, insert first value (by defintion a 1) into the buffer.
   *  After the first 1 is received, the programs' loop timers should be synchronized.
   */
  bool isHigh = false;
  int count = 0;
  while(!isHigh) {
      // Take average of ambient light until laser turns on
      if(count%2500==0){Serial.println("Waiting for laser: ");}
      sensorValue = analogRead(sensorPin);
      if (isSignalHigh(average,sensorValue)) {
          // Write 1 (symbolizing HIGH or the laser being in on state) into the buffer
          isHigh = true;
          //Serial.println(isHigh);
      }
      count++;
  }
  //delay(50); // half cycle delay here
//  Serial.print("(char)byte: ");
//  Serial.println((char)
}