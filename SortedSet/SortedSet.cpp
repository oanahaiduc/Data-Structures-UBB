#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <exception>
#include <cmath>

//BC=WC=TC=theta(n)
SortedSet::SortedSet(Relation r) {
    this->r = r;
    this->m = 100;
    this->T = new TComp[this->m];
    this->next = new int[this->m];
    this->sizeSet = 0;
    this->firstEmpty = 0;

    for (int i = 0; i < this->m; i++) {
        this->T[i] = MAX;
        this->next[i] = -1;
    }
}


//BC=WC=TC=theta(1)
int SortedSet::hash(TComp e) const {
    return std::abs(e) % m;
}

//BC=WC=TC=theta(n)
void SortedSet::resize() {
    auto* old = new TComp [sizeSet];
    for(int i = 0; i< sizeSet; ++i){
        old[i] = MAX;
    }

    int current = 0;
    for(int i = 0; i < m; ++i){
        if(T[i] != MAX){
            old[current++] = T[i];
        }
    }

    this->m *= 2;
    auto* nou = new TComp[m];
    int* newNext = new int[m];
    for(int i = 0; i < m; ++i){
        nou[i] = MAX;
        newNext[i] = -1;
    }

    delete[] T;
    delete[] next;
    T = nou;
    next = newNext;

    firstEmpty = 0;
    int oldSizeSet = sizeSet;
    sizeSet = 0;
    for(int i = 0; i < oldSizeSet; ++i){
        add(old[i]);
    }

    delete[] old;
}

//BC=theta(1) WC=theta(n) TC=O(n) n=size of the set
bool SortedSet::add(TComp e) {
    if((sizeSet / m) * 100 > 70)
        resize();

    int i = hash(e);
    if(T[i] == MAX){
        T[i] = e;
        if(i == firstEmpty){
            firstEmpty++;
            while((firstEmpty < m) && T[firstEmpty] != MAX)
                firstEmpty++;
        }
        sizeSet++;
        return true;
    }
    int j =-1;
    while(i != -1){
        if(T[i] == e)
            return false;
        j = i;
        i = next[i];
    }
    T[firstEmpty] = e;
    next[j] = firstEmpty;
    firstEmpty++;
    while((firstEmpty < m) && T[firstEmpty] != MAX)
        firstEmpty++;
    sizeSet++;
    return true;
}

//BC=theta(1) WC=theta(n) TC=O(n) n=size of the set
bool SortedSet::remove(TComp e) {
    int i = this->hash(e);
    int j = -1;

    while (i != -1 && T[i] != e) {
        j = i;
        i = next[i];
    }

    if (i == -1) {
        return false;
    }else{
        bool check = false;
        do{
            int current = next[i];
            int prev = i;

            while(current != -1 && hash(T[current]) != i){
                prev = current;
                current = next[i];
            }
            if(current == -1){
                check = true;
            }else{
                T[i] = T[current];
                i = current;
                j = prev;
            }
        }while(!check);
        if(j != -1){
            next[j] = next[i];
        }
        T[i] = MAX;
        next[i] = -1;
        if(i < firstEmpty){
            firstEmpty = i;
        }

    }
    sizeSet--;
    return true;
}


//BC=theta(1) WC=theta(n) TC=O(n) n=size of the set
bool SortedSet::search(TElem elem) const {
    int i = hash(elem);
    if(T[i] == elem){
        return true;
    }
    while(i != -1){
        if(T[i] == elem)
            return true;
        i = next[i];
    }
    return false;
}


//BC=WC=TC=theta(1)
int SortedSet::size() const {
    return this->sizeSet;
}

//BC=WC=TC=theta(1)
bool SortedSet::isEmpty() const {
    return this->sizeSet == 0;
}

//BC=WC=TC=theta(1)
SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}


//BC=WC=TC=theta(1)
SortedSet::~SortedSet() {
    delete[] this->T;
    delete[] this->next;
}
