#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
    friend class MultiMap;

private:

    MultiMapIterator(const MultiMap& c);

    const MultiMap& col;

    Node* current;

public:

    //t(1) BC=WC=TC
    void first();

    //t(1) BC=WC=TC
    void next();

    //t(1) BC=WC=TC
    bool valid() const;

    //t(1) BC=WC=TC
    TElem getCurrent() const;
};