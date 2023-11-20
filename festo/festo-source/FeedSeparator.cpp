/** 
 * File:   FeedSeparator.cpp
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "FeedSeparator.h"
#include "FestoTransferSystem.h"

FeedSeparator::FeedSeparator(unsigned short bitmask) : bitmask(bitmask) {
}

void FeedSeparator::setState(bool state) {
    if (FestoTransferSystem::access != NULL) {
        if (state) {
            FestoTransferSystem::access->setBitInOutput(bitmask);
        } else {
            FestoTransferSystem::access->clearBitInOutput(bitmask);
        }
    }
}

void FeedSeparator::open() {
    setState(true);
}

void FeedSeparator::close() {
    setState(false);
}
