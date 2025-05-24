#include <Adafruit_SH110X.h>
#include <cstdio>  // For vsnprintf
#include <cstdarg> // For va_list, va_start, va_end

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
  void drawFastHLine(int x, int y, int w, int color) override {
    oled.drawFastHLine(x, y, w, color);
  }

  // Fill a rectangular area on the display
  void fillRect(int x, int y, int w, int h, int color) override {
    oled.fillRect(x, y, w, h, color);
  }

  // Return the width of the display
  int width() const override {
    return oled.width();
  }

  int height() const override {
    return oled.height();
  }

  // Enable or disable text wrapping
  void setTextWrap(bool wrap) override {
    oled.setTextWrap(wrap);
  }

  // Set the color used to draw text
  void setTextColor(int color) override {
    oled.setTextColor(color);
  }

  // Set the cursor position for text
  void setCursor(int x, int y) override {
    oled.setCursor(x, y);
  }

  // Print text to the display (without newline)
  void print(const char* text) override {
    oled.print(text);
  }

  // Print text to the display followed by a newline
  void println(const char* text) override {
    oled.println(text);
  }

  // Draw a single pixel at (x, y) with the given color
  void drawPixel(int x, int y, int color) override {
    oled.drawPixel(x, y, color);
  }

   // Draw a triangle outline
  void drawTriangle(int x0, int y0, 
                   int x1, int y1,
                   int x2, int y2, 
                   int color) override {
    oled.drawTriangle(x0, y0, x1, y1, x2, y2, color);
  }

  // Draw a filled triangle
  void fillTriangle(int x0, int y0,
                   int x1, int y1,
                   int x2, int y2,
                   int color) override {
    oled.fillTriangle(x0, y0, x1, y1, x2, y2, color);
  }

  // Refresh the display with the current buffer contents
  void display() override {
    oled.display();
  }

  // Clear the display buffer
  void clearDisplay() override {
    oled.clearDisplay();
  }

  // Print formatted text using printf-style syntax
  void printf(const char* format, ...) override {
    char buffer[128]; // Temporary buffer for formatted text
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    oled.print(buffer); // Print the formatted string
  }

  // Set the size of the text
  void setTextSize(int size) override {
    oled.setTextSize(size);
  }

  // Provide access to the underlying Adafruit_SH1106G object
  Adafruit_SH1106G& getDisplay() {
    return oled;
  }
};
