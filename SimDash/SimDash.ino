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
const int drawable = 50;
DrawText toDraw[drawable];

DrawText rpm;

void setup() {
  Serial.begin(19200);
  Serial.println("TFT LCD Shield Test");
  rpm.setup(200, 200, 0, 0, "RPM");
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("Your LCD driver chip name is: ");
  Serial.println(identifier, HEX);
  tft.begin(identifier);
  tft.fillScreen(0x0000);
  Serial.println("Working Well");
  Serial.println("Hello World");
  tft.setRotation(1);
  tft.setTextSize(1);
}
void loop() {
  //for(uint8_t rotation=0; rotation<4; rotation++) {
    //tft.setRotation(rotation);
    testText();
    if(Serial.available() > 0){
      DrawWord(Serial.readString());
    }
    for(int i = 0; i < drawable; i++){
      toDraw[i].draw(tft);
    }
    //delay(10);
  //}
  
}

void DrawWord(String word){  
    tft.fillRect(0, 0, 250, 60, 0x0000);
    tft.setCursor(0, 0);
    tft.setTextColor(0xFFFF);  
    tft.setTextSize(1);
    tft.print(word);
    
}

void staticTest(){
  
}

void testText() {
  if(resetCounter < 2){
    tft.fillScreen(0x2034);
    resetCounter++;
    rpm.setValue("" + resetCounter);
    int size = 4;
    tft.setTextSize(size);
    rpm.draw(tft);
    tft.fillRect(198, 200, 1, size * textHeightMultiplier, 0x0000);
    tft.fillRect(200, 198, size * textWidthMultiplier * 3, 1, 0x0000);
  } 
  /*tft.println();
  tft.setTextColor(0xFFE0); tft.setTextSize(2);
  tft.println("A Yellow Text Here");
  tft.println();
  tft.setTextColor(0x07E0);
  tft.setTextSize(3);
  tft.println("A Green Text Here");
  tft.fillRect(100,100,200,100,0x07E0);*/
}
