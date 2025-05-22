#include <string>
#include "PixelBle.h"

// Sprite definitions
const uint8_t PixelBle::BLE[9][14] = {
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 }
};

const uint8_t PixelBle::BLE_CONNECTED[9][14] = {
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 }
};


void PixelBle::draw(Adafruit_GFX& display, int xx, int yy) {
  const uint8_t(*sprite)[14];

 // Calculate drawing position with offsets
  // Adjust X position based on whether icon is left or right aligned
  int drawX = x + xx + ((position == IconPosition::LEFT) ? offsetX : -offsetX); 
  // Y position with vertical offset
  int drawY = y + yy + offsetY;

  if (isConnected) {
    sprite = BLE_CONNECTED;
  } else {
    sprite = BLE;
  }


  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 14; col++) {
      if (sprite[row][col]) {
        display.drawPixel(drawX + col, drawY + row, color);
      }
    }
  }
 
}