#include <string>
#include "PixelBattery.h"

// Sprite definitions - 9x14 pixel arrays representing different battery states

// Full battery icon (100% charge)
const uint8_t PixelBattery::BATTERY_FULL[9][14] = {
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Top border with battery tip
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // Left border
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, // Full battery bars (3)
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, // Full battery bars (3)
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, // Full battery bars (3)
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, // Full battery bars (3)
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, // Full battery bars (3)
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // Bottom border
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // Bottom border with battery tip
};

// 65% battery icon (similar structure but with fewer bars)
const uint8_t PixelBattery::BATTERY_65[9][14] = {
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 }, // Only 2 bars visible
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 }, // Only 2 bars visible
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 }, // Only 2 bars visible
  { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 }, // Only 2 bars visible
  { 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 }, // Only 2 bars visible
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// 30% battery icon (only one bar visible)
const uint8_t PixelBattery::BATTERY_30[9][14] = {
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // Only 1 bar visible
  { 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // Only 1 bar visible
  { 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // Only 1 bar visible
  { 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // Only 1 bar visible
  { 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // Only 1 bar visible
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Empty battery icon (no bars visible)
const uint8_t PixelBattery::BATTERY_EMPTY[9][14] = {
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // No bars
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // No bars
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // No bars
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // No bars
  { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // No bars
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Charging battery icon (with lightning bolt symbol)
const uint8_t PixelBattery::BATTERY_CHARGING[9][14] = {
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 }, // Plug pattern
  { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 }, // Plug pattern
  { 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 }, // Plug pattern
  { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 }, // Plug pattern
  { 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 }, // Plug pattern
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Duplicate includes (could be removed)
#include <string>
#include "PixelBattery.h"

// Draw method implementation
void PixelBattery::draw(Adafruit_GFX& display, int xx, int yy) {
  // Pointer to the selected sprite
  const uint8_t(*sprite)[14];
  
  // Calculate drawing position with offsets
  // Adjust X position based on whether icon is left or right aligned
  int drawX = x + xx + ((position == IconPosition::LEFT) ? offsetX : -offsetX); 
  // Y position with vertical offset
  int drawY = y + yy + offsetY;

  // Select appropriate sprite based on battery state
  if (isCharging) {
    sprite = BATTERY_CHARGING;
  } else if (level > 65) {
    sprite = BATTERY_FULL;
  } else if (level > 30) {
    sprite = BATTERY_65;
  } else if (level > 5) {
    sprite = BATTERY_30;
  } else {
    sprite = BATTERY_EMPTY;
  }

  // Format percentage text with proper spacing
  char textBuf[6]; // Buffer for percentage text
  if (level == 100) {
    snprintf(textBuf, sizeof(textBuf), "100%%"); // Full percentage
  } else if (level < 10) {
    snprintf(textBuf, sizeof(textBuf), "  %d%%", level); // Single digit with extra space
  } else {
    snprintf(textBuf, sizeof(textBuf), " %d%%", level); // Double digit
  }
  
  // Calculate text dimensions
  const int charWidth = 6; // Width of each character
  const int batteryWidth = 14; // Width of battery icon
  const int textWidth = strlen(textBuf) * charWidth; // Total text width

  // Handle left-aligned position
  if (position == IconPosition::LEFT) {
    // Draw battery icon
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 14; col++) {
        if (sprite[row][col]) {
          display.drawPixel(drawX + col, drawY + row, color);
        }
      }
    }
    
    // Draw percentage text if enabled
    if (percent) {
      display.setTextColor(color);
      display.setCursor(drawX + batteryWidth, drawY + 1);
      display.print(textBuf);
    }
  } 
  else { 
    // Handle right-aligned position
    if (percent) {
      display.setTextColor(color);
      display.setCursor(drawX, drawY + 1);
      display.print(textBuf);
    }
    
    // Draw battery icon after text for right alignment
    int batteryStartX = drawX + (percent ? textWidth : 0);
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 14; col++) {
        if (sprite[row][col]) {
          display.drawPixel(batteryStartX + col, drawY + row, color);
        }
      }
    }
  }
}

// Get total width of icon (including text if shown)
int PixelBattery::getWidth() {
  if (percent) {
    return 14 + (4 * 6); // Battery width (14) + max text width (4 chars * 6px)
  }
  return 14; // Just battery width
}

// Set battery level (0-100) with bounds checking
void PixelBattery::setLevel(int lvl) {
  level = constrain(lvl, 0, 100); // Constrain to valid range
}

// Set charging state
void PixelBattery::setIsCharging(bool charging) {
  isCharging = charging;
}

// Toggle percentage display
void PixelBattery::setShowPercent(bool showPercent) {
  percent = showPercent;
}

// Position setters and getters
void PixelBattery::setX(int x) {
  this->x = x;
}

void PixelBattery::setY(int y) {
  this->y = y;
}

int PixelBattery::getX() const {
  return x;
}

int PixelBattery::getY() const {
  return y;
}

// Color setters and getters
void PixelBattery::setColor(uint16_t color) {
  this->color = color;
}

uint16_t PixelBattery::getColor() const {
  return color;
}