#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
    friend class SortedSet;
private:
    const SortedSet& multime;
    SortedSetIterator(const SortedSet& m);
    TComp* sortedElements;
    int currentIndex;
    int size;
public:
    void first();
    void next();
    TComp getCurrent();
    bool valid() const;
    ~SortedSetIterator();
};

