/*
 * Button.h
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <GL/glut.h>
#include <functional>

#include "glm/glm.hpp"

#include "field.h"
#include "guielement.h"

class Button : public GuiElement
{
public:
    Button(std::function<void()> function, glm::vec2 position, glm::vec2 size);
    virtual ~Button();

    bool         click(glm::vec2 click_position) const;
    bool         in_region(glm::vec2 click_position) const;
    virtual void draw() const;

private:
    std::function<void()> function;

    glm::vec2 position;
    glm::vec2 size;
};

#endif /* SRC_BUTTON_H_ */
