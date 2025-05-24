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
  std::vector<std::shared_ptr<StatusBarElement>> leftElements;   // Left-aligned status bar elements
  std::vector<std::shared_ptr<StatusBarElement>> rightElements;  // Right-aligned status bar elements
  int elementSpacing = 2;  // Pixel spacing between status bar elements

  // Menu system configuration
  std::vector<std::shared_ptr<MenuItem>> currentMenu;  // Currently displayed menu items
  std::stack<std::vector<std::shared_ptr<MenuItem>>> menuHistory;  // Menu navigation history stack
  int selectedIndex = 0;    // Index of currently selected menu item
  int scrollOffset = 0;     // Vertical scroll position for long menus
  int visibleElements = 5;  // Number of visible menu items at once

  // Horizontal scrolling control
  int manualScrollOffset = 0;       // Current horizontal scroll offset
  bool isScrollingManually = false; // Whether manual scrolling is active
  const int charWidth = 6;          // Monospace character width (pixels)
  const int prefixWidth = 12;       // Width for "> " prefix before selected item

  // Top bar customization options
  int statusBarBgColor = 1;    // Status bar background color (0/1 for monochrome)
  int statusBarHeight = 13;    // Status bar height in pixels
  bool showStatusBar = true;   // Whether to show status bar

  // Display dimensions (default 128x64)
  int displayVSize = 64;    // Vertical size (height)
  int displayHSize = 128;   // Horizontal size (width)

  // Display control flag
  bool renderDisplay = true;  // Whether to render the display

public:
  // Constructor - takes a reference to the display
  MenuDisplay(DisplayInterface& disp)
    : display(disp) {}  // Initialize display reference

  // ========== STATUS BAR ELEMENT MANAGEMENT ==========

  // Set spacing between status bar elements
  void setElementSpacing(int spacing) {
    elementSpacing = spacing;
  }

  // Add element to left side of status bar
  void addLeftElement(std::shared_ptr<StatusBarElement> element) {
    leftElements.push_back(element);
  }
  
  // Add element to right side of status bar
  void addRightElement(std::shared_ptr<StatusBarElement> element) {
    rightElements.push_back(element);
  }

  // Clear all left/right status bar elements
  void clearLeftElements();
  void clearRightElements();

  // ========== TOP BAR CONFIGURATION ==========

  // Set status bar background color
  void setStatusBarBackgroundColor(int color) {
    statusBarBgColor = color;
  }

  // Get current status bar color
  int getStatusBarBackgroundColor() {
    return statusBarBgColor;
  }

  // Set status bar height
  void setStatusBarHeight(int height) {
    statusBarHeight = height;
  }

  // Show/hide status bar
  void setShowStatusBar(bool show) {
    showStatusBar = show;
  }

  // ========== DISPLAY CONFIGURATION ==========

  // Set display dimensions
  void setDisplaySize(int width, int height) {
    displayHSize = width;
    displayVSize = height;
  }

  // Enable/disable display rendering
  void setRenderDisplay(bool isRender) {
    renderDisplay = isRender;
  }

  // Check if rendering is enabled
  bool isRenderDisplay() {
    return renderDisplay;
  }

  // ========== MENU MANAGEMENT METHODS ==========

  // Core menu functions
  void setMenu(const std::vector<std::shared_ptr<MenuItem>>& menu);  // Set active menu
  void scrollUp();      // Move selection up
  void scrollDown();    // Move selection down
  void scrollLeft();    // Scroll text left (for long items)
  void scrollRight();   // Scroll text right (for long items)
  void select();        // Activate selected item
  void goBack();        // Return to previous menu
  bool canGoBack() const;  // Check if back navigation is possible

  // Set number of visible menu items
  void setVisibleElements(int count) {
    visibleElements = max(1, count);  // Ensure at least 1 item is visible
  }

  // Main rendering function
  void render();  // Render entire display

private:
  // ========== PRIVATE RENDERING HELPERS ==========

  void renderLeftElements() const;     // Render left status bar elements
  void renderRightElements() const;    // Render right status bar elements
  void renderMenu() const;             // Render menu items
  void renderScrollIndicator() const;  // Render vertical scrollbar
};

#endif // MENU_DISPLAY_H