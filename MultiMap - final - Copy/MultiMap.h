#pragma once
#include<vector>
#include<utility>
#define NULL_TKEY 0
using namespace std;

typedef int TKey;
typedef int TValue;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
typedef std::pair<TKey, TValue> TElem;

struct Node{
    TElem key;
    Node* next;
};

class MultiMapIterator;

class MultiMap
{
    friend class MultiMapIterator;
private:
    Node* start;
public:


    //t(1)
    MultiMap();

    //O(n)
    //BC = t(1)
    //WC = t(n)
    void add(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    //t(n) BC=WC=TC
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    //t(1) BC - the element is on the first position
    //t(n) WC - the element is on the last position or it is not found
    //O(n) TC
    bool remove(TKey c, TValue v);

    //returns the number of pairs from the multimap
    //TC O(n)
    //BC t(1)
    //WC t(n)
    int size() const;

    //checks whether the multimap is empty
    //t(1) BC=WC=TC
    bool isEmpty() const;

    //returns an iterator for the multimap
    //t(1) BC=WC=TC
    MultiMapIterator iterator() const;

    //destructor
    //t(n) BC=WC=TC
    ~MultiMap();

};