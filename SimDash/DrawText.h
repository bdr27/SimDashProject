#include "SWTFT.h" 
class DrawText
{  
protected:
  const bool DEBUG = false;
  const float textHeightMultiplier = 8;
  const float textWidthMultiplier = 6;
	int x;
	int y;
  int height;
  int width;
  int fontSize;  
  String text;
  String newValue;
  String oldValue; 
  
public:
  DrawText();
  void setup(int x, int y, int width, int height, int fontSize, String text);
  void setValue(String value);
  void draw(SWTFT &tft);
	//Drawable(int x, int y, int width, int height);
	//virtual void Draw(&SWTFT tft, string value);
};
