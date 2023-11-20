
/* 
 * File:   simhciaction.h
 * @author Lehmann
 * @date 9. Mai 2020
 */

#ifndef SIMHCIACTION_H
#define SIMHCIACTION_H

#include "simjsonbase.h"

enum class SimHCIActionKind {
    pressStartOnly, pressStopOnly, pressResetOnly, pressEStopOnly, pressStart, pressStop, pressReset, pressEStop, releaseAll
};

class SimHCIAction : public SimJSONBase {
public:
    bool executed;
    unsigned int atTime;
    unsigned short setPattern;
    unsigned short clearPattern;

    SimHCIAction(unsigned int atTime);
    SimHCIAction(unsigned int atTime, SimHCIActionKind kind);

    void releaseAll();
    void pressStart();
    void pressStartOnly();
    void pressStop();
    void pressStopOnly();
    void pressReset();
    void pressResetOnly();
    void pressEStop();
    void pressEStopOnly();
    void releaseStart();
    void releaseStop();
    void releaseReset();
    void releaseEStop();
public:
    std::string toJSONString()override;
protected:
    bool evalPair(const char* key, const char* value) override;
    bool evalPair(const char* key, double value) override;
    void setToDefault() override;
};

#endif /* SIMHCIACTION_H */


