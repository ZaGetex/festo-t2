/** 
 * File:   minilab1008processimage.h
 *
 * Class reads out the sensor values and controls actuators of the FESTO system 
 * via the MiniLab 1008 USB interface. 
 * 
 * @author Thomas Lehmann
 * @date 2017-11-12
 * @version 1
 * Initial version
 */

#ifndef MINILAB1008PROCESSIMAGE_H
#define	MINILAB1008PROCESSIMAGE_H
#ifdef SIMULATION
  #include "isimadapter.h"
  #include "simulation.h"
#endif
// if SIL is defined, no hardware interface is accessed or compiled in.
//#define SIL

// compiler option HOME to enforce Software in the Loop 
#ifdef HOME
  #define SIL
#endif

class MiniLab1008 {
    friend class FestoTransferSystem;
    friend class TimeHelper;
private:
    unsigned short process_image;
    unsigned short process_image_old;
    unsigned short process_image_change;
    unsigned short output_image;
    unsigned short height_analogue_value;
    static MiniLab1008* instance;
    MiniLab1008();
#ifdef SIMULATION
    ISimAdapter* adapter;
#endif
private:
    static MiniLab1008* getInstance();
public:
    virtual ~MiniLab1008();
public:
    void updateProcessImage(void);
    void applyOutputToProcess(void);
    unsigned char isBitSet(unsigned short bitMask);
    unsigned char isBitPosEdge(unsigned short bitMask);
    unsigned char isBitNegEdge(unsigned short bitMask);
    void setBitInOutput(unsigned short bitMask);
    void clearBitInOutput(unsigned short bitMask);
    void resetOutputs(void);
    unsigned short height();
    void sleep(unsigned long ms);
    unsigned int getMS();
#ifdef SIMULATION
    void updateSim(void);
private:
    unsigned long simTime = 0; // [ms]
#endif
private:
    void initProcessImageLayer(void);
};

#endif	/* PROCESSIMAGE_H */

