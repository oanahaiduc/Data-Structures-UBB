#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

//theta(n)
SortedMap::SortedMap(Relation r) {
    this->capacity = 5;
    this->length = 0;
    this->r = r;
    this->elems = new TElem[capacity];
    this->next = new int[capacity];
    this->prev = new int[capacity];
    this->head = -1;
    this->tail = -1;
    for (int i = 0; i < capacity - 1; i++) {
        next[i] = i + 1;
        prev[i + 1] = i;
    }
    this->next[capacity - 1] = -1;
    this->prev[0] = -1;
    this->firstEmpty = 1;
}

//BC=WC=AC=t(n)
void SortedMap::resize() {
    int newCapacity = capacity * 2;
    TElem* newElems = new TElem[newCapacity];
    int* newNext = new int[newCapacity];
    int* newPrev = new int[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newElems[i] = elems[i];
        newNext[i] = next[i];
        newPrev[i] = prev[i];
    }

    for (int i = capacity; i < newCapacity - 1; i++) {
        newNext[i] = i + 1;
        newPrev[i + 1] = i;
    }
    newNext[newCapacity - 1] = -1;
    newPrev[capacity] = -1;

    delete[] elems;
    delete[] next;
    delete[] prev;

    elems = newElems;
    next = newNext;
    prev = newPrev;

    int oldCapacity = capacity;
    capacity = newCapacity;
    firstEmpty = oldCapacity;
}

//BC t(1)
//WC t(n)
//AC O(n)
TValue SortedMap::add(TKey k, TValue v) {
    if (next[firstEmpty] == -1)
        resize();

    int current = head;
    int previous = -1;

    while (current != -1 && r(elems[current].first, k)) {
        previous = current;
        current = next[current];
    }

    if (elems[previous].first == k) {
        TValue oldValue = elems[previous].second;
        elems[previous].second = v;
        return oldValue;
    }

    int newIndex = firstEmpty;
    firstEmpty = next[firstEmpty];
    elems[newIndex] = make_pair(k, v);
    next[newIndex] = current;
    prev[newIndex] = previous;

    if (current != -1)
        prev[current] = newIndex;
    else
        tail = newIndex;

    if (previous != -1)
        next[previous] = newIndex;
    else
        head = newIndex;

    length++;

    return NULL_TVALUE;
}

//BC t(1)
//WC t(n)
//AC O(n)
TValue SortedMap::search(TKey k) const {
    int current = head;
    while (current != -1 && elems[current].first != k)
        current = next[current];

    if (current != -1)
        return elems[current].second;

    return NULL_TVALUE;
}

//BC t(1)
//WC t(n)
//AC O(n)
TValue SortedMap::remove(TKey k) {
    int current = head;
    while (current != -1 && elems[current].first != k)
        current = next[current];

    if (current == -1)
        return NULL_TVALUE;

    if (current == head)
        head = next[current];
    else
        next[prev[current]] = next[current];

    if (current == tail)
        tail = prev[current];
    else
        prev[next[current]] = prev[current];

    next[current] = firstEmpty;
    prev[current] = -1;
    firstEmpty = current;

    length--;

    return elems[current].second;
}

// BC=WC=AC=t(1)
int SortedMap::size() const {
    return length;
}

// BC=WC=AC=t(1)
bool SortedMap::isEmpty() const {
    return length == 0;
}


// BC=WC=AC=t(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// BC=WC=AC=t(1)
SortedMap::~SortedMap() {
    delete[] elems;
    delete[] next;
    delete[] prev;
}
