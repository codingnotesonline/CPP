#include <iostream>
using namespace std;

template <typename DataType> class Node {
public:
  DataType value;
  Node<DataType> *next;

  Node() { this->next = NULL; }

  Node(DataType value) {
    this->value = value;
    this->next = NULL;
  }

  ~Node() { this->next = NULL; }
};

template <typename DataType> class Queue {
private:
  Node<DataType> *Front;
  Node<DataType> *Back;
  int Size;

public:
  Queue() {
    this->Front = NULL;
    this->Back = NULL;
    this->Size = 0;
  }

  Queue(DataType value) {
    Node<DataType> *node = new Node<DataType>(value);
    this->Front = node;
    this->Back = node;
    this->Size = 1;
  }

  ~Queue() {
    delete this->Front;
    delete this->Back;
    this->Size = 0;
  }

  void push(DataType value) {
    Node<DataType> *node = new Node<DataType>(value);
    if (this->Front == NULL) {
      this->Front = node;
      this->Back = node;
      this->Size++;
      return;
    }

    this->Back->next = node;
    this->Back = node;
    this->Size++;
  }

  DataType pop() {
    if (this->Front == NULL) {
      return NULL;
    }

    DataType temp = this->Front->value;
    if (this->Front->next == NULL) {
      delete this->Front;

      this->Front = NULL;
      this->Back = NULL;
      this->Size--;

      return temp;
    }

    Node<DataType> *nodeToDelete = this->Front;
    this->Front = this->Front->next;
    this->Size--;

    delete nodeToDelete;

    return temp;
  }

  DataType front() { return this->Front->value; }

  DataType back() { return this->Back->value; }

  int size() { return this->Size; }

  bool empty() {
    if (this->Front == NULL) {
      return true;
    } else {
      return false;
    }
  }

  void print() {
    Node<DataType> *temp = this->Front;
    while (temp != NULL) {
      cout << temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }
};

// int main()
// {
//     Queue<int> *container = new Queue<int>();

//     cout<<"Is Empty: "<<container->empty()<<endl;
//     container->push(0);
//     container->push(1);
//     container->push(2);
//     container->push(3);
//     container->pop();
//     container->push(4);
//     container->push(5);
//     container->push(6);
//     container->pop();

//     cout<<"Front: "<<container->front()<<endl;

//     container->push(7);
//     container->push(8);
//     container->pop();
//     container->push(9);

//     cout<<"Back: "<<container->back()<<endl;

//     container->print();

//     cout<<"Size: "<<container->size()<<endl;
//     return 0;
// }