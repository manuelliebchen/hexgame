/*
 * Button.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#include "button.h"

Button::Button(std::function<void()> function, glm::vec2 position,
               glm::vec2 size)
    : function(function), position(position), size(size)
{
}

Button::~Button() {}

bool Button::click(glm::vec2 click_position) const
{
    if (click_position.x > position.x &&
        click_position.x < position.x + size.x &&
        click_position.y > position.y && click_position.y < position.y + size.y)
    {
        function();
        return true;
    }
    return false;
}

void Button::draw() const
{
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
};
