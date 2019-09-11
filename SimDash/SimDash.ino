#include  <Adafruit_GFX.h>
#include "SWTFT.h"
#include "HelloWorld.h" 
#include "DrawText.h"
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
SWTFT tft;
double textHeightMultiplier = 8;
double textWidthMultiplier = 6;
int resetCounter = 0;

//const int drawable = 50;
//DrawText toDraw[drawable];
String inData = "";
DrawText rpm;
String priorWord = "";

void setup() {
  Serial.begin(9600);
  //Serial.println("TFT LCD Shield Test");
  rpm.setup(0, 100, 0, 0, 4, "RPM");
  tft.reset();
  uint16_t identifier = tft.readID();
  //Serial.print("Your LCD driver chip name is: ");
  //Serial.println(identifier, HEX);
  tft.begin(identifier);
  tft.fillScreen(0x0000);
  //Serial.println("Working Well");
  //Serial.println("Hello World");
  tft.setRotation(1);
  tft.setTextSize(1);
  inData = "";
  randomSeed(analogRead(0));
  //rpm.setValue("Hello World"); 
  //rpm.draw(tft);
}
void loop() {
    testText();
    bool updateScreen = false;
    while(Serial.available() > 0){
      updateScreen = true;
      char recieved = Serial.read();
      inData += recieved;
      //Process message when new line character is revieved
      if(recieved == '\n')
      {
        rpm.setValue(inData); 
        rpm.draw(tft);
        Serial.println(inData);        
        inData = "";
      }
    }
}

void DrawToRPM(String word){
  rpm.setValue(word);
  rpm.draw(tft);
}

void DrawWord(String word){  
    tft.fillRect(0, 0, 250, 60, 0x0000);
    tft.setCursor(0, 0);
    tft.setTextColor(0xFFFF, 0x0000);  
    tft.setTextSize(1);
    tft.print(word);
    
}

void staticTest(){
  
}

void testText() {
  if(resetCounter < 2){
    tft.fillScreen(0x0000);
    resetCounter++;
    //rpm.setValue("" + resetCounter);
    //int size = 4;
    //tft.setTextSize(size);
    //rpm.draw(tft);
    //tft.fillRect(198, 200, 1, size * textHeightMultiplier, 0x0000);
    //tft.fillRect(200, 198, size * textWidthMultiplier * 3, 1, 0x0000);
  }
  //String value = String(random(1000, 2000));
  //rpm.setValue("RPM " + value); 
  //rpm.draw(tft);
  //Serial.println("RPM");
  /*tft.println();
  tft.setTextColor(0xFFE0); tft.setTextSize(2);
  tft.println("A Yellow Text Here");
  tft.println();
  tft.setTextColor(0x07E0);
  tft.setTextSize(3);
  tft.println("A Green Text Here");
  tft.fillRect(100,100,200,100,0x07E0);*/
}
