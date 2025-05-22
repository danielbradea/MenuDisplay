// IIcon.h
#ifndef IIcon_H
#define IIcon_H

#include <Adafruit_GFX.h>

enum class IconPosition {
    LEFT,
    RIGHT
};


class IIcon {
public:
    /**
     * Draws the icon on the display with optional offset from base position
     * @param display Reference to the display object
     * @param xx Horizontal offset from base X position
     * @param yy Vertical offset from base Y position
     */
    virtual void draw(Adafruit_GFX& display, int xx = 0, int yy = 0) = 0;
    
    /**
     * Gets the width of the icon in pixels
     * @return Icon width in pixels
     */
    virtual int getWidth() = 0;
    
    // Position methods
    virtual void setX(int x) = 0;      ///< Sets base X position
    virtual void setY(int y) = 0;      ///< Sets base Y position
    virtual int getX() const = 0;      ///< Gets base X position
    virtual int getY() const = 0;      ///< Gets base Y position
    
    // Color control
    virtual void setColor(uint16_t color) = 0;  ///< Sets drawing color
    virtual uint16_t getColor() const = 0;      ///< Gets current drawing color

    virtual void setPosition(IconPosition position) = 0;
    virtual IconPosition getPosition() const = 0;
    
    virtual ~IIcon() = default;
};

#endif