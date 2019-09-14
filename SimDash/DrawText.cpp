#include "DrawText.h"

DrawText::DrawText(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->text = "";
    this->fontSize = 0;
    oldValue = "";
}

  void DrawText::setup(int x, int y, int width, int height, int fontSize, String text){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->fontSize = fontSize;
    oldValue = "";
  }

  void DrawText::setValue(String value){
    text = value;
  }

  void DrawText::draw(SWTFT &tft){
    if(DEBUG){
      Serial.println("oldText: " + oldValue + " newText: " + text);
    }
    if(text.compareTo(oldValue) != 0){
      if(DEBUG){
        Serial.println("Displaying Text");
      }
      
      //tft.setTextColor(0x0000, 0xFFFF);  
      //tft.print(oldValue);
      oldValue = text;
      tft.setTextColor(0xFFFF, 0x0000);
      tft.setCursor(x, y);
      tft.setTextSize(fontSize);
      tft.setFont();
      tft.print(oldValue);
    }
    else{
      if(DEBUG){
        Serial.println("Not priniting text");
      }
    }
  } 