#include "SWTFT.h"

class DrawText
{
protected:
  bool setValueSetMode(String input);
  const float textHeightMultiplier = 8;
  const float textWidthMultiplier = 6;
  long x;
  long y;
  long height;
  long width;
  long fontSize;
  String text;
  String oldValue;
  enum ValueSetMode
  {
    NONE,
    X,
    Y,
    WIDTH,
    HEIGHT,
    FONTSIZE,
    TEXT
  };
  enum ValueSetMode valueSetMode;

public:
  const bool DEBUG = true;
  DrawText();
  void setup(String settings);
  void setup(int x, int y, int width, int height, int fontSize, String text);
  void setValue(String value);
  void draw(SWTFT &tft);
};
