#include "MenuDisplay.h"

// Main render function - draws all visual components to the screen
void MenuDisplay::render() {
  if (renderDisplay) {
    display.clearDisplay();
    if (showStatusBar) {
      // Draw top bar background or line if transparent
      if (statusBarBgColor == 0) {
        display.drawFastHLine(0, statusBarHeight, 128, 1);  // Transparent status bar
      } else {
        display.fillRect(0, 0, 128, statusBarHeight, statusBarBgColor);  // Filled top bar
      }
    }
    renderLeftElements();         // Draw left-aligned status symbols
    renderRightElements();        // Draw right-aligned status symbols
    renderMenu();                 // Draw menu items
    renderScrollIndicator();      // Draw scroll position indicator
    display.display();            // Commit changes to screen
  }
}

// Renders left-aligned status bar elements
void MenuDisplay::renderLeftElements() const {
  if (!showStatusBar) return;

  int x = 0;
  for (const auto& item : leftElements) {
    if (item) {
      item->setPosition(StatusBarElementPosition::LEFT);
      item->setColor(statusBarBgColor == 1 ? 0 : 1);  // Invert text color for contrast
      item->draw(display, x, 0);
      x += item->getWidth() + elementSpacing;
    }
  }
}

// Renders right-aligned status bar elements, clipped if necessary
void MenuDisplay::renderRightElements() const {
  if (!showStatusBar) return;

  int totalWidth = 0;
  int itemsToDraw = 0;

  // Calculate how many elements can fit
  for (int i = rightElements.size() - 1; i >= 0; --i) {
    const auto& item = rightElements[i];
    if (item) {
      int itemWidth = item->getWidth();
      int spacing = (totalWidth == 0) ? 0 : elementSpacing;

      if (totalWidth + itemWidth + spacing <= displayHSize) {
        totalWidth += itemWidth + spacing;
        ++itemsToDraw;
      } else {
        break;
      }
    }
  }

  int x = displayHSize - totalWidth;
  int drawn = 0;

  // Draw the calculated number of elements
  for (int i = rightElements.size() - 1; i >= 0 && drawn < itemsToDraw; --i) {
    const auto& item = rightElements[i];
    if (item) {
      item->setPosition(StatusBarElementPosition::RIGHT);
      item->setColor(statusBarBgColor == 1 ? 0 : 1);
      item->draw(display, x, 0);
      x += item->getWidth();
      if (++drawn < itemsToDraw) {
        x += elementSpacing;
      }
    }
  }
}

// Draws the visible portion of the menu
void MenuDisplay::renderMenu() const {
  constexpr int lineHeight = 10;
  constexpr int prefixWidth = 12;
  constexpr int charWidth = 6;

  const int startY = showStatusBar ? statusBarHeight + 2 : 0;
  const int scrollbarWidth = (currentMenu.size() > visibleElements) ? 3 : 0;
  const int contentWidth = display.width() - 4 - scrollbarWidth;

  display.setTextWrap(false);
  display.setTextColor(1);

  auto getVisibleText = [&](const std::string& label, bool isSelected, int availableWidth) -> std::string {
    if (!isSelected || label.length() * charWidth <= availableWidth)
      return label;

    if (!isScrollingManually) {
      int maxChars = availableWidth / charWidth;
      return (maxChars > 3) ? label.substr(0, maxChars - 3) + "..." : "...";
    }

    // Scroll manual: permitem un pas în plus ca ultimul caracter să fie complet vizibil
    int labelPixelWidth = label.length() * charWidth;
    int maxScroll = std::max(0, labelPixelWidth - availableWidth);
    int pixelOffset = std::min(manualScrollOffset, maxScroll);

    int currentX = 0, startChar = 0;
    while (startChar <= label.size() && currentX + charWidth <= pixelOffset) {
      currentX += charWidth;
      ++startChar;
    }

    std::string result;
    int drawnWidth = currentX - pixelOffset;

    for (size_t j = startChar; j < label.size() && drawnWidth + charWidth <= availableWidth; ++j) {
      result += label[j];
      drawnWidth += charWidth;
    }

    return result;
  };

  for (int i = 0; i < visibleElements; ++i) {
    int idx = scrollOffset + i;
    if (idx >= currentMenu.size()) break;

    const std::string& label = currentMenu[idx]->getLabel();
    bool isSelected = (idx == selectedIndex);
    int availableWidth = contentWidth - (isSelected ? prefixWidth : 0);
    int y = startY + i * lineHeight;

    // Clear background
    display.fillRect(2, y, display.width() - 4, lineHeight, 0);

    // Draw selection indicator
    int textStartX = 2;
    if (isSelected) {
      display.setCursor(textStartX, y);
      display.print("> ");
      textStartX += prefixWidth;
    }

    // Compute visible text
    std::string visibleText = getVisibleText(label, isSelected, availableWidth);

    // Draw text
    display.setCursor(textStartX, y);
    display.print(visibleText.c_str());
  }
}



