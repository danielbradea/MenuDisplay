#include "MenuDisplay.h"

// Main update function - redraws all display components
void MenuDisplay::update() {
  // Draw top bar if enabled
  if (showTopBar) {
    if (topBarBgColor == 0) {
      // Draw a simple line if background is transparent (color 0)
      display.drawFastHLine(0, topBarHeight, 128, 1);
    } else {
      // Fill the top bar with background color
      display.fillRect(0, 0, 128, topBarHeight, topBarBgColor);
    }
  }

  // Draw all display components
  drawLeftIcons();    // Left-aligned icons
  drawRightIcons();   // Right-aligned icons
  drawMenu();         // Menu items
  drawScrollBar();    // Scroll indicator
}

// Draw left-aligned icons in top bar
void MenuDisplay::drawLeftIcons() const {
  if (!showTopBar) return;  // Skip if top bar is hidden

  int x = 0;  // Start position for first icon
  for (size_t i = 0; i < leftIcons.size(); ++i) {
    const auto& icon = leftIcons[i];
    if (icon) {
      icon->setPosition(IconPosition::LEFT);  // Set left alignment
      int width = icon->getWidth();
      
      // Set icon color based on top bar background (contrast)
      topBarBgColor == 1 ? icon->setColor(0) : icon->setColor(1);
      
      // Add spacing after first icon
      if (i > 0) {
        x += width;
        x += iconSpacing;
      }
      
      // Draw the icon at calculated position
      icon->draw(display, x, 0);
    }
  }
}

// Draw right-aligned icons in top bar
void MenuDisplay::drawRightIcons() const {
  if (!showTopBar) return;  // Skip if top bar is hidden

  int totalWidth = 0;
  int iconsToDraw = 0;

  // Calculate total width needed and how many icons fit
  for (int i = rightIcons.size() - 1; i >= 0; --i) {
    const auto& icon = rightIcons[i];
    if (icon) {
      int iconWidth = icon->getWidth();
      int spacing = (totalWidth == 0) ? 0 : iconSpacing;

      // Check if icon fits in remaining space
      if (totalWidth + iconWidth + spacing <= displayHSize) {
        totalWidth += iconWidth + spacing;
        ++iconsToDraw;
      } else {
        break;  // Stop when no more space
      }
    }
  }

  // Draw icons from right to left
  int x = displayHSize - totalWidth;  // Starting position
  int drawn = 0;  // Counter for drawn icons

  for (int i = rightIcons.size() - 1; i >= 0 && drawn < iconsToDraw; --i) {
    const auto& icon = rightIcons[i];
    if (icon) {
      int iconWidth = icon->getWidth();

      icon->setPosition(IconPosition::RIGHT);  // Set right alignment
      topBarBgColor == 1 ? icon->setColor(0) : icon->setColor(1);

      // Draw icon and move position right
      icon->draw(display, x, 0);
      x += iconWidth;

      ++drawn;
      // Add spacing between icons
      if (drawn < iconsToDraw) {
        x += iconSpacing;
      }
    }
  }
}

// Draw the menu items
void MenuDisplay::drawMenu() const {
  int startY = showTopBar ? topBarHeight + 2 : 0;  // Start below top bar
  int lineHeight = 10;  // Height of each menu item
  int scrollbarWidth = (currentMenu.size() > visibleItems) ? 3 : 0;  // Scrollbar space
  int maxWidth = display.width() - 4 - scrollbarWidth;  // Available width for text

  unsigned long currentMillis = millis();  // For scrolling animation

  for (int i = 0; i < visibleItems; ++i) {
    int idx = scrollOffset + i;  // Actual menu index
    if (idx >= currentMenu.size()) break;  // Skip if beyond menu items

    std::string label = currentMenu[idx]->getLabel();
    int textWidth = label.length() * 6;  // 6px per character (monospace)

    // Space for "> " prefix if selected
    int prefixWidth = (idx == selectedIndex) ? 12 : 0;
    int availableWidth = maxWidth - prefixWidth;

    // Calculate horizontal scroll position for long selected items
    int scrollX = 0;
    if (idx == selectedIndex && textWidth > availableWidth) {
      int overflow = textWidth - availableWidth;
      unsigned long scrollInterval = 40;  // ms per step
      unsigned long totalCycle = overflow * 2;  // Forth and back
      unsigned long step = (currentMillis / scrollInterval) % totalCycle;

      // Calculate scroll position (ping-pong)
      if (step > overflow) {
        scrollX = (int)(step - overflow);  // Returning
      } else {
        scrollX = (int)(overflow - step);  // Going
      }
      scrollX = -scrollX;  // Negative for left scroll
    }

    // Clear the line
    display.fillRect(0, startY + i * lineHeight - 1, display.width(), lineHeight, 0);
    display.setTextWrap(false);
    display.setTextColor(1);  // White text

    // Draw "> " prefix for selected item
    int textStartX = 0;
    if (idx == selectedIndex) {
      display.setCursor(0, startY + i * lineHeight);
      display.print("> ");
      textStartX = prefixWidth;  // Offset after prefix
    }

    // Draw the menu text (with scrolling if needed)
    display.setCursor(textStartX + scrollX, startY + i * lineHeight);
    display.print(label.c_str());
  }
}

