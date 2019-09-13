#include  <Adafruit_GFX.h>
#include "SWTFT.h"
#include "HelloWorld.h" 
#include "DrawText.h"
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
SWTFT tft;
enum mode{
  NONE,
  INIT,
  DATA
};

enum mode intputMode;
double textHeightMultiplier = 8;
double textWidthMultiplier = 6;
int resetCounter = 0;
int dataCounter;

//const int drawable = 50;
//DrawText toDraw[drawable];
String inData;
DrawText rpm;

void setup() {
  intputMode = NONE;
  Serial.begin(250000);
  Serial.println("TFT LCD Shield Test");
  rpm.setup(0, 100, 0, 0, 2, "RPM");
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("Your LCD driver chip name is: ");
  Serial.println(identifier, HEX);
  tft.begin(identifier);
  tft.fillScreen(0x0000);
  tft.setRotation(1);
  tft.setTextSize(1);
  inData = "";
  dataCounter = 0;
}
void loop() {
    screenClean();
    updateScreen();
}

void updateScreen(){
  while(Serial.available() > 0){
      char recieved = Serial.read();
      // if(intputMode == NONE){
      //   setInputMode(recieved);  
      // }
      // else{
      //   inData += recieved;
        //Process message when new line character is revieved
        if(recieved == '\n' || recieved == ','){
          switch(intputMode){
            case NONE:
              setInputMode(inData);              
            case DATA:
              updateData(inData);
              break;
            case INIT:
              initScreen(inData);
              break;
          }
          intputMode = NONE;
          //rpm.setValue(inData); 
          //rpm.draw(tft);
          //Serial.println(inData);        
          inData = "";
          dataCounter++;
        }
        else{
          inData += recieved
        }
      //}      
    }
}

void setInputMode(char recieved){
  switch(recieved){
    case 'i':
    case 'I':
      intputMode = INIT;
      dataCounter = 0;
      break;
    case 'd':
    case 'D':
      intputMode = DATA;
      dataCounter = 0;
      break;       
    }
}

void initScreen(String settings){
  rpm.setValue("Initialising");
  rpm.draw(tft);
}

void updateData(String message){
  rpm.setValue("Data");
  rpm.draw(tft);
}

void drawToRPM(String word){
  rpm.setValue(word);
  rpm.draw(tft);
}

void drawWord(String word){  
    tft.fillRect(0, 0, 250, 60, 0x0000);
    tft.setCursor(0, 0);
    tft.setTextColor(0xFFFF, 0x0000);  
    tft.setTextSize(1);
    tft.print(word);
    
}

void staticTest(){
  
}

void screenClean() {
  if(resetCounter < 2){
    tft.fillScreen(0x0000);
    resetCounter++;    
  }  
}
