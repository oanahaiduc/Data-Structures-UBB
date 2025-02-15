#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

using namespace std;

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    current=col.start;
}

TElem MultiMapIterator::getCurrent() const{
    if(!valid()){
        throw exception();
    }
    return current->key;
}

bool MultiMapIterator::valid() const {
    if(current==nullptr)
        return false;
    return true;
}

void MultiMapIterator::next() {
    if(!valid()){
        throw exception();
    }
    current=current->next;
}

void MultiMapIterator::first() {
    current=col.start;
}
