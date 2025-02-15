#include "SortedSetIterator.h"
#include "SortedSet.h"
#include <exception>
#include <algorithm>

using namespace std;


//BC=WC=TC=theta(n * log(n))
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m), currentIndex(0) {
   size = multime.size();
   sortedElements = new TComp[size];
   int current = 0;
   for(int i = 0; i< multime.m; ++i){
       if(multime.T[i] != MAX){
           sortedElements[current++] = multime.T[i];
       }
   }
   std::sort(sortedElements, sortedElements + size, multime.r);
}


//BC=WC=TC=theta(1)
void SortedSetIterator::first() {
    currentIndex = 0;
}


//BC=WC=TC=theta(1)
void SortedSetIterator::next() {
    if (valid()) {
        currentIndex++;
    }else
        throw std::exception();
}


//BC=WC=TC=theta(1)
TComp SortedSetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return sortedElements[currentIndex];
}


//BC=WC=TC=theta(1)
bool SortedSetIterator::valid() const {
    return currentIndex < size;
}


//BC=WC=TC=theta(1)
SortedSetIterator::~SortedSetIterator() {
    delete[] sortedElements;
}
