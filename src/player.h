#ifndef _PLAYER_
#define _PLAYER_

#include "constants.h"
#include "vec2.h"
#include "figure.h"
#include "tile.h"

class Player : public Figure
{
public:
    Player(Tile* _standing_on) : standing_on(_standing_on){};
    Tile* standing_on = nullptr;
    void  move(Tile* move_to)
    {
        standing_on->moveFigureTo(move_to);
        standing_on = move_to;
    };
    void draw(vec2 position) const;
};

#endif
