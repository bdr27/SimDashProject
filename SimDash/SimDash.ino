#include  <Adafruit_GFX.h>
#include "SWTFT.h"
#include "HelloWorld.h" 
#include "DrawText.h"
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
SWTFT tft;
double textMultiplier = 8;
int resetCounter = 0;
DrawText rpm(200, 200, 0, 0, "RPM");

void setup() {
  Serial.begin(9600);
  Serial.println("TFT LCD Shield Test");
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("Your LCD driver chip name is: ");
  Serial.println(identifier, HEX);
  tft.begin(identifier);
  //tft.fillScreen(0x0000);
  Serial.println("Working Well");
  Serial.println("Hello World");
  tft.setRotation(1);
  tft.setTextSize(1);
}
void loop() {
  //for(uint8_t rotation=0; rotation<4; rotation++) {
    //tft.setRotation(rotation);
    testText();
    //delay(10);
  //}
  
}

void staticTest(){
  
}

unsigned long testText() {
  //tft.fillScreen(0x0000);
  unsigned long start = micros();
  if(resetCounter < 2){
    tft.fillScreen(0x2034);
    resetCounter++;
    Serial.println("Resetting");
    tft.fillRect(0, 0, 250, 60, 0x0000); 
    tft.setCursor(0, 0);
    tft.setTextColor(0xFFFF);  
    tft.setTextSize(1);
    tft.print("Hello World!");
    rpm.setValue("" + resetCounter);
    int size = 4;
    tft.setTextSize(size);
    rpm.draw(tft);
    tft.fillRect(198, 200, 1, size * textMultiplier, 0x0000);
    /*delay(1);
    tft.setCursor(100, 120);
    tft.print("I am a test");*/
  } 
  /*tft.println();
  tft.setTextColor(0xFFE0); tft.setTextSize(2);
  tft.println("A Yellow Text Here");
  tft.println();
  tft.setTextColor(0x07E0);
  tft.setTextSize(3);
  tft.println("A Green Text Here");
  tft.fillRect(100,100,200,100,0x07E0);*/
  return micros() - start;
}
