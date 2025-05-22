// Header guard to prevent multiple inclusions
#ifndef MENU_ITEM_H
#define MENU_ITEM_H

// Include necessary standard libraries
#include <string>       // For std::string
#include <vector>       // For std::vector
#include <memory>       // For std::shared_ptr
#include <functional>   // For std::function

// MenuItem class declaration
class MenuItem {
private:
  // Private member variables:
  std::string label;  // The text displayed for this menu item
  std::function<void()> action;  // Callback function when item is activated
  std::vector<std::shared_ptr<MenuItem>> submenu;  // List of submenu items

public:
  // Constructor - creates a new menu item with specified label and optional action
  // Parameters:
  //   label - the text to display for this menu item
  //   action - optional callback function (defaults to nullptr)
  MenuItem(const std::string& label, std::function<void()> action = nullptr)
    : label(label), action(action) {}  // Initializer list sets members

  // Get the label text of this menu item
  // Returns: constant reference to the label string
  const std::string& getLabel() const {
    return label;
  }

  // Set a submenu for this item
  // Parameters:
  //   items - vector of shared pointers to MenuItems that will form the submenu
  void setSubmenu(const std::vector<std::shared_ptr<MenuItem>>& items) {
    submenu = items;  // Copy the submenu items
  }

  // Check if this item has a submenu
  // Returns: true if submenu is not empty, false otherwise
  bool hasSubmenu() const {
    return !submenu.empty();  // Returns true if submenu has items
  }

  // Get the submenu items
  // Returns: constant reference to the vector of submenu items
  const std::vector<std::shared_ptr<MenuItem>>& getSubmenu() const {
    return submenu;
  }

  // Activate this menu item (execute its action)
  void activate() const {
    if (action) action();  // Only call if action is set (not nullptr)
  }
};

// End of header guard
#endif