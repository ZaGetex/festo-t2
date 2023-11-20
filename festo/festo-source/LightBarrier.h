/**
 * File:   LightBarrier.h
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef LIGHTBARRIER_H
#define LIGHTBARRIER_H

class LightBarrier{
private:
    unsigned int bitmask;
    bool getState();
public:
    explicit LightBarrier(unsigned short bitmask);
    bool isOpen();
    bool isClosed();
};

#endif /* LIGHTBARRIER_H */

