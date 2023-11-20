/** 
 * File:   minilab1008processimage.cpp
 *
 * Class reads out the sensor values and controls actuators of the FESTO system 
 * via the MiniLab 1008 USB interface. 
 * 
 * @author Thomas Lehmann
 * @date 2016-09-26
 * @version 1
 * Initial version
 */

#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>
#include "minilab1008.h"
#include "TimeHelper.h"
#ifdef SIMULATION
#if !defined(SIMLONGRUN) && !defined(SIMTESTS)
#include "simadapter.h"
#elif defined(SIMLONGRUN) && !defined(SIMTESTS)
#include "simadapter_longrun.h"
#elif defined(SIMTESTS) && !defined(SIMLONGRUN)
#include "simadapter_tests.h"
#else
#error SIMTESTS und SIMLONGRUN wurden definiert, maximal eines dieser Defines darf definiert sein.
#endif
#endif

using namespace std;

#ifndef SIL
    #ifndef WIN_SYS
        #error Not compiling on a Windows-System, cbw-lib can not be used!
    #endif

    #ifdef __cplusplus
    extern "C" {
    #endif

    #include "cbw.h"

    #ifdef __cplusplus
    }
    #endif
#endif  //SIL
#ifdef SIL  
#warning Software in the Loop is active, no interaction with hardware!
#endif
#ifdef SIMULATION
#warning Redirection to Simulation is active

#define HWDELAY 25 //[ms]

#endif

MiniLab1008* MiniLab1008::instance = NULL;

MiniLab1008::MiniLab1008() : process_image(0), process_image_old(0), process_image_change(0), output_image(0), height_analogue_value(0)
#ifdef SIMULATION
,adapter(nullptr)
#endif
{
    initProcessImageLayer();
    updateProcessImage();
}

MiniLab1008* MiniLab1008::getInstance() {
    if (instance == NULL) {
        instance = new MiniLab1008();
    }
    return instance;
}

MiniLab1008::~MiniLab1008() {
    resetOutputs();
#ifdef SIMULATION
   if(nullptr != adapter){
       delete adapter;
       adapter = nullptr;
   }
#endif
}

void MiniLab1008::initProcessImageLayer(void) {
    /* connect to board */
#ifndef SIL
    cbDConfigPort(0, FIRSTPORTA, DIGITALOUT);
    cbDConfigPort(0, FIRSTPORTB, DIGITALIN);
    cbDConfigPort(0, FIRSTPORTCH, DIGITALIN);
    cbDConfigPort(0, FIRSTPORTCL, DIGITALOUT);
#endif
#ifdef SIMULATION
#if !defined(SIMLONGRUN) && !defined(SIMTESTS)
    adapter = new SimAdapter();
#elif defined(SIMLONGRUN)
    adapter = new SimAdapterLongrun();
#else
    adapter = new SimAdapterTests();
#endif
    adapter->init();
#endif
}

void MiniLab1008::updateProcessImage(void) {
    static bool init = false;
    process_image_old = process_image; // save old values for change detection

    /* read input signals */
    process_image = 0;

#ifndef SIL
    unsigned short ioValue = 0;
    cbDIn(0, FIRSTPORTB, &ioValue);
    process_image = ioValue;
    cbDIn(0, FIRSTPORTCH, &ioValue); // High nibble already moved to low nibble
    process_image |= (ioValue & 0x0F) << 8;

    int error = 0;
    error = cbAIn(0, 0, BIP10VOLTS, &height_analogue_value);
#endif
#ifdef SIMULATION
    if(init) {
        sleep(HWDELAY);
    } else{
        init = true;
    }
    adapter->update_in();
    process_image = adapter->read();
#endif

    process_image_change = process_image_old ^ process_image;
}

void MiniLab1008::applyOutputToProcess(void) {
#ifdef SIL
    //    std::printf("new output: %0x\n", output_image);
#else
    unsigned short ioValue = 0;
    ioValue = (output_image & 0xFF);
    cbDOut(0, FIRSTPORTA, ioValue);
    ioValue = ((output_image >> 8) & 0x0F);
    cbDOut(0, FIRSTPORTCL, ioValue);
#endif
    
#ifdef SIMULATION
    sleep(HWDELAY);
    adapter->write(output_image);
    adapter->update_out();
#endif

}

unsigned char MiniLab1008::isBitSet(unsigned short bitMask) {
    return ((process_image & bitMask) != 0);
}

unsigned char MiniLab1008::isBitPosEdge(unsigned short bitMask) {
    return ((process_image & bitMask) == bitMask) && ((process_image_change & bitMask) == bitMask);
}

unsigned char MiniLab1008::isBitNegEdge(unsigned short bitMask) {
    return ((process_image & bitMask) == 0) && ((process_image_change & bitMask) == bitMask);
}

void MiniLab1008::setBitInOutput(unsigned short bitMask) {
    output_image |= bitMask;
}

void MiniLab1008::clearBitInOutput(unsigned short bitMask) {
    output_image &= ~bitMask;
}

unsigned short MiniLab1008::height() {
    return height_analogue_value;
}

void MiniLab1008::resetOutputs(void) {
    output_image = 0;
    applyOutputToProcess();
}

#ifdef SIL
void MiniLab1008::updateSim(void) {
    adapter->update_in();
}
#endif

void MiniLab1008::sleep(unsigned long ms) {
#ifndef SIL
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
#ifdef SIMULATION
    unsigned long starTime = adapter->getSim()->getSimTime();
    unsigned long now = 0;
    do {
        updateSim();
        now = adapter->getSim()->getSimTime();
    }while((now - starTime) <  ms);
#endif
}

unsigned int MiniLab1008::getMS() {
    unsigned long time = 0;
#ifndef SIL
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    time = llabs(millis);
#endif
#ifdef SIMULATION
    updateSim();
    time = adapter->getSim()->getSimTime();
#endif
    return time;
}

