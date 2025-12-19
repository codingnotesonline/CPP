#include <iostream>
#include "../Return-Nothing/ReturnNothing.cpp"
using namespace std;

template <typename DataType>
class BinomialHeapNode{
private:
    ReturnNothing<DataType> DefaultValues;
public:
    BinomialHeapNode *parent;
    // Point to the left most node
    BinomialHeapNode *child;
    int degree;
    DataType key;
    BinomialHeapNode *sibling;

    BinomialHeapNode(){
        this->parent = NULL;
        this->child = NULL;
        this->degree = 0;
        this->key = this->DefaultValues.DefaultValue();
        this->sibling = NULL;
    }

    BinomialHeapNode(DataType value){
        this->parent = NULL;
        this->child = NULL;
        this->degree = 0;
        this->key = value;
        this->sibling = NULL;
    }
};

class BinomialHeap{
    
};