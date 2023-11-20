/** 
 * File:   MetalDetector.h
 * @author Thomas Lehmann
 * @date 2016-10-12
 * @version 1
 * Initial version
 */

#ifndef METALDETECTOR_H
#define METALDETECTOR_H

class MetalDetector{
private:
    unsigned int bitmask;
    bool getState();
public:
    explicit MetalDetector(unsigned short bitmask);
    bool isMetalDetected();
};


#endif /* METALDETECTOR_H */

