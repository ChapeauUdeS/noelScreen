#include <Arduino.h> 
#include <SPI.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>
#include "animation.h"


#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

typedef struct RGB{ double r; double g; double b; } ;

struct RGB colorConverter(int hexValue)
{
  struct RGB rgbColor;
  rgbColor.r = (hexValue & 0x000000ff) >> 0;  // Extract the RR byte
  rgbColor.g = (hexValue & 0x0000ff00) >> 8;   // Extract the GG byte
  rgbColor.b = (hexValue & 0x00ff0000) >> 16;        // Extract the BB byte

  return rgbColor; 
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  int t = 500;
  while(1)
  {
  
  for (int i =0;i<NEW_PISKEL_FRAME_COUNT;i++){
    
    for(int h=0;h<32;h++){
      for(int w =0;w<64;w++)
    {
      RGB rgb = colorConverter(new_piskel_data[i][h*64+w]);
      Serial.println(matrix.Color333(rgb.r, rgb.g, rgb.b));
      matrix.drawPixel(w, h, matrix.Color888(rgb.r, rgb.g, rgb.b));
    }    
  }
   delay(t);
  }
 
  }
  
}





void loop() {
  // Do nothing -- image doesn't change
}

