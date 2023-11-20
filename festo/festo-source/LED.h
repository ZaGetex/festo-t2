/** 
 * File:   LED.h
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef LED_H
#define LED_H

class LED{
private:
    unsigned int bitmask;
    void setState(bool state);
public:
    explicit LED(unsigned short bitmask);
    void switchOn();
    void switchOff();
};

#endif /* LED_H */

