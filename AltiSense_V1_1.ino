/*
AltiSense Version 1.1

software for measuring distance with a TeraTanger Evo 60m TOF sensor, displaying distance
on an LCD display, saving data on an SD card and playing back audio callout via DFPlayer 
mini MP3 module

last changed on 05.10.2021
translated to english on 14.08.2022
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define SENSOR_ADDR 0x31                    // define sensor address

LiquidCrystal_I2C lcd(0x27, 16, 2);         // declare lcd object

File myFile;                                // declare File object

SoftwareSerial mySoftwareSerial(5,6);       // (RX,TX)  declare SoftwareSerial object
DFRobotDFPlayerMini myDFPlayer;             // declare DFPlayer object for mp3 control

// custom char set definition
const char custom[][8] PROGMEM = { 
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 }, // char 1 
      { 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }, // char 2 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03 }, // char 3 
      { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 4 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C, 0x18 }, // char 5 
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F }, // char 6 
      { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 7 
      { 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }  // char 8 
};

// Definition big chars

const char bigChars[][8] PROGMEM = {
      { 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Space
      { 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // !
      { 0x05, 0x05, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00 }, // "
      { 0x04, 0xFF, 0x04, 0xFF, 0x04, 0x01, 0xFF, 0x01 }, // #
      { 0x08, 0xFF, 0x06, 0x07, 0xFF, 0x05, 0x00, 0x00 }, // $
      { 0x01, 0x20, 0x04, 0x01, 0x04, 0x01, 0x20, 0x04 }, // %
      { 0x08, 0x06, 0x02, 0x20, 0x03, 0x07, 0x02, 0x04 }, // &
      { 0x05, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '
      { 0x08, 0x01, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00 }, // (
      { 0x01, 0x02, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00 }, // )
      { 0x01, 0x04, 0x04, 0x01, 0x04, 0x01, 0x01, 0x04 }, // *
      { 0x04, 0xFF, 0x04, 0x01, 0xFF, 0x01, 0x00, 0x00 }, // +
      { 0x20, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // 
      { 0x04, 0x04, 0x04, 0x20, 0x20, 0x20, 0x00, 0x00 }, // -
      { 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // .
      { 0x20, 0x20, 0x04, 0x01, 0x04, 0x01, 0x20, 0x20 }, // /
      { 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00 }, // 0
      { 0x01, 0x02, 0x20, 0x04, 0xFF, 0x04, 0x00, 0x00 }, // 1
      { 0x06, 0x06, 0x02, 0xFF, 0x07, 0x07, 0x00, 0x00 }, // 2
      { 0x01, 0x06, 0x02, 0x04, 0x07, 0x05, 0x00, 0x00 }, // 3
      { 0x03, 0x04, 0xFF, 0x20, 0x20, 0xFF, 0x00, 0x00 }, // 4
      { 0xFF, 0x06, 0x06, 0x07, 0x07, 0x05, 0x00, 0x00 }, // 5
      { 0x08, 0x06, 0x06, 0x03, 0x07, 0x05, 0x00, 0x00 }, // 6
      { 0x01, 0x01, 0x02, 0x20, 0x08, 0x20, 0x00, 0x00 }, // 7
      { 0x08, 0x06, 0x02, 0x03, 0x07, 0x05, 0x00, 0x00 }, // 8
      { 0x08, 0x06, 0x02, 0x07, 0x07, 0x05, 0x00, 0x00 }, // 9
      { 0xA5, 0xA5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // :
      { 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ;
      { 0x20, 0x04, 0x01, 0x01, 0x01, 0x04, 0x00, 0x00 }, // <
      { 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x00, 0x00 }, // =
      { 0x01, 0x04, 0x20, 0x04, 0x01, 0x01, 0x00, 0x00 }, // >
      { 0x01, 0x06, 0x02, 0x20, 0x07, 0x20, 0x00, 0x00 }, // ?
      { 0x08, 0x06, 0x02, 0x03, 0x04, 0x04, 0x00, 0x00 }, // @
      { 0x08, 0x06, 0x02, 0xFF, 0x20, 0xFF, 0x00, 0x00 }, // A
      { 0xFF, 0x06, 0x05, 0xFF, 0x07, 0x02, 0x00, 0x00 }, // B
      { 0x08, 0x01, 0x01, 0x03, 0x04, 0x04, 0x00, 0x00 }, // C
      { 0xFF, 0x01, 0x02, 0xFF, 0x04, 0x05, 0x00, 0x00 }, // D
      { 0xFF, 0x06, 0x06, 0xFF, 0x07, 0x07, 0x00, 0x00 }, // E
      { 0xFF, 0x06, 0x06, 0xFF, 0x20, 0x20, 0x00, 0x00 }, // F
      { 0x08, 0x01, 0x01, 0x03, 0x04, 0x02, 0x00, 0x00 }, // G
      { 0xFF, 0x04, 0xFF, 0xFF, 0x20, 0xFF, 0x00, 0x00 }, // H
      { 0x01, 0xFF, 0x01, 0x04, 0xFF, 0x04, 0x00, 0x00 }, // I
      { 0x20, 0x20, 0xFF, 0x04, 0x04, 0x05, 0x00, 0x00 }, // J
      { 0xFF, 0x04, 0x05, 0xFF, 0x20, 0x02, 0x00, 0x00 }, // K
      { 0xFF, 0x20, 0x20, 0xFF, 0x04, 0x04, 0x00, 0x00 }, // L
      { 0x08, 0x03, 0x05, 0x02, 0xFF, 0x20, 0x20, 0xFF }, // M
      { 0xFF, 0x02, 0x20, 0xFF, 0xFF, 0x20, 0x03, 0xFF }, // N
      { 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00 }, // 0
      { 0x08, 0x06, 0x02, 0xFF, 0x20, 0x20, 0x00, 0x00 }, // P
      { 0x08, 0x01, 0x02, 0x20, 0x03, 0x04, 0xFF, 0x04 }, // Q
      { 0xFF, 0x06, 0x02, 0xFF, 0x20, 0x02, 0x00, 0x00 }, // R
      { 0x08, 0x06, 0x06, 0x07, 0x07, 0x05, 0x00, 0x00 }, // S
      { 0x01, 0xFF, 0x01, 0x20, 0xFF, 0x20, 0x00, 0x00 }, // T
      { 0xFF, 0x20, 0xFF, 0x03, 0x04, 0x05, 0x00, 0x00 }, // U
      { 0x03, 0x20, 0x20, 0x05, 0x20, 0x02, 0x08, 0x20 }, // V
      { 0xFF, 0x20, 0x20, 0xFF, 0x03, 0x08, 0x02, 0x05 }, // W
      { 0x03, 0x04, 0x05, 0x08, 0x20, 0x02, 0x00, 0x00 }, // X
      { 0x03, 0x04, 0x05, 0x20, 0xFF, 0x20, 0x00, 0x00 }, // Y
      { 0x01, 0x06, 0x05, 0x08, 0x07, 0x04, 0x00, 0x00 }, // Z
      { 0xFF, 0x01, 0xFF, 0x04, 0x00, 0x00, 0x00, 0x00 }, // [
      { 0x01, 0x04, 0x20, 0x20, 0x20, 0x20, 0x01, 0x04 }, // Backslash
      { 0x01, 0xFF, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00 }, // ]
      { 0x08, 0x02, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00 }, // ^
      { 0x20, 0x20, 0x20, 0x04, 0x04, 0x04, 0x00, 0x00 }  // _
};

byte col,row,nb=0,bc=0;
byte bb[8];                                               // byte buffer for reading from PROGMEM



// table for cyclic redundancy checks of "crc8" function
static const uint8_t crc_table[] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31,
    0x24, 0x23, 0x2a, 0x2d, 0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d, 0xe0, 0xe7, 0xee, 0xe9,
    0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1,
    0xb4, 0xb3, 0xba, 0xbd, 0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea, 0xb7, 0xb0, 0xb9, 0xbe,
    0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16,
    0x03, 0x04, 0x0d, 0x0a, 0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a, 0x89, 0x8e, 0x87, 0x80,
    0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8,
    0xdd, 0xda, 0xd3, 0xd4, 0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44, 0x19, 0x1e, 0x17, 0x10,
    0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f,
    0x6a, 0x6d, 0x64, 0x63, 0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13, 0xae, 0xa9, 0xa0, 0xa7,
    0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef,
    0xfa, 0xfd, 0xf4, 0xf3
};

// ********************************* GLOBAL VARIABLES ************************************* //

uint8_t buf[3];           // "buf[3]" takes data frame from sensor

uint16_t offset;          // memory for saving height offset value

uint16_t distBuf = 0;     // buffer for last measured distance

uint8_t announced = 0;    // indicator variable for audio output

uint8_t timeDiv = 0;      // counter variable for display & audio freq. divider

String filename;          // variable for incrementing file name

// **************************************************************************************** //


// **************************************************************************************** //
//                                           SETUP                                          //
// **************************************************************************************** //

void setup() {

  Wire.begin();                       // join I2C bus as master
  
  // initialize LCD
  lcd.begin();
  for (nb=0; nb<8; nb++ ) {           // generate 8 custom chars
    for (bc=0; bc<8; bc++) bb[bc]= pgm_read_byte( &custom[nb][bc] );
    lcd.createChar ( nb+1, bb );
  }
  lcd.clear();
  lcd.backlight();

  // initialize SD
  while (!SD.begin(10)) {
    writeBigString("SD", 0, 0);       // blinking "SD" on display in case no SD inserted
    delay(1500);
    lcd.clear();
  }

  //loading screen
  writeBigString("LOAD", 0, 0);       // loading screen for remaining Setup() function

  // open new file with incrementing file name
  for (uint8_t n = 0; n <= 1000; n++){
    String i_str = String(n);
    if (!SD.exists(String("data_" + i_str + ".csv"))){
      filename = String("data_" + i_str + ".csv");
      break;
    }
  }
  
  myFile = SD.open(filename, FILE_WRITE);
  if(myFile){
    myFile.println("TIMESTAMP;ENTFERNUNG");
    myFile.close();
  }


  // initialize mp3 module
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(10);
  myDFPlayer.playMp3Folder(7);        // play test audio ("minimums")


  // adjusting
 pinMode(2, INPUT_PULLUP);
  if (digitalRead(2) == LOW) {        // button pressed: 
    offset = messen();                // offset is measured and saved in "offset.txt"
    if (SD.exists("offset.txt")) {
      SD.remove("offset.txt");
    }
    
    myFile = SD.open("offset.txt", FILE_WRITE);
    if(myFile){

      myFile.write(buf[0]);
      myFile.write(buf[1]);

      myFile.close();
    }
  }
  else {
    myFile = SD.open("offset.txt", FILE_READ);         // button not pressed:
    if(myFile.available() > 0){                        // offset value is loaded from file
      offset = ((uint16_t) myFile.read() << 8) | (uint16_t) myFile.read();
      myFile.close();
    }
    else {
      offset = 0;
    }

  }

  
  lcd.clear();                                         // loading screen reset
  
}


// **************************************************************************************** //
//                                        MAIN LOOP                                         //
// **************************************************************************************** //

void loop() {
  
  // ************************************ VARIABLES *************************************** //

  uint16_t distance = 0;  // "distance" includes distance in mm, gets corrected by offset
  float distance_m = 0;   // distance as float in metres
  char distance_c[5];     // distance as string for lcd display

  // ************************************************************************************** //
  
  distance = messen();
  
  if (distance<=offset)                           // if measured distance < offset:
  {                                               // distance = 0
    distance = 0.0;
  }
  else                                            // else: distance gets corrected by offset
  {
    distance = distance-offset;
  }


  distance_m = (float) distance / 1000.0;
  dtostrf(distance_m, 5, 1, distance_c);


  if((distance_m<=30.0) && (distance_m>0.4)){     // threshold at which measuring frequency = 1/sec
    
    // save to file
    myFile = SD.open(filename, FILE_WRITE);
    if(myFile){
      unsigned long t = millis();                 // get timestamp
      myFile.print(t);
      myFile.print(";");
      myFile.println(distance);
      myFile.close();
    }
       
    if(timeDiv<9){          // frequency divider for display & audio

      timeDiv++;            // -> functions for display & audio get triggered every 10th time

    }
    else{

      timeDiv = 0;
      // display on lcd
      lcd.setCursor(0,0);
      lcd.clear();
      writeBigString(distance_c, 0, 0);
      writeBigChar('M', 12, 0);

      // audio callout MP3 module
      if ((distBuf-distance > 50) && (distBuf > distance)){
        
        callout(distance, mySoftwareSerial);
        
        distBuf = distance;
      }

    }

    delay(100);                                   // waiting 1/10 sec -> frequency ~10/sec
    
  }

  else{                                           // measuring frequency also 1/sec:

    // display on lcd
    lcd.setCursor(0,0);
    lcd.clear();
    writeBigString(distance_c, 0, 0);
    writeBigChar('M', 12, 0);

    // save to file
    myFile = SD.open(filename, FILE_WRITE);
    if(myFile){
      unsigned long t = millis();                 // get timestamp
      myFile.print(t);
      myFile.print(";");
      myFile.println(distance);
      myFile.close();
    }
    
    // audio callout MP3 module
    if ((distBuf-distance > 50) && (distBuf > distance)){
      
      callout(distance, mySoftwareSerial);
      
      distBuf = distance;
    }

    delay(1000);                                  // wait for 1 sec -> frequency 1/sec

  }


}

// **************************************************************************************** //
//                                       SUBROUTINES                                        //
// **************************************************************************************** //

// CRC function for checksum calculation
uint8_t crc8(uint8_t *p, uint8_t len) {
  uint8_t i;
  uint8_t crc = 0x0;
  while (len--) {
    i = (crc ^ *p++) & 0xFF;
    crc = (crc_table[i] ^ (crc << 8)) & 0xFF;
  }
  return crc & 0xFF;
}

// writeBigChar: writes big char 'ch' into column x, row y; 
// returns number of columns used by 'ch'
int writeBigChar(char ch, byte x, byte y) {
  if (ch < ' ' || ch > '_') return 0;                  // if outside of table: no action
  nb=0;                                                // Byte counter for chars
  for (bc=0; bc<8; bc++) {                        
    bb[bc] = pgm_read_byte( &bigChars[ch-' '][bc] );   // read 8 Bytes from PROGMEM
    if(bb[bc] != 0) nb++;
  }  
 
  bc=0;
  for (row = y; row < y+2; row++) {
    for (col = x; col < x+nb/2; col++ ) {
      lcd.setCursor(col, row);                         // go to position
      lcd.write(bb[bc++]);                             // write Byte and increment
    }

  }
  return nb/2-1;                                    // return number of columns for char
}

// writeBigString: writes every letter of a string
void writeBigString(char *str, byte x, byte y) {
  char c;
  while ((c = *str++))
  x += writeBigChar(c, x, y) + 1;
}


// function for measuring distance
uint16_t messen() {

  uint16_t dist;
  uint8_t CRC = 0;                        // "CRC" includes checksum for comparison with sensor
  
  Wire.beginTransmission(SENSOR_ADDR);    // transmit message to sensor via I2C
    Wire.write(0x00);                     // send trigger byte
    Wire.endTransmission();               // end transmission
  
    delay(0.5);                           // delay between transmissions
  
    Wire.requestFrom(SENSOR_ADDR, 3);     // retrieve three Bytes from sensor
    buf[0] = Wire.read();                 // first distance byte
    buf[1] = Wire.read();                 // second distance byte
    buf[2] = Wire.read();                 // crc byte
    
    CRC = crc8(buf, 2);                   // calculates checksum from both received data bytes
  
    
    if (CRC == buf[2]) {                  // compares checksums; if identical: 
      dist = (buf[0]<<8) + buf[1];        // calculate and return distance
     
    }
    else {                                                   
      dist = 0;
                              
    }                                                         
  
    return dist;
}

// audio output function
void callout(uint16_t xdistance, SoftwareSerial xmySoftwareSerial) {
    
  if (myDFPlayer.begin(mySoftwareSerial)){
    
    if ((announced != 1) && xdistance < 52000 && xdistance > 48000){
      myDFPlayer.playMp3Folder(1);
      announced = 1;
    }
    else if ((announced != 2) && xdistance < 42000 && xdistance > 38000){
      myDFPlayer.playMp3Folder(2);
      announced = 2;
    }
    else if ((announced != 3) && xdistance < 32000 && xdistance > 28000){
      myDFPlayer.playMp3Folder(3);
      announced = 3;
    }
    else if ((announced != 4) && xdistance < 22000 && xdistance > 18000){
      myDFPlayer.playMp3Folder(4);
      announced = 4;
    }
    else if ((announced != 5) && xdistance < 12000 && xdistance > 9000){
      myDFPlayer.playMp3Folder(5);
      announced = 5;
    }
    else if ((announced != 6) && xdistance < 6000 && xdistance > 4000){
      myDFPlayer.playMp3Folder(6);
      announced = 6;
    }
  
  }
  
}

/*

parts of this code are based upon the following sources:

http://woodsgood.ca/projects/2015/02/17/big-font-lcd-characters/

https://github.com/Terabee/sample_codes/blob/master/Arduino/
TeraRanger_single_point_Arduino_I2C/TeraRanger_single_point_Arduino_I2C.ino

*/