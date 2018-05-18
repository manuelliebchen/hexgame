#ifndef _TILE_
#define _TILE_

#include <GL/glut.h>

#include <map>

#include "color.h"
#include "figure.h"
#include "bush.h"
#include "coin.h"
#include "vec2.h"
#include "constants.h"

class Tile
{
    Figure* figure;
    Color   color_variation;
    int     height;

    Tile(const Tile& tile) = delete;
    const Tile& operator=(const Tile& tile) = delete;

public:
    Tile()
    {
        color_variation = Color(rand() % 16, rand() % 16, rand() % 16);
        height          = 1;
        figure          = nullptr;
    };
    ~Tile()
    {
        if (figure)
            delete figure;
    };
    Figure*& getFigure() { return figure; };
    bool     place(Figure* fig)
    {
        if (figure)
            return false;
        figure = fig;
        return true;
    }
    void clear()
    {
        delete figure;
        figure = nullptr;
    };
    void raise(int amount)
    {
        height += amount;
        if (height <= 0)
        {
            clear();
        }
    };

    void moveFigureTo(Tile* tile)
    {
        tile->clear();
        tile->place(figure);
        figure = nullptr;
    }

    int  getHeight() const { return height; };
    bool isWalkable() const { return (height > 0 && !figure); };

    void draw(vec2 position, const std::map<int, Color>& color_map) const;
    void mark(vec2 translation) const;

    void plant()
    {
        if (height > 0)
        {
            place(new Bush());
        }
    };
};

#endif
