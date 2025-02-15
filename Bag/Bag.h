#pragma once
#include <vector>
#include <utility>
typedef int TElem;
typedef std::pair<TElem,int> Element;
class BagIterator; 
class Bag {

private:
	int cp;
    int n;

    Element *e;

    void resize();

	friend class BagIterator;
public:
	Bag();

	void add(TElem e);


	bool remove(TElem e);

	bool search(TElem e) const;

	int nrOccurrences(TElem e) const;

	int size() const;

	BagIterator iterator() const;

	bool isEmpty() const;

	~Bag();
};