#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
    this->cp = 1;
    e = new Element[cp];
    this->n = 0;
}

void Bag::resize() {

    Element *eNou = new Element[2 * cp];

    for (int i = 0; i < n; i++)
        eNou[i] = e[i];

    cp = 2 * cp;

    delete[] e;

    e = eNou;
}

void Bag::add(TElem elem) {
    if(n == cp)
        resize();
    for(int i = 0; i < this->n ; ++i)
        if(e[i].first == elem)
        {
            e[i].second++;
            return;
        }
    this->e[n].first = elem;
    this->e[n].second = 1;
    //e[n] = {elem, 1};
    n++;
}


bool Bag::remove(TElem elem) {
	bool found = false;
    int i = 0;
    while(i < this->n && !found){
        if(this->e[i].first == elem){
            found = true;
            for(int j = i; j < n-1; j++){
                this->e[j] = this->e[j+1];
            }
            this->n--;
        } else {
            i++;
        }
    }
    return found;
}


bool Bag::search(TElem elem) const {
    for(int i = 0; i < n; i++){
        if(this->e[i].first == elem)
            return true;
    }
}

int Bag::nrOccurrences(TElem elem) const {
    for(int i = 0; i < n; i++){
        if(this->e[i].first == elem){
            return this->e[i].second;
        }
    }
}


int Bag::size() const {
    return this->n;
}


bool Bag::isEmpty() const {
	return (n==0);
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    delete[] e;
}

