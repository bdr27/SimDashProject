#include "DrawText.h"
DrawText::DrawText(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->text = "";
    this->fontSize = 0;
    valueSetMode = NONE;
    oldValue = "";
}

void DrawText::setup(String settings){
  bool setValue = false;
  char memberSetting = 0;
  String memberValue = "";
  for(char& c : settings){
    if(setValue){
      if(c == ',' || c == '\n'){
      }
      else{
        memberValue += c;
      }
    }
    else{
      if(c == ':')
      {
        setValue = setValueSetMode(c);
      }
      else{
        memberSetting = c;
      }  
    }
  }
}

bool DrawText::setValueSetMode(char input){
  bool setValue = false;
  switch (input)
  {
  case 'x':
  case 'X':
    valueSetMode = X;
    setValue = true;
    break;
  case 'y':
  case 'Y':
    valueSetMode = Y;
    setValue = true;
    break;
  case 'h':
  case 'H':
    valueSetMode = Height;
    setValue = true;
    break;
  case 'w':
  case 'W':
    valueSetMode = Width;
    setValue = true;
    break;
  case 'f':
  case 'F':
    valueSetMode = FONTSIZE;
    setValue = true;
    break;
  case 't':
  case 'T':
    valueSetMode = Text;
    setValue = true;
    break;
        }
        return setValue;
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