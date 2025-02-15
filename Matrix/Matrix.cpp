#include "Matrix.h"
#include <exception>
using namespace std;

//BC=WC=TC=theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
    this->lines = nrLines;
    this->columns = nrCols;
    this->BST.root = INVALID_INDEX;
    this->BST.size = 0;
    this->BST.indexFirstEmpty = 0;
    this->BST.capacity = INITIAL_SIZE;
    this->BST.elements = new Node[this->BST.capacity];
	   
}

//BC=WC=TC=theta(1)
int Matrix::nrLines() const {
    return this->lines;
}

//BC=WC=TC=theta(1)
int Matrix::nrColumns() const {
    return this->columns;
}

//BC=theta(1) WC=theta(n) TC=(n) n=size
TElem Matrix::element(int i, int j) const {
    if(i < 0 || i > this->nrLines() || j < 0 || j > this->nrColumns())
        throw std::exception();
    auto node = this->search(i, j);
    if(node != INVALID_INDEX)
        return this->BST.elements[node].info.value;

    return NULL_TELEM;
}

//BC=theta(1) WC=theta(h) TC=O(h) height
TElem Matrix::modify(int i, int j, TElem e) {
    if(i < 0 || i > this->nrLines() || j < 0 || j > this->nrColumns())
        throw std::exception();
    auto node = this->search(i,j);
    if(node != INVALID_INDEX){
        TElem savedValue = this->BST.elements[node].info.value;
        this->BST.elements[node].info.value = e;
        return savedValue;
    }else if(e != NULL_TELEM){
        this->addNode(i, j, e);
    }
    return NULL_TELEM;
}

//BC=WC=AC=theta(1)
int Matrix::comparisonFunction(const Matrix::matrixElement &firstElement,
                               const Matrix::matrixElement &secondElement) const {
    int aux;
    aux = firstElement.line - secondElement.line;
    if(aux < 0)
        return -1;
    else if(aux > 0)
        return 1;
    else{
        aux = firstElement.column - secondElement.column;
        if(aux < 0)
            return -1;
        else if(aux > 0)
            return 1;
        else return 0;
    }
}

//BC=theta(1) WC=theta(h) TC=O(h) height
int Matrix::search(int line, int column) const{
    if(line < 0 || column < 0 || line > this->lines || column > this->columns)
        return INVALID_INDEX;
    matrixElement searchedElement{};
    searchedElement.line = line;
    searchedElement.column = column;
    auto currentNode = this->BST.root;
    while(currentNode != INVALID_INDEX){
        if(this->comparisonFunction(this->BST.elements[currentNode].info, searchedElement) == 0)
            return currentNode;
        else if(this->comparisonFunction(this->BST.elements[currentNode].info, searchedElement) < 0)
            currentNode = this->BST.elements[currentNode].right;
        else
            currentNode = this->BST.elements[currentNode].left;
    }
    return INVALID_INDEX;
}

//BC=theta(1) WC=theta(h) TC=O(h) height
int Matrix::insertNodeRecursively(int headIndex, matrixElement value) {
    if(headIndex == INVALID_INDEX){
        int indexToBeInserted = this->BST.indexFirstEmpty;
        this->BST.elements[indexToBeInserted].right = INVALID_INDEX;
        this->BST.elements[indexToBeInserted].left = INVALID_INDEX;
        this->BST.elements[indexToBeInserted].info = value;
        this->BST.size++;
        this->BST.indexFirstEmpty++;
        return indexToBeInserted;
    }
    else if(this->comparisonFunction(this->BST.elements[headIndex].info, value) < 0)
        this->BST.elements[headIndex].right = this->insertNodeRecursively(this->BST.elements[headIndex].right, value);
    else
        this->BST.elements[headIndex].left = this->insertNodeRecursively(this->BST.elements[headIndex].left, value);
    return headIndex;
}

