#include <Adafruit_GFX.h>
#include "SWTFT.h"
#include "HelloWorld.h"
#include "DrawText.h"
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
SWTFT tft;
enum mode
{
  NONE,
  INIT,
  DATA
};

enum mode inputMode;
double textHeightMultiplier = 8;
double textWidthMultiplier = 6;
int resetCounter = 0;
int dataCounter;

const int drawable = 10;
DrawText toDraw[drawable];
String inData;
DrawText message;

void setup()
{
  inputMode = NONE;
  Serial.begin(9600);
  Serial.println("TFT LCD Shield Test");
  message.setup(0, 100, 0, 0, 2, "Initialise");
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
  screenClean();
}
void loop()
{
  updateScreen();
}

//Waits to recieve input via Serial at the moment
//Potentially want to extract this to quickly allow
//Other methods of commincation like bluetooth
void updateScreen()
{
  while (Serial.available() > 0)
  {
    char recieved = Serial.read();
    if(message.DEBUG)
    {
      Serial.println(recieved);
    }
    //Process message when new line character is revieved
    //if (recieved == '\n' || recieved == ',')
    if(recieved == ',' && inputMode == NONE)
    {
      if(message.DEBUG)
      {
        Serial.println("I Get here");
      }
      setInputMode(inData);
      dataCounter = 0;
      inData = "";
    }
    else if(recieved == '\n'){
      switch(inputMode){
        case INIT:
          initScreen(inData);
          break;
        case DATA:
          updateData(inData);
          break;          
      }
      inputMode = NONE;
      inData = "";
    }
    else
    {
      inData += recieved;
    }
  }
}

void setInputMode(String recieved)
{
  if(message.DEBUG)
  {
    Serial.print("Set input mode (");
    Serial.print(recieved);
    Serial.println(")");
  }
  recieved.toLowerCase();
  if(recieved == "i")
  {
    if(message.DEBUG)
    {
      Serial.print("Init Mode");
    }
    inputMode = INIT;
    dataCounter = 0;
  }
  else if(recieved == "d")
  {  
    if(message.DEBUG)
    {
      Serial.print("Data Mode");
    }
    inputMode = DATA;
    dataCounter = 0;
  }
}

void initScreen(String settings)
{
  drawToMessage("Initialise");
  if(message.DEBUG)
  {
    Serial.print("Init Screen with (");
    Serial.print(settings);
    Serial.println(")");
  }
  DrawText initText = toDraw[dataCounter++];
  initText.setup(settings);
  initText.draw(tft);
}

void updateData(String message)
{
  drawToMessage("Update");
}

void drawToMessage(String word)
{
  message.setValue(word);
  message.draw(tft);
}

void drawWord(String word)
{
  tft.fillRect(0, 0, 250, 60, 0x0000);
  tft.setCursor(0, 0);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(1);
  tft.print(word);
}

void staticTest()
{
}

void screenClean()
{
  if (resetCounter < 2)
  {
    tft.fillScreen(0x0000);
    resetCounter++;
  }
}
