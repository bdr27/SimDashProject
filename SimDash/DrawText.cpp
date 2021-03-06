#include "DrawText.h"
DrawText::DrawText()
{
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
  this->text = "";
  this->fontSize = 0;
  valueSetMode = NONE;
  oldValue = "";
}

void DrawText::setup(String settings)
{
  if(DEBUG){
    Serial.println(settings);
  }
  bool setValue = false;
  String memberSetting = "";
  String memberValue = "";
  for (char &c : settings)
  {
    if(DEBUG)
    {
      Serial.println(c);
    }
    if (setValue)
    {
      
      if (c == ',' || c == '\n')
      {
        if(DEBUG)
        {
          Serial.print("Store value (");
          Serial.print(memberValue);
          Serial.println(")");
        }
        switch(valueSetMode){
          case X:
            if(DEBUG)
            {
              Serial.print("Trying to turn (");
              Serial.print(memberValue.toInt());
              Serial.println(") to int");
            }
            x = memberValue.toInt();    
            if(DEBUG)
            {
              Serial.print("x (");
              Serial.print(x);
              Serial.println(")");
            }
            break;
          case Y:
            y = memberValue.toInt();
            break;
          case WIDTH:
            width = memberValue.toInt();
            break;
          case HEIGHT:
            height = memberValue.toInt();
            break;
          case FONTSIZE:
            fontSize = memberValue.toInt();
            break;
          case TEXT:
            text = memberValue;
            break;
        }
        memberValue = "";
        setValue = false;
      }
      else
      {
        memberValue += c;
      }
    }
    else
    {
      if (c == ':')
      {
        setValue = setValueSetMode(memberSetting);
        memberSetting = "";
      }
      else if(c == ','){
        memberSetting = "";
        setValue = false;
      }
      else
      {
        memberSetting += c;
      }
    }
  }

  if(DEBUG)
  {  
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Width: ");
    Serial.print(width);
    Serial.print(" Height: ");
    Serial.print(height);
    Serial.print(" FontSize: ");
    Serial.print(fontSize);
    Serial.print(" Text: ");
    Serial.println(text);
  }
}

bool DrawText::setValueSetMode(String input)
{
  if(DEBUG){
    Serial.print("Value mode ");
    Serial.println(input);
  }
  bool setValue = false;
  input.toLowerCase();
  if (input == "x")
  {
    valueSetMode = X;
    setValue = true;
  }
  else if(input == "y")
  {
    valueSetMode = Y;
    setValue = true;
  }
  else if(input == "h")
  {
    valueSetMode = HEIGHT;
    setValue = true;
  }
  else if(input == "w")
  {
    valueSetMode = WIDTH;
    setValue = true;
  }
  else if(input == "f")
  {
    valueSetMode = FONTSIZE;
    setValue = true;
  }
  else if(input == "t")
  {
    valueSetMode = TEXT;
    setValue = true;
  }
  return setValue;
}

void DrawText::setup(int x, int y, int width, int height, int fontSize, String text)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->text = text;
  this->fontSize = fontSize;
  oldValue = "";
}

void DrawText::setValue(String value)
{
  text = value;
}

void DrawText::draw(SWTFT &tft)
{
  if (DEBUG)
  {
    Serial.println("oldText: " + oldValue + " newText: " + text);
  }
  if (text.compareTo(oldValue) != 0)
  {
    if (DEBUG)
    {
      Serial.println("Displaying Text");
    }

    oldValue = text;
    tft.setTextColor(0xFFFF, 0x0000);
    tft.setCursor(x, y);
    tft.setTextSize(fontSize);
    tft.setFont();
    tft.print(oldValue);
  }
  else
  {
    if (DEBUG)
    {
      Serial.println("Not priniting text");
    }
  }
}
