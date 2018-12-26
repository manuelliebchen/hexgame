/*
 * GUI.h
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include <vector>

#include "glm/glm.hpp"

#include "guielement.h"
#include "button.h"

class GUI
{
public:
    GUI();
    virtual ~GUI();

    bool click(glm::vec2 position);
    bool in_region(glm::vec2 position) const;
    void draw() const;

    void addButton(Button* b);

private:
    std::vector<GuiElement*> elements;
    float                    scaling_factor;
};

#endif /* SRC_GUI_H_ */
