#include "SMIterator.h"
#include "SortedMap.h"
#include <iostream>

SMIterator::SMIterator(const SortedMap& m) : map(m), current(m.head) {}

//t(1)
void SMIterator::first() {
    current = map.head;
}

//t(1)
void SMIterator::next() {
    if (valid())
        current = map.next[current];
    else
        throw std::exception();
}

//t(1)
bool SMIterator::valid() const {
    return current != -1;
}

//t(1)
TElem SMIterator::getCurrent() const {
    if (!valid())
        throw std::exception();
    return map.elems[current];
}
