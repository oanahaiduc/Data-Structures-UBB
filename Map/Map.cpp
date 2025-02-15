#include "Map.h"
#include "MapIterator.h"

Map::Map() {
    capacity = 10;
    nodes = new Node[capacity];
    nextIndexes = new int[capacity];
    prevIndexes = new int[capacity];
    head = -1;
    tail = -1;
    firstEmpty = 0;
    for (int i = 0; i < capacity - 1; ++i) {
        nextIndexes[i] = i + 1;
        prevIndexes[i + 1] = i;
    }
    nextIndexes[capacity - 1] = -1; // Last node
    prevIndexes[0] = -1; // First node
}

Map::~Map() {
    delete[] nodes;
    delete[] nextIndexes;
    delete[] prevIndexes;
}
bool Map::relation(const TKey& key1, const TKey& key2) const{
    return key1 < key2;
}
void Map::resize() {
    int newCapacity = capacity * 2;
    Node* newNodes = new Node[newCapacity];
    int* newNextIndexes = new int[newCapacity];
    int* newPrevIndexes = new int[newCapacity];

    for (int i = 0; i < capacity; ++i) {
        newNodes[i] = nodes[i];
        newNextIndexes[i] = nextIndexes[i];
        newPrevIndexes[i] = prevIndexes[i];
    }
    for (int i = capacity; i < newCapacity - 1; ++i) {
        newNextIndexes[i] = i + 1;
        newPrevIndexes[i + 1] = i;
    }
    newNextIndexes[newCapacity - 1] = -1; // Last node
    newPrevIndexes[0] = -1; // First node

    delete[] nodes;
    delete[] nextIndexes;
    delete[] prevIndexes;

    nodes = newNodes;
    nextIndexes = newNextIndexes;
    prevIndexes = newPrevIndexes;
    firstEmpty = capacity;
    capacity = newCapacity;
}

int Map::allocateNode() {
    if (firstEmpty == -1) {
        resize(); // Resize the array if there's no empty space
    }
    int pos = firstEmpty; // Get the position of the first empty slot
    firstEmpty = nextIndexes[firstEmpty]; // Update firstEmpty to point to the next empty slot
    return pos; // Return the position of the allocated node
}

void Map::deallocateNode(int pos) {
    nextIndexes[pos] = firstEmpty;
    prevIndexes[pos] = -1;
    firstEmpty = pos;
}

TValue Map::add(TKey c, TValue v){
    int current = head;
    int prev = -1;

    // Traverse the list to find the correct position to insert/update the new element
    while (current != -1 && relation(nodes[current].element.first, c)) {
        prev = current;
        if (nodes[current].element.first == c) {
            // Key already exists, update the value and return the old value
            TValue oldValue = nodes[current].element.second;
            nodes[current].element.second = v;
            return oldValue;
        }
        current = nodes[current].next;
    }

    // Key doesn't exist, insert a new pair
    int newPos = allocateNode();
    nodes[newPos].element = TElem(c, v);
    nodes[newPos].next = current;

    if (prev == -1) {
        // Insert at the beginning of the list
        head = newPos;
    } else {
        // Insert in the middle or at the end of the list
        nodes[prev].next = newPos;
    }

    return NULL_TVALUE;
}

int Map::findPositionByKey(TKey key) const {
    int current = head;
    while (current != -1) {
        if (relation(nodes[current].element.first, key)) {
            return current;
        }
        current = nextIndexes[current];
    }
    return -1;
}

TValue Map::search(TKey c) const{
    int current = findPositionByKey(c);
    if (current != -1) {
        return nodes[current].element.second;
    }
    return NULL_TVALUE;
}

TValue Map::remove(TKey c){
    int pos = findPositionByKey(c);
    if (pos != -1) {
        TValue oldValue = nodes[pos].element.second;
        int prev = prevIndexes[pos];
        int next = nextIndexes[pos];

        deallocateNode(pos);

        if (prev != -1) {
            nextIndexes[prev] = next;
        } else {
            head = next;
        }

        if (next != -1) {
            prevIndexes[next] = prev;
        } else {
            tail = prev;
        }

        return oldValue;
    }
    return NULL_TVALUE;
}


int Map::size() const {
    int count = 0;
    int current = head;
    while (current != -1) {
        ++count;
        current = nextIndexes[current];
    }
    return count;
}

bool Map::isEmpty() const{
    return head == -1;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



