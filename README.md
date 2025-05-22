# MenuDisplay

## Description

**MenuDisplay** is an advanced scrolling menu system for embedded displays.  
It implements a customizable menu with vertical scrolling navigation, horizontal text scrolling for long items, dynamic icons, and submenu support.

Designed for microcontrollers such as **ESP32** and **AVR-based boards**, it works seamlessly with displays using the **Adafruit GFX Library**.

---

## Features

- ✅ Vertical navigation with automatic scroll
- 📝 Horizontal text scrolling for long labels
- 📁 Submenu support (nested menus)
- ⚙️ Easy integration with callback actions
- 🖥️ Abstracted rendering via `DisplayInterface` for portability
- 📦 Includes a concrete display implementation for SH1106
- 💡 Extendable with custom UI elements (e.g., status bars, icons)

---

## Getting Started

### Requirements

- Arduino IDE or PlatformIO
- Adafruit GFX-compatible display (e.g., SH1106, SSD1306)
- Adafruit GFX Library

### Installation

Install the library via the **Arduino Library Manager** or manually:

```bash
git clone https://github.com/danielbradea/MenuDisplay.git
```

Copy the folder to your Arduino libraries directory.

---

## Example

```cpp
#include <MenuItem.h>
#include <MenuBuilder.h>
#include <DisplaySH1106G.h>

// Callback function
void onHelloSelected() {
    Serial.println("Hello selected!");
}

// Display object
DisplaySH1106G display(128, 64, -1);

void setup() {
    Serial.begin(115200);
    display.begin();

    // Create menu items
    auto item1 = MenuBuilder::createItem("Say Hello", onHelloSelected);
    auto item2 = MenuBuilder::createItem("Option 2");
    auto submenu = MenuBuilder::createMenu("Submenu", {
        MenuBuilder::createItem("Sub 1"),
        MenuBuilder::createItem("Sub 2")
    });

    std::vector<std::shared_ptr<MenuItem>> menuItems = { item1, item2, submenu };

    // Custom rendering and navigation code goes here
}
```

> You must implement your own rendering and input handling using the `DisplayInterface`.

---

## File Overview

- `MenuItem.h` – Represents menu items with optional submenus and actions
- `MenuBuilder.h` – Factory methods for easy menu creation
- `DisplayInterface.h` – Abstract class for rendering methods
- `DisplaySH1106G.h` – Implementation of `DisplayInterface` using Adafruit SH1106
- `StatusBarElement.h` – Base for on-screen status elements (icons, labels, etc.)

---

