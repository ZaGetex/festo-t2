/*
 * File:   simlbiaction.h
 * @author Jaehnichen
 * @date 14. April 2021
 */

#ifndef SIMLBIACTION_H
#define SIMLBIACTION_H

#include "simjsonbase.h"


enum class SimLBIActionKind {
    interruptBegin, interruptHeightSensor, interruptFeedSeparator, interruptBufferFull, interruptEnd, closeBegin, closeHeightSensor, closeFeedSeparator, closeBufferFull, closeEnd, closeAll
};

enum class SimLBKind {
    lbBegin = (1<<0), lbHeightSensor = (1<<1), lbFeedSeparator = (1<<2), lbBufferFull = (1<<3), lbEnd = (1<<4), all = (0x1F)
};

class SimLBIAction : public SimJSONBase {
public:
    bool executed;
    unsigned int atTime;
    SimLBKind lb;
    bool manuallyInterrupted;
    unsigned short pattern;

    SimLBIAction(unsigned int atTime);
    SimLBIAction(unsigned int atTime, SimLBIActionKind kind);

    void closeAll();
    void interruptStart();
    void closeStart();
    void interruptHeightSensor();
    void closeHeightSensor();
    void interruptFeedSeparator();
    void closeFeedSeparator();
    void interruptBufferFull();
    void closeBufferFull();
    void interruptEnd();
    void closeEnd();

public:
    std::string toJSONString()override;
protected:
    bool evalPair(const char* key, const char* value) override;
    bool evalPair(const char* key, double value) override;
    void setToDefault() override;
};


#endif //SIMLIGHTBARRIERACTION_H