// Set new menu and reset navigation state
void MenuDisplay::setMenu(const std::vector<std::shared_ptr<MenuItem>>& menu) {
  currentMenu = menu;
  selectedIndex = scrollOffset = 0;  // Reset position
  while (!menuHistory.empty()) menuHistory.pop();  // Clear history
}

// Move selection up
void MenuDisplay::scrollUp() {
  if (selectedIndex > 0) {
    selectedIndex--;
    // Adjust scroll offset if needed
    if (selectedIndex < scrollOffset) scrollOffset--;
  }
}

// Move selection down
void MenuDisplay::scrollDown() {
  if (selectedIndex < currentMenu.size() - 1) {
    selectedIndex++;
    // Adjust scroll offset if needed
    if (selectedIndex >= scrollOffset + visibleItems) scrollOffset++;
  }
}

// Handle menu item selection
void MenuDisplay::select() {
  auto selected = currentMenu[selectedIndex];
  if (selected && selected->hasSubmenu()) {
    // Push current menu to history and open submenu
    menuHistory.push(currentMenu);
    currentMenu = selected->getSubmenu();
    selectedIndex = scrollOffset = 0;  // Reset position
  } else if (selected) {
    // Execute item action
    selected->activate();
  }
}

// Navigate back to previous menu
void MenuDisplay::goBack() {
  if (!menuHistory.empty()) {
    currentMenu = menuHistory.top();  // Restore previous menu
    menuHistory.pop();
    selectedIndex = scrollOffset = 0;  // Reset position
  }
}

// Draw scroll bar indicator
void MenuDisplay::drawScrollBar() const {
  if (currentMenu.size() <= visibleItems) return;  // Skip if no scrolling needed

  int barX = displayHSize - 2;  // Position from right edge
  int totalItems = currentMenu.size();

  // Calculate scroll bar area
  int scrollOffsetY = showTopBar ? (topBarHeight + 3) : 2;
  int barHeight = displayVSize - scrollOffsetY - 1;

  // Draw dotted line
  for (int y = 0; y < barHeight; y++) {
    int pixelY = y + scrollOffsetY;
    if (y % 2 == 0) {  // Every other pixel
      display.drawPixel(barX, pixelY, 1);
    }
  }

  // Calculate scroll position indicator
  float percent = selectedIndex / (float)(totalItems - 1);
  int centerY = scrollOffsetY + (int)(percent * (barHeight - 1));

  // Draw 3x3 position indicator
  for (int dy = -1; dy <= 1; dy++) {
    display.drawPixel(barX - 1, centerY + dy, 1);
    display.drawPixel(barX,     centerY + dy, 1);
    display.drawPixel(barX + 1, centerY + dy, 1);
  }
}

// Check if back navigation is possible
bool MenuDisplay::canGoBack() const {
  return !menuHistory.empty();  // True if history has menus
}

// Add icon to left side
void MenuDisplay::addLeftIcon(std::shared_ptr<IIcon> icon) {
  leftIcons.push_back(icon);
}

// Add icon to right side
void MenuDisplay::addRightIcon(std::shared_ptr<IIcon> icon) {
  rightIcons.push_back(icon);
}

// Clear all left icons
void MenuDisplay::clearLeftIcons() {
  leftIcons.clear();
}

// Clear all right icons
void MenuDisplay::clearRightIcons() {
  rightIcons.clear();
}