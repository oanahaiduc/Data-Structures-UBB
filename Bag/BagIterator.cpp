#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    this->current = 0;
}

void BagIterator::first() {
    this->current = 0;
}


void BagIterator::next() {
    if(!valid()){
        throw exception();
    } else{
        this->current++;
    }
}


bool BagIterator::valid() const {
	return (this->current < this->bag.n);
}


TElem BagIterator::getCurrent() const
{
    if(!valid()){
        throw exception();
    } else{
        return this->bag.e[this->current].first;
    }
}
