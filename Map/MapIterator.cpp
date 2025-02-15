#include "Map.h"
#include "MapIterator.h"
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	first();
}


void MapIterator::first() {
    current = map.head;
    moveNextValid();
}


void MapIterator::next() {
    if (valid()) {
        current = map.nextIndexes[current];
        moveNextValid(); // Move to the next valid element
    }
}


TElem MapIterator::getCurrent(){
    if (valid()) {
        return map.nodes[current].element;
    }
    return NULL_TELEM; // Return NULL_TELEM if iterator is not valid
}


bool MapIterator::valid() const {
    return current != -1;
}

void MapIterator::moveNextValid() {
    while (valid() && !map.relation(map.nodes[current].element.first, map.nodes[map.head].element.first)) {
        current = map.nextIndexes[current];
    }
}