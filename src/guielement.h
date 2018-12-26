/*
 * guielement.h
 *
 *  Created on: Dec 22, 2018
 *      Author: jemand
 */

#ifndef SRC_GUIELEMENT_H_
#define SRC_GUIELEMENT_H_

class GuiElement
{
public:
    GuiElement(){};
    virtual ~GuiElement(){};

    virtual void draw() const = 0;
};

#endif /* SRC_GUIELEMENT_H_ */
