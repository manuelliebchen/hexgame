#ifndef _FIGURE_
#define _FIGURE_

#include <GL/glut.h>

#include "glm/glm.hpp"

#include "util.h"
#include "constants.h"

class Figure
{

public:
    virtual ~Figure(){};
    virtual void draw(glm::vec2 position) const = 0;
};

#endif
