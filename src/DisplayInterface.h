#ifndef DISPLAY_INTERFACE_H
#define DISPLAY_INTERFACE_H

// Abstract interface for display functionality
// This allows different types of displays to be used interchangeably
class DisplayInterface {
public:
  virtual ~DisplayInterface() = default;

  // Draws a fast horizontal line at (x, y) with width 'w' and the given color
  virtual void drawFastHLine(int x, int y, int w, int color) = 0;

  // Fills a rectangle at (x, y) with width 'w', height 'h', and the given color
  virtual void fillRect(int x, int y, int w, int h, int color) = 0;

  // Returns the width of the display
  virtual int width() const = 0;

  virtual int height() const = 0;

  // Enables or disables automatic text wrapping
  virtual void setTextWrap(bool wrap) = 0;

  // Sets the color of the text
  virtual void setTextColor(int color) = 0;

  // Sets the cursor position for subsequent text output
  virtual void setCursor(int x, int y) = 0;

  // Prints a text string at the current cursor position
  virtual void print(const char* text) = 0;

  // Draws a single pixel at (x, y) with the given color
  virtual void drawPixel(int x, int y, int color) = 0;

  // Prints a text string followed by a newline
  virtual void println(const char* text) = 0;

  // Prints a formatted string at the current cursor position
  // Example: display->printf("Temp: %d C", temperature);
  virtual void printf(const char* format, ...) = 0;

  // Sets the text size (1 is default, 2 is double size, etc.)
  virtual void setTextSize(int size) = 0;

  // Pushes all drawing changes to the actual display
  virtual void display() = 0;

  // Clears the display buffer 
  virtual void clearDisplay() = 0;

  virtual void drawTriangle(int x0, int y0, 
                          int x1, int y1,
                          int x2, int y2, 
                          int color) = 0;
                          
  virtual void fillTriangle(int x0, int y0,
                          int x1, int y1,
                          int x2, int y2,
                          int color) = 0;


};

#endif // DISPLAY_INTERFACE_H
