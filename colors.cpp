#include "colors.h"

#define NUM_COLORS 12

extern RgbColor colors[] = {
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
  for (int i = 0; i < NUM_COLORS; i++) {
    if (colors[i].name.equalsIgnoreCase(colorName)) {
      return colors[i];
    }
  }
  // Return a default color (black) if the color name is not found
  return RgbColor("Black", 0, 0, 0);
}

RgbColor getRandomColor() {
  return colors[random(0, NUM_COLORS)];
}