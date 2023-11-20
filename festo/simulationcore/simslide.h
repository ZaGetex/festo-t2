/* 
 * File:   simslide.h
 * @author Lehmann
 * @date 3. April 2020
 */

#ifndef SIMSLIDE_H
#define SIMSLIDE_H

#include "simbase.h"
#include "simitem.h"

#include <vector>
#include <memory>

class SimSlide{
public:
    static constexpr double slideDepth = 180;
private:
    std::vector<std::shared_ptr<SimItem>> *items;
    double speedY;
    int displayCounter;
public:
    SimSlide(std::vector<std::shared_ptr<SimItem>> *items);
    void addItem(const std::shared_ptr<SimItem> &item);
    void evalTimeStep(unsigned int simTime); 
    void removeFirst();
    void removeAll();
};

#endif /* SIMSLIDE_H */

