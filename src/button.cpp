/*
 * Button.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#include "button.h"

Button::Button(std::basic_string<unsigned char> text,
               std::function<void()> function, glm::vec2 position,
               glm::vec2 size)
    : text(text), function(function), position(position), size(size)
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

bool Button::in_region(glm::vec2 click_position) const
{
    if (click_position.x > position.x &&
        click_position.x < position.x + size.x &&
        click_position.y > position.y && click_position.y < position.y + size.y)
    {
        return true;
    }
    return false;
}

void Button::draw() const
{
    glColor3ub(128, 128, 128);
    glBegin(GL_POLYGON);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();

    void* font = GLUT_BITMAP_TIMES_ROMAN_24;
    glColor3ub(255, 255, 255);
    int w = glutBitmapLength(font, text.c_str());
    //    int h = glutBitmapHeight(font);
    int h = 25;
    glRasterPos2f(position.x + (size.x - w) * 0.5,
                  position.y + (size.y - h) * 0.5);
    int len = text.length();
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
};
