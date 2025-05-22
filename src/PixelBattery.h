#ifndef PIXEL_BATTERY_H
#define PIXEL_BATTERY_H

#include <Adafruit_GFX.h>
#include "IIcon.h"

// Declare a PixelBattery class that inherits from IIcon interface
class PixelBattery : public IIcon {
private:
  // Static constant 2D arrays representing different battery states as pixel art
  static const uint8_t BATTERY_FULL[9][14];     // Full battery icon (100%)
  static const uint8_t BATTERY_65[9][14];       // 65% battery level icon
  static const uint8_t BATTERY_30[9][14];       // 30% battery level icon
  static const uint8_t BATTERY_EMPTY[9][14];    // Empty battery icon
  static const uint8_t BATTERY_CHARGING[9][14]; // Charging battery icon

  // Position variables
  int x = 0;          // X-coordinate position
  int y = 0;          // Y-coordinate position
  int offsetX = 0;    // Horizontal offset from position
  int offsetY = 0;    // Vertical offset from position
  
  // Appearance and state variables
  uint16_t color = 1;         // Color of the icon (default 1)
  int level = 100;            // Battery level percentage (default 100%)
  bool isCharging = false;    // Whether battery is charging
  bool percent = true;        // Whether to show percentage
  IconPosition position = IconPosition::LEFT; // Default position on screen

public:
  // IIcon interface implementation
  void draw(Adafruit_GFX& display, int xx = 0, int yy = 0) override; // Draw the icon
  int getWidth() override; // Get icon width

  // Position management
  void setX(int x) override;     // Set X position
  void setY(int y) override;     // Set Y position
  int getX() const override;     // Get X position
  int getY() const override;     // Get Y position

  // Color management
  void setColor(uint16_t color) override; // Set icon color
  uint16_t getColor() const override;     // Get current color

  // Battery-specific methods
  void setLevel(int level);          // Set battery level (0-100)
  void setIsCharging(bool charging);  // Set charging state
  void setShowPercent(bool showPercent); // Toggle percentage display

  // Offset management
  void setOffsetX(int offset) { offsetX = offset; }  // Set horizontal offset
  int getOffsetX() const { return offsetX; }         // Get horizontal offset
  void setOffsetY(int offset) { offsetY = offset; }  // Set vertical offset
  int getOffsetY() const { return offsetY; }         // Get vertical offset
  
  // Position management (relative to screen edges)
  void setPosition(IconPosition pos) override { position = pos; } // Set screen position
  IconPosition getPosition() const override { return position; }  // Get current position
};

#endif