// Renders the scroll indicator on the right side of the display
void MenuDisplay::renderScrollIndicator() const {
  int barX = displayHSize - 2;
  int totalItems = currentMenu.size();
  int scrollOffsetY = showStatusBar ? (statusBarHeight + 3) : 2;
  int barHeight = displayVSize - scrollOffsetY - 1;

  // Draw dotted vertical scrollbar
  for (int y = 0; y < barHeight; y++) {
    int pixelY = y + scrollOffsetY;
    if (y % 2 == 0) {
      display.drawPixel(barX, pixelY, 1);
    }
  }

  // Draw scroll position marker
  float percent = selectedIndex / (float)(totalItems - 1);
  int centerY = scrollOffsetY + (int)(percent * (barHeight - 1));

  for (int dy = -1; dy <= 1; dy++) {
    display.drawPixel(barX - 1, centerY + dy, 1);
    display.drawPixel(barX, centerY + dy, 1);
    display.drawPixel(barX + 1, centerY + dy, 1);
  }
}

// Sets the current menu and clears history
void MenuDisplay::setMenu(const std::vector<std::shared_ptr<MenuItem>>& menu) {
  currentMenu = menu;
  selectedIndex = scrollOffset = 0;
  while (!menuHistory.empty()) menuHistory.pop();
}

// Navigates one item up in the menu
void MenuDisplay::scrollUp() {
  if (selectedIndex > 0) {
    selectedIndex--;
    if (selectedIndex < scrollOffset) scrollOffset--;
  }
  manualScrollOffset = 0;
}

// Navigates one item down in the menu
void MenuDisplay::scrollDown() {
  if (selectedIndex < currentMenu.size() - 1) {
    selectedIndex++;
    if (selectedIndex >= scrollOffset + visibleElements) scrollOffset++;
  }
  manualScrollOffset = 0;
}

// Activates the selected menu item or enters a submenu
void MenuDisplay::select() {
  if (selectedIndex >= 0 && selectedIndex < currentMenu.size()) {
    auto selected = currentMenu[selectedIndex];
    if (selected && selected->hasSubmenu()) {
      menuHistory.push(currentMenu);
      currentMenu = selected->getSubmenu();
      selectedIndex = scrollOffset = 0;
    } else if (selected) {
      selected->activate();  // Execute menu action
    }
  }
  manualScrollOffset = 0;
}

// Returns to the previous menu (if available)
void MenuDisplay::goBack() {
  if (!menuHistory.empty()) {
    currentMenu = menuHistory.top();
    menuHistory.pop();
    selectedIndex = scrollOffset = 0;
  }
  manualScrollOffset = 0;
}

// Checks if it's possible to return to a previous menu
bool MenuDisplay::canGoBack() const {
  return !menuHistory.empty();
}

// Horizontal scrolling controls
void MenuDisplay::scrollLeft() {
   if (manualScrollOffset > 0) {
    manualScrollOffset = std::max(manualScrollOffset - charWidth, 0);
    if (manualScrollOffset == 0) {
      isScrollingManually = false;
    }
  }
  
}

void MenuDisplay::scrollRight() {
 if (selectedIndex >= 0 && selectedIndex < currentMenu.size()) {
    const std::string label = currentMenu[selectedIndex]->getLabel();
    const int textWidth = label.length() * charWidth;
    const int availableWidth = displayHSize - prefixWidth - 4; // Account for padding
    
    if (textWidth > availableWidth) {
      isScrollingManually = true;
      manualScrollOffset = std::min(
        manualScrollOffset + charWidth, 
        textWidth - availableWidth
      );
    }
  }
}

