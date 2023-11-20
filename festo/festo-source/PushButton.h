/** 
 * File:   PushButton.h
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

class PushButton{
private:
    unsigned int bitmask;
    bool inverseLogic;
    bool getState();
    bool positiveEvent();
    bool negativeEvent();
public:
    explicit PushButton(unsigned short bitmask);
    explicit PushButton(unsigned short bitmask, bool invert);
    void setInverseLogic();
    bool isPressed();
    bool isReleased();
    bool isPressEvent();
    bool isReleaseEvent();
};


#endif /* PUSHBUTTON_H */

