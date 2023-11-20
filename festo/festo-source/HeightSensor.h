/**
 * File:   HeightSensor.h
 * @author Thomas Lehmann
 * @date 2016-10-12
 * @version 1
 * Initial version
 */

#ifndef HEIGHTSENSOR_H
#define HEIGHTSENSOR_H

class HeightSensor{
private:
    unsigned int bitmask;
    bool getState();
public:
    explicit HeightSensor(unsigned short bitmask);
    bool isHeightCorrect();
};


#endif /* HEIGHTSENSOR_H */

