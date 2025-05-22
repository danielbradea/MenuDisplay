#ifndef STATUSBARELEMENT_H
#define STATUSBARELEMENT_H

#include <DisplayInterface.h>

// Enum to define possible positions of a status bar element
enum class StatusBarElementPosition {
    LEFT,   // Element will be aligned to the left side
    RIGHT   // Element will be aligned to the right side
};

// Base class for elements displayed in a status bar
class StatusBarElement {
protected:
    int x = 0;              // X coordinate of the element
    int y = 0;              // Y coordinate of the element
    int offsetX = 0;        // Horizontal offset for positioning
    int offsetY = 0;        // Vertical offset for positioning
    int color = 1;          // Color used for rendering the element
    StatusBarElementPosition position = StatusBarElementPosition::LEFT; // Default position

public:
    StatusBarElement() = default;

    // Virtual draw method to be overridden by subclasses
    // 'xx' and 'yy' are optional offsets for drawing
    virtual void draw(DisplayInterface& display, int xx = 0, int yy = 0) {}

    // Virtual method to return element width; override in subclasses
    virtual int getWidth() { return 0; }

    // Set and get methods for position and offset coordinates
    virtual void setX(int newX) { x = newX; }
    virtual void setY(int newY) { y = newY; }
    virtual int getX() const { return x; }
    virtual int getY() const { return y; }

    virtual void setOffsetX(int dx) { offsetX = dx; }
    virtual void setOffsetY(int dy) { offsetY = dy; }
    virtual int getOffsetX() const { return offsetX; }
    virtual int getOffsetY() const { return offsetY; }

    // Set and get the color used to draw the element
    virtual void setColor(uint16_t newColor) { color = newColor; }
    virtual uint16_t getColor() const { return color; }

    // Set and get the alignment position (left or right)
    virtual void setPosition(StatusBarElementPosition pos) { position = pos; }
    virtual StatusBarElementPosition getPosition() const { return position; }

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~StatusBarElement() = default;
};

#endif
