#include "DrawText.h"

DrawText::DrawText(){
    this->DEBUG = false;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->text = "";
    oldValue = "";
}

  void DrawText::setup(int x, int y, int width, int height, String text){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    oldValue = "";
  }

  void DrawText::setValue(String value){
    newValue = value;
  }

  void DrawText::draw(SWTFT &tft){
    if(DEBUG){
      Serial.println("oldText: " + oldValue + " newText: " + newValue);
    }
    if(newValue.compareTo(oldValue) != 0){
      if(DEBUG){
        Serial.println("Displaying Text");
      }
      oldValue = newValue;
      tft.setCursor(x, y);
      tft.print(text);
    }
    else{
      if(DEBUG){
        Serial.println("Not priniting text");
      }
    }
  }

  
  /*Drawable(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;*/ 



/*void Drawable::draw(&SWTFT tft, string value) {
	tft.setCursor(x, y);
	tft.print(value);
}*/

/* class BaseClass       //Abstract class
       {

              public:
               virtual void Display1()=0;     //Pure virtual function or abstract function
               virtual void Display2()=0;     //Pure virtual function or abstract function

               void Display3()
               {
                      cout<<"\n\tThis is Display3() method of Base Class";
               }

       };

       class DerivedClass : public BaseClass
       {

              public:
               void Display1()
               {
                      cout<<"\n\tThis is Display1() method of Derived Class";
               }

               void Display2()
               {
                      cout<<"\n\tThis is Display2() method of Derived Class";
               }

       };*/
