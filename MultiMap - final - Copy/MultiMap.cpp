#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() : start(nullptr){
}


void MultiMap::add(TKey c, TValue v) {
    Node* elem_nou = new Node;
    elem_nou->key = make_pair(c, v);
    elem_nou->next = nullptr;

    if (start == nullptr) {
        start = elem_nou;
        return;
    }

    Node* current = start;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = elem_nou;
}


bool MultiMap::remove(TKey c, TValue v) {
    if (start == nullptr) {
        return false;
    }

    if (start->key == make_pair(c, v)) {
        Node* n = start;
        start = start->next;
        delete n;
        return true;
    }

    Node* prev = start;
    Node* current = start->next;

    while (current != nullptr && current->key != make_pair(c, v)) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    prev->next = current->next;
    delete current;
    return true;
}


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> ans;
    auto head=start;
    while(head!=nullptr){
        if(head->key.first==c){
            ans.push_back(head->key.second);
        }
        head=head->next;
    }
    return ans;
}


int MultiMap::size() const {
    int size=0;
    Node* head=start;
    while(head!=nullptr){
        head=head->next;
        ++size;
    }
    return size;
}


bool MultiMap::isEmpty() const {
    if(start==nullptr)
        return true;
    return false;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
    Node* currentNode = start;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    start = nullptr;
}

