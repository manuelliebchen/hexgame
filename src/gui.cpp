/*
 * GUI.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#include "gui.h"

GUI::GUI() : scaling_factor(1) {}

GUI::~GUI()
{
    for (GuiElement* g : elements)
    {
        delete g;
    }
}

bool GUI::click(glm::vec2 position)
{
    bool clicked = false;
    for (GuiElement* e : elements)
    {
        if (Button* b = dynamic_cast<Button*>(e))
        {
            clicked |= b->click(position);
        }
    }
    return clicked;
}

void GUI::draw() const
{
    for (const GuiElement* e : elements)
    {
        e->draw();
    }
}

void GUI::addButton(Button* b)
{
    elements.push_back(b);
}
