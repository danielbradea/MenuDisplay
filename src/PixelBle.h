#ifndef PIXEL_BLE_H
#define PIXEL_BLE_H

#include <Adafruit_GFX.h>
#include "IIcon.h"

class PixelBle: public IIcon {
private:
  static const uint8_t BLE[9][14];
  static const uint8_t BLE_CONNECTED[9][14];

  // Position variables
  int x = 0;
  int y = 0;
  int offsetX = 0;
  int offsetY = 0;
  
  // Appearance and state variables
  uint16_t color = 1;
  bool isConnected = false;
  IconPosition position = IconPosition::LEFT;

public:
  PixelBle() = default;
  void draw(Adafruit_GFX& display, int xx = 0, int yy = 0) override;

  void setIsConnected(bool connected) { isConnected = connected; }

  // Implement all pure virtual functions from IIcon
  int getWidth() override { return 14; }
  
  void setX(int xPos) override { x = xPos; }
  void setY(int yPos) override { y = yPos; }
  int getX() const override { return x; }
  int getY() const override { return y; }
  
  void setColor(uint16_t newColor) override { color = newColor; }
  uint16_t getColor() const override { return color; }

  // Offset management (only if they exist in IIcon)
  void setOffsetX(int offset)  { offsetX = offset; }
  int getOffsetX() const  { return offsetX; }
  void setOffsetY(int offset) { offsetY = offset; }
  int getOffsetY() const  { return offsetY; }

  // Position management
  void setPosition(IconPosition pos)  { position = pos; }
  IconPosition getPosition() const  { return position; }
};

#endif