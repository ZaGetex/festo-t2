/*
 * isimdrophandler.h
 *
 *  Created on: 01.05.2020
 *      Author: Lehmann
 */

#ifndef SRC_SIMULATIONCORE_ISIMDROPHANDLER_H_
#define SRC_SIMULATIONCORE_ISIMDROPHANDLER_H_

#include <memory>
#include "simitem.h"

class ISimDropHandler{
public:
	virtual ~ISimDropHandler(){};
	virtual void dropEnd(std::shared_ptr<SimItem> droppeditem)=0;
};

#endif /* SRC_SIMULATIONCORE_ISIMDROPHANDLER_H_ */
