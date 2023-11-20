/**
 * File:   FeedSeparator.h
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 *
 */

#ifndef FEEDSEPARATOR_H
#define FEEDSEPARATOR_H

class FeedSeparator{
private:
    unsigned int bitmask;
    void setState(bool state);
public:
    explicit FeedSeparator(unsigned short bitmask);
    void open();
    void close();
};


#endif /* FEEDSEPARATOR_H */

