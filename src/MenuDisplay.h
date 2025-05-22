// Header guard to prevent multiple inclusions
#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

// Include necessary libraries
#include <Adafruit_GFX.h>  // Graphics library for display
#include <vector>          // For dynamic arrays
#include <memory>          // For smart pointers
#include <stack>           // For menu history stack
#include "IIcon.h"         // Icon interface
#include "MenuItem.h"      // Menu item class

// MenuDisplay class declaration
class MenuDisplay {
private:
  // Reference to the display object (using Adafruit GFX)
  Adafruit_GFX& display;

  // Icon bar configuration
  std::vector<std::shared_ptr<IIcon>> leftIcons;   // Icons on left side of top bar
  std::vector<std::shared_ptr<IIcon>> rightIcons;  // Icons on right side of top bar
  int iconSpacing = 2;  // Space between icons in pixels

  // Menu system configuration
  std::vector<std::shared_ptr<MenuItem>> currentMenu;  // Currently displayed menu items
  std::stack<std::vector<std::shared_ptr<MenuItem>>> menuHistory;  // Menu navigation history
  int selectedIndex = 0;    // Currently selected menu item index
  int scrollOffset = 0;     // Scroll position for long menus
  int visibleItems = 5;     // Number of menu items visible at once

  // Top bar customization options
  int topBarBgColor = 1;    // Background color of top bar
  int topBarHeight = 13;    // Height of top bar in pixels
  bool showTopBar = true;   // Whether to show top bar

  // Display dimensions (default 128x64)
  int displayVSize = 64;    // Vertical size (height)
  int displayHSize = 128;   // Horizontal size (width)

public:
  // Constructor - takes a reference to the display
  MenuDisplay(Adafruit_GFX& disp)
    : display(disp) {}  // Initializer list sets display reference

  // ========== ICON MANAGEMENT METHODS ==========

  // Set spacing between icons
  void setIconSpacing(int spacing) {
    iconSpacing = spacing;
  }
  
  // Add icon to left side (implementation in .cpp)
  void addLeftIcon(std::shared_ptr<IIcon> icon);
  
  // Add icon to right side (implementation in .cpp)
  void addRightIcon(std::shared_ptr<IIcon> icon);
  
  // Clear all left icons
  void clearLeftIcons();
  
  // Clear all right icons
  void clearRightIcons();

  // ========== TOP BAR CONFIGURATION ==========

  // Set top bar background color
  void setTopBarBackgroundColor(int color) {
    topBarBgColor = color;
  }
  
  // Set top bar height
  void setTopBarHeight(int height) {
    topBarHeight = height;
  }
  
  // Show/hide top bar
  void setShowTopBar(bool show) {
    showTopBar = show;
  }

  // ========== DISPLAY CONFIGURATION ==========

  // Set custom display dimensions (if different from default 128x64)
  void setDisplaySize(int width, int height) {
    displayHSize = width;
    displayVSize = height;
  }

  // ========== MENU MANAGEMENT METHODS ==========

  // Set current menu (replaces existing menu)
  void setMenu(const std::vector<std::shared_ptr<MenuItem>>& menu);
  
  // Navigation methods
  void scrollUp();      // Move selection up
  void scrollDown();    // Move selection down
  void select();        // Select current item
  void goBack();        // Return to previous menu
  bool canGoBack() const; // Check if back navigation is possible
  
  // Set number of visible menu items (constrained between 1 and 10)
  void setVisibleItems(int count) {
    visibleItems = max(1, count);
  }
  
  // Update/redraw entire display
  void update();

private:
  // ========== PRIVATE DRAWING METHODS ==========
  
  void drawLeftIcons() const;    // Draw left-aligned icons
  void drawRightIcons() const;   // Draw right-aligned icons
  void drawTopBar() const;       // Draw top bar background
  void drawMenu() const;         // Draw menu items
  void drawScrollBar() const;    // Draw scroll indicator
};

// End of header guard
#endif