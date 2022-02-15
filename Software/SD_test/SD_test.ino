#include <SPI.h>
#include <SD.h>

File myFile;
String filename;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*while (!Serial){
    ;
  }*/

  SD.begin(10);

  for (uint8_t i = 0; i <= 1000; i++){
    String i_str = String(i);
    if (!SD.exists(String("data_" + i_str + ".txt"))){
      filename = String("data_" + i_str + ".txt");
      break;
    }
  }
 
  myFile = SD.open(filename, FILE_WRITE);
  if(myFile){
    myFile.println("test");
    myFile.println("1, 2, 3");
    myFile.println("4, 5, 4");
    myFile.println("3, 2, 1");
    myFile.close();
  }


  myFile = SD.open("data.txt",FILE_READ);
  if (myFile){
    while(myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
