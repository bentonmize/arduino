#include "colors.h"

extern RgbColor colors[] = {
  // RgbColor("Red", 255, 0, 0),
  // RgbColor("Green", 0, 255, 0),
  // RgbColor("Blue", 0, 0, 255),
  // RgbColor("Yellow", 255, 255, 0),
  // RgbColor("Cyan", 0, 255, 255),
  // RgbColor("Magenta", 255, 0, 255),
  // RgbColor("Silver", 192, 192, 192),
  // RgbColor("Gray", 128, 128, 128),
  // RgbColor("Maroon", 128, 0, 0),
  // RgbColor("Olive", 128, 128, 0),
  // RgbColor("Dark Green", 0, 128, 0)

  RgbColor("red", 255, 0, 0),      
  RgbColor("orange", 255, 128, 0),    
  RgbColor("yellow", 255, 255, 0),    
  RgbColor("lime", 128, 255, 0),
  RgbColor("green", 0, 255, 0),      
  RgbColor("teal", 255, 128, 0),    
  RgbColor("marine", 0, 255, 255),    
  RgbColor("blue", 0, 0, 255),      
  RgbColor("purple", 127, 0, 255),    
  RgbColor("magenta", 255, 0, 255),    
  RgbColor("pink" , 255, 0, 127),    
  RgbColor("white" , 255, 255, 255),  
};

RgbColor getColorByName(String colorName) {
  for (int i = 0; i < 11; i++) {
    if (colors[i].name.equalsIgnoreCase(colorName)) {
      return colors[i];
    }
  }
  // Return a default color (black) if the color name is not found
  return RgbColor("Black", 0, 0, 0);
}