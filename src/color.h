#ifndef _COLOR_
#define _COLOR_

struct Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Color() : red(0), green(0), blue(0){};

    Color(unsigned char _red, unsigned char _green, unsigned char _blue)
        : red(_red), green(_green), blue(_blue){};

    const Color& operator=(const Color& color)
    {
        red   = color.red;
        green = color.green;
        blue  = color.blue;
        return (*this);
    };
};

#endif
