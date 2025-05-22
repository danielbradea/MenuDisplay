// Header guard to prevent multiple inclusions
#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

// Include necessary libraries
#include <DisplayInterface.h>  // Graphics library for display
#include <vector>              // For dynamic arrays
#include <memory>              // For smart pointers
#include <stack>               // For menu history stack
#include "StatusBarElement.h"  // Status bar element interface
#include "MenuItem.h"          // Menu item class
#include <Arduino.h>

// Declaration of the MenuDisplay class
class MenuDisplay {
private:
  // Reference to the display object (e.g. Adafruit GFX-based)
  DisplayInterface& display;

  // Status bar configuration
  std::vector<std::shared_ptr<StatusBarElement>> leftElements;   // Elements shown on the left side of the top bar
  std::vector<std::shared_ptr<StatusBarElement>> rightElements;  // Elements shown on the right side of the top bar
  int elementSpacing = 2;  // Pixel spacing between elements

  // Menu system configuration
  std::vector<std::shared_ptr<MenuItem>> currentMenu;  // Currently displayed menu items
  std::stack<std::vector<std::shared_ptr<MenuItem>>> menuHistory;  // Stack for menu navigation history
  int selectedIndex = 0;    // Index of the currently selected menu item
  int scrollOffset = 0;     // Scroll position for long menus
  int visibleElements = 5;  // Number of menu items visible at once

  // Top bar customization options
  int statusBarBgColor = 1;    // Background color of the top bar
  int statusBarHeight = 13;    // Height of the top bar in pixels
  bool showStatusBar = true;   // Whether the top bar should be displayed

  // Display size (default 128x64)
  int displayVSize = 64;    // Vertical size (height)
  int displayHSize = 128;   // Horizontal size (width)

  // Whether the display should be rendered
  bool renderDisplay = true;

public:
  // Constructor - takes a reference to the display
  MenuDisplay(DisplayInterface& disp)
    : display(disp) {}  // Use initializer list to assign display reference

  // ========== STATUS BAR ELEMENT MANAGEMENT ==========

  void setElementSpacing(int spacing) {
    elementSpacing = spacing;
  }

  void addLeftElement(std::shared_ptr<StatusBarElement> element) {
    leftElements.push_back(element);
  }
  
  void addRightElement(std::shared_ptr<StatusBarElement> element) {
    rightElements.push_back(element);
  }

  void clearLeftElements();
  void clearRightElements();

  // ========== TOP BAR CONFIGURATION ==========

  void setStatusBarBackgroundColor(int color) {
    statusBarBgColor = color;
  }

  int getStatusBarBackgroundColor() {
    return statusBarBgColor;
  }

  void setStatusBarHeight(int height) {
    statusBarHeight = height;
  }

  void setShowStatusBar(bool show) {
    showStatusBar = show;
  }

  // ========== DISPLAY CONFIGURATION ==========

  void setDisplaySize(int width, int height) {
    displayHSize = width;
    displayVSize = height;
  }

  void setRenderDisplay(bool display) {
    renderDisplay = display;
  }

  bool isRenderDisplay() {
    return renderDisplay;
  }

  // ========== MENU MANAGEMENT METHODS ==========

  void setMenu(const std::vector<std::shared_ptr<MenuItem>>& menu);  // Set the active menu
  void scrollUp();      // Scroll up in the menu
  void scrollDown();    // Scroll down in the menu
  void select();        // Select the current item
  void goBack();        // Go back to the previous menu
  bool canGoBack() const;  // Check if back navigation is possible

  void setVisibleElements(int count) {
    visibleElements = max(1, count);
  }

  void render();  // Render the menu and status bar

private:
  // ========== PRIVATE RENDERING HELPERS ==========

  void renderLeftElements() const;          // Render left-aligned status bar elements
  void renderRightElements() const;         // Render right-aligned status bar elements
  void renderMenu() const;                  // Render the menu items
  void renderScrollIndicator() const;       // Render the scroll indicator
};

// End of header guard
#endif
