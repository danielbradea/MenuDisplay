# Menu Display System

A flexible menu system for embedded displays (designed for 128x64 OLED screens) with support for:
- Hierarchical menus with navigation
- Top bar with left/right aligned icons
- Scrolling for long menus
- Customizable appearance

## Features

### Menu System
- **Hierarchical navigation** - Support for nested submenus with back navigation
- **Dynamic scrolling** - Handles menus longer than visible area
- **Text scrolling** - Automatic horizontal scrolling for long menu items
- **Visual feedback** - Clear selection indicator (">" prefix)

### Top Bar
- **Customizable appearance** - Adjustable height and background color
- **Icon support** - Left and right-aligned icons with configurable spacing
- **Dynamic layout** - Icons automatically adjust to available space

### Technical Details
- **Adafruit GFX compatible** - Works with any display supporting Adafruit_GFX
- **Memory efficient** - Uses smart pointers and STL containers
- **Responsive design** - Adapts to different display sizes

## Class Structure

### MenuDisplay (`MenuDisplay.h`/`MenuDisplay.cpp`)
The main class handling menu rendering and navigation.

#### Public Methods:
- **Navigation**:
  - `scrollUp()`/`scrollDown()` - Move selection
  - `select()` - Activate current item
  - `goBack()` - Return to previous menu
  - `canGoBack()` - Check if back navigation is available

- **Configuration**:
  - `setMenu()` - Set the current menu items
  - `setVisibleItems()` - Set how many items show at once
  - `setTopBarBackgroundColor()`/`setTopBarHeight()` - Customize top bar
  - `setShowTopBar()` - Show/hide top bar
  - `setDisplaySize()` - For non-standard displays

- **Icon Management**:
  - `addLeftIcon()`/`addRightIcon()` - Add icons to top bar
  - `clearLeftIcons()`/`clearRightIcons()` - Remove all icons

- **Rendering**:
  - `update()` - Redraws the entire display

### MenuItem (`MenuItem.h`)
Represents an individual menu item with optional submenu and action.

#### Key Methods:
- `getLabel()` - Returns the display text
- `hasSubmenu()` - Checks if item has submenu
- `getSubmenu()` - Returns submenu items
- `activate()` - Executes the item's action

## Usage Example

```cpp
// Create display instance
Adafruit_SSD1306 display(128, 64, &Wire);
MenuDisplay menu(display);

// Create menu items
auto mainMenu = {
  std::make_shared<MenuItem>("Settings", []{ /* open settings */ }),
  std::make_shared<MenuItem>("Info")
};

// Set the menu
menu.setMenu(mainMenu);

// In main loop:
void loop() {
  menu.update();
  
  if (buttonPressed(UP)) menu.scrollUp();
  if (buttonPressed(DOWN)) menu.scrollDown();
  if (buttonPressed(SELECT)) menu.select();
  if (buttonPressed(BACK)) menu.goBack();
}