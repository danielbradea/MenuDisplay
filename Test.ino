#include "PixelBattery.h"
#include "MenuDisplay.h"
#include "MenuItem.h"
#include "PixelBle.h"
#include "MenuBuilder.h"
#include "DisplaySH1106G.h"

// OLED display settings
#define SDA_PIN 8
#define SCL_PIN 9
#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Initialize the display and menu system
DisplaySH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);
MenuDisplay menu(display);

// Shared status icons
std::shared_ptr<PixelBattery> battery = std::make_shared<PixelBattery>();
std::shared_ptr<PixelBle> bleIcon = std::make_shared<PixelBle>();

void setup() {
  Serial.begin(115200);
  delay(2000); // Allow hardware to stabilize
  display.begin();

  // === Build Menu Structure ===

  // WiFi menu items
  auto wifiScanItem = MenuBuilder::createItem("WiFi Scanner");
  auto wifiSettingsItem = MenuBuilder::createItem("WiFi Settings");
  auto wifiMenu = MenuBuilder::createMenu("WiFi", { wifiScanItem, wifiSettingsItem });

  // Bluetooth menu items
  auto bluetoothScanItem = MenuBuilder::createItem("Scan Devices");
  auto bluetoothPairItem = MenuBuilder::createItem("Pair Device");
  auto bluetoothMenu = MenuBuilder::createMenu("Bluetooth", { bluetoothScanItem, bluetoothPairItem });

  // Other main menu items
  auto infoItem = MenuBuilder::createItem("Info");
  auto settingsItem = MenuBuilder::createItem("Settings");
  auto aboutItem = MenuBuilder::createItem("About");

  // Root menu combining all top-level items
  std::vector<std::shared_ptr<MenuItem>> rootMenu = {
    wifiMenu,
    bluetoothMenu,
    infoItem,
    settingsItem,
    aboutItem
  };

  // === Configure status bar icons ===
  battery->setOffsetX(2);
  battery->setOffsetY(2);
  battery->setShowPercent(true); // Show battery percentage

  bleIcon->setOffsetX(2);
  bleIcon->setOffsetY(2);
  bleIcon->setIsConnected(true); // Assume BLE is connected

  menu.addLeftElement(bleIcon);
  menu.addRightElement(battery);
  menu.setStatusBarBackgroundColor(1); // Set initial status bar background
  menu.setMenu(rootMenu); // Display the main menu
}

// === Battery level and status bar update variables ===
int batteryLevel = 0;
unsigned long lastBatteryUpdate = 0;
const unsigned long batteryUpdateInterval = 500;  // milliseconds
int colorToggleCounter = 0;

void loop() {
  menu.render(); // Draw menu and status icons

  // === Update battery level and toggle icons every 500ms ===
  if (millis() - lastBatteryUpdate > batteryUpdateInterval) {
    batteryLevel += 10;
    if (batteryLevel > 100) {
      batteryLevel = 0;
      colorToggleCounter++;

      // Every third cycle, toggle the status bar background color
      if (colorToggleCounter >= 3) {
        colorToggleCounter = 0;
        bool currentColor = menu.getStatusBarBackgroundColor();
        menu.setStatusBarBackgroundColor(!currentColor);
      }

      // Simulate BLE connection change and toggle battery percentage visibility
      bleIcon->setIsConnected(!bleIcon->getIsConnected());
      battery->setShowPercent(!battery->getShowPercent());
    }

    battery->setLevel(batteryLevel);
    lastBatteryUpdate = millis();
  }

  // === Handle Serial Monitor input for menu navigation ===
  if (Serial.available()) {
    char input = Serial.read();
    if (input == 'w') {
      menu.scrollUp();      // Move up in the menu
    } else if (input == 's') {
      menu.scrollDown();    // Move down in the menu
    } else if (input == 'e') {
      menu.select();        // Select the current item
    } else if (input == 'q') {
      menu.goBack();        // Return to previous menu
    }
  }
}
