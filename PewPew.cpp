#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D3
#define PIXEL_COUNT 30
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint32_t color;

int ledColors[][] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 25}};
int x = 0;

void setup() {
  Spark.function("setColor", setColor);
  
  color = strip.Color(r(10,255), r(10,255), r(10,255));
    
  strip.begin();
  strip.setBrightness(2);
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  pewpew(color);
}

// shoot lazers
static void pewpew(uint32_t color)
{
  static int pixels = strip.numPixels;
  
  for(int i = 0; i < pixels+4; i++)
  {
      strip.setPixelColor(i % pixels, color); // Color pixel
      strip.setPixelColor((i-4) % pixels, 0); // Turn off pixel
      strip.show(); // Update display
      delay(25);
  }
}

// returns a random integar between minVal and maxVal
int r(int minVal, int maxVal)
{
  return rand() % (maxVal-minVal+1) + minVal;
}

// Webpage sends color value in base 16 format: "#AABBCC"
// AA -> Red, BB -> Blue, CC -> Green, 0-255 (1 byte) for each channel
int setColor(String colorValue)
{
    // Verify Photon is receiving commands
    RGB.control(true);
    RGB.setColor(ledColors[x][0], ledColors[x][1], ledColors[x][2]);
    
    // 6 HEX char, 1 null character
    char col[7];
    colorValue.substring(1).toCharArray(col, 7);
    
    long int rgb = strtol(col, NULL, 16);
    int r = rgb / 0x10000;
    int g = (rgb / 0x100) % 0x100;
    int b = rgb % 0x100;
    
    color = strip.Color(r, g, b);
    return 0;
}