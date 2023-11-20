/** 
 * File:   BeltDrive.h
 * @author Lehmann
 * @date 2016-09-19
 * @version 1
 * Initial version
 * 
 */

#ifndef BELTDRIVE_H
#define BELTDRIVE_H

#define CONVEYERBELT_STOP       0
#define CONVEYERBELT_LEFT_SLOW  1
#define CONVEYERBELT_LEFT_FAST  2
#define CONVEYERBELT_RIGHT_SLOW 3
#define CONVEYERBELT_RIGHT_FAST 4

class BeltDrive{
private:
    static unsigned int objectCounter;
public:
    BeltDrive();
    void setSpeed(unsigned char mode);
};




#endif /* BELTDRIVE_H */

