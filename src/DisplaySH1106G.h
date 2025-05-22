#include <Adafruit_SH110X.h>

// Concrete implementation of DisplayInterface using the Adafruit_SH1106G OLED display
class DisplaySH1106G : public DisplayInterface {
private:
  Adafruit_SH1106G oled;  // Instance of the Adafruit SH1106G OLED display driver

public:
  // Constructor initializes the OLED display with specified width, height, and reset pin
  DisplaySH1106G(uint8_t _width, uint8_t _height, int8_t _reset)
    : oled(_width, _height, &Wire, _reset) {}

  // Initializes the OLED display with the given I2C address (default: 0x3C)
  bool begin(uint8_t _i2caddr = 0x3C) {
    if (!oled.begin(_i2caddr, true)) {
      return false; // Initialization failed
    }
    oled.clearDisplay();  // Clear the screen
    oled.display();       // Push the cleared screen to the display
    return true;
  }

  // Draw a fast horizontal line on the display
  void drawFastHLine(int x, int y, int w, int color) {
    oled.drawFastHLine(x, y, w, color);
  }

  // Fill a rectangular area on the display
  void fillRect(int x, int y, int w, int h, int color) {
    oled.fillRect(x, y, w, h, color);
  }

  // Return the width of the display
  int width() const {
    return oled.width();
  }

  // Enable or disable text wrapping
  void setTextWrap(bool wrap) {
    oled.setTextWrap(wrap);
  }

  // Set the color used to draw text
  void setTextColor(int color) {
    oled.setTextColor(color);
  }

  // Set the cursor position for text
  void setCursor(int x, int y) {
    oled.setCursor(x, y);
  }

  // Print text to the display (without newline)
  void print(const char* text) {
    oled.print(text);
  }

  // Print text to the display followed by a newline
  void println(const char* text) {
    oled.println(text);
  }

  // Draw a single pixel at (x, y) with the given color
  void drawPixel(int x, int y, int color) {
    oled.drawPixel(x, y, color);
  }

  // Refresh the display with the current buffer contents
  void display() {
    oled.display();
  }

  // Clear the display buffer
  void clearDisplay() {
    oled.clearDisplay();
  }

  // Provide access to the underlying Adafruit_SH1106G object
  Adafruit_SH1106G& getDisplay() {
    return oled;
  }
};
