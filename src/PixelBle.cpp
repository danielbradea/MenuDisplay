#include <string>
#include "PixelBle.h"
#include "DisplayInterface.h"

// Sprite for BLE disconnected state (9 rows x 14 columns)
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

// Sprite for BLE connected state (same size, with some additional connection indicators)
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

// Method to draw the BLE icon on a display
void PixelBle::draw(DisplayInterface& display, int xx, int yy) {
  const uint8_t(*sprite)[14]; // Pointer to the sprite to draw

  // Compute drawing position including offsets
  // X is adjusted depending on whether the icon is on the left or right
  int drawX = x + xx + ((position == StatusBarElementPosition::LEFT) ? offsetX : -offsetX); 
  // Y is adjusted by a fixed offset
  int drawY = y + yy + offsetY;

  // Choose sprite based on connection status
  if (isConnected) {
    sprite = BLE_CONNECTED;
  } else {
    sprite = BLE;
  }

  // Loop through the sprite matrix and draw the non-zero pixels
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 14; col++) {
      if (sprite[row][col]) {
        display.drawPixel(drawX + col, drawY + row, color);
      }
    }
  }
}

// Returns the fixed width of the BLE icon
int PixelBle::getWidth(){
  return 14;
}
