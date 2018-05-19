#include "SWTFT.h" 
class DrawText
{
protected:
	int x;
	int y;
  int height;
  int width;
  String text;
  String newValue;
  String oldValue; 
  
public:
  DrawText(int x, int y, int width, int height, String text);
  void setValue(String value);
  void draw(SWTFT &tft);
	//Drawable(int x, int y, int width, int height);
	//virtual void Draw(&SWTFT tft, string value);
};
