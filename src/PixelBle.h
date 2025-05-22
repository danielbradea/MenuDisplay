#ifndef PIXEL_BLE_H
#define PIXEL_BLE_H

#include <DisplayInterface.h>
#include "StatusBarElement.h"

// The PixelBle class represents a graphical status bar element that displays the Bluetooth (BLE) connection status.
class PixelBle : public StatusBarElement {
private:
  // BLE disconnected icon (9x14 pixel sprite)
  static const uint8_t BLE[9][14];

  // BLE connected icon (9x14 pixel sprite)
  static const uint8_t BLE_CONNECTED[9][14];

  // Bluetooth connection status: true = connected, false = disconnected
  bool isConnected = false;

public:
  // Default constructor
  PixelBle() = default;

  // Draws the icon corresponding to the current connection status (connected or not)
  void draw(DisplayInterface& display, int xx = 0, int yy = 0) override;

  // Returns the width of the icon (used for layout)
  int getWidth() override;

  // Sets the Bluetooth connection status
  void setIsConnected(bool connected) { isConnected = connected; }

  // Returns the current Bluetooth connection status
  bool getIsConnected() { return isConnected; }
};

#endif