//BC=theta(1) WC=theta(h) TC=O(h) height
void Matrix::addNode(int i, int j, TElem e){
    if(this->BST.size == this->BST.capacity)
        this->resize();
    matrixElement elementToBeAdded{};
    elementToBeAdded.line = i;
    elementToBeAdded.column = j;
    elementToBeAdded.value = e;
    if(this->BST.root == INVALID_INDEX){
        this->BST.root = 0;
        this->BST.elements[0].left = INVALID_INDEX;
        this->BST.elements[0].right = INVALID_INDEX;
        this->BST.elements[0].info = elementToBeAdded;
        this->BST.size++;
        this->BST.indexFirstEmpty++;
        return ;
    }
    this->insertNodeRecursively(this->BST.root, elementToBeAdded);
}
//BC=theta(n) WC=theta(n) TC=theta(n) n=size
void Matrix::resize() {
    int newCapacity = this->BST.capacity * 2;
    Node* newElements = new Node[newCapacity];
    for(int i = 0; i< this->BST.size; i++)
        newElements[i] = this->BST.elements[i];
    delete[] this->BST.elements;
    this->BST.elements = newElements;
    this->BST.capacity = newCapacity;
}
//BC=theta(1) WC=theta(h) TC=O(h) height
int Matrix::minimumElementIndex(int currentNode) {
    int lastNode = currentNode;
    while(currentNode != INVALID_INDEX){
        lastNode = currentNode;
        currentNode = this->BST.elements[currentNode].left;
    }
    return lastNode;
}

//BC=theta(1) WC=theta(h) TC=O(h) height
void Matrix::removeNode(int i, int j) {
    int indexOfNode = this->search(i, j);
    if(indexOfNode != INVALID_INDEX){
        matrixElement elementToBeRemoved{};
        elementToBeRemoved.line = i;
        elementToBeRemoved.line = j;
        this->BST.root = this->removeRecursively(this->BST.root, elementToBeRemoved);
        this->BST.size--;
    }
}

//BC=WC=AC=theta(1)
Matrix::~Matrix(){
    delete[] this->BST.elements;
}

//BC=theta(1) WC=theta(h) TC=O(h) height
int Matrix::removeRecursively(int headIndex, Matrix::matrixElement toBeRemoved) {
    if(headIndex == INVALID_INDEX)
        return INVALID_INDEX;
    if(this->comparisonFunction(toBeRemoved, this->BST.elements[headIndex].info) == 0){
        if(this->BST.elements[headIndex].left == INVALID_INDEX && this->BST.elements[headIndex].right == INVALID_INDEX){
            this->BST.elements[headIndex].left == this->BST.indexFirstEmpty;
            this->BST.indexFirstEmpty = headIndex;
            return INVALID_INDEX;
        }
        else if(this->BST.elements[headIndex].left == INVALID_INDEX){
            int rightIndex = this->BST.elements[headIndex].right;
            this->BST.elements[headIndex].left = this->BST.indexFirstEmpty;
            this->BST.indexFirstEmpty = headIndex;
            return rightIndex;
        }
        else if(this->BST.elements[headIndex].right == INVALID_INDEX){
            int leftIndex = this->BST.elements[headIndex].left;
            this->BST.elements[headIndex].left = this->BST.indexFirstEmpty;
            this->BST.indexFirstEmpty = headIndex;
            return leftIndex;
        }
        int minimumIndex = this->minimumElementIndex(this->BST.elements[headIndex].right);
        this->BST.elements[headIndex].info = this->BST.elements[minimumIndex].info;
        this->BST.indexFirstEmpty = headIndex;
        return headIndex;
    }
    else if(this->comparisonFunction(toBeRemoved, this->BST.elements[headIndex].info) > 0)
        this->BST.elements[headIndex].left = this->removeRecursively(this->BST.elements[headIndex].left, toBeRemoved);
    else
        this->BST.elements[headIndex].right = this->removeRecursively(this->BST.elements[headIndex].right, toBeRemoved);
    return headIndex;
}


