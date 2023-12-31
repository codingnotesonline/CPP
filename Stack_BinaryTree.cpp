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

template <typename DataType> class Stack {
private:
  Node<DataType> *Head;
  Node<DataType> *Top;
  int Size;

public:
  Stack() {
    this->Head = NULL;
    this->Top = NULL;
    this->Size = 0;
  }

  Stack(DataType value) {
    Node<DataType> *node = new Node<DataType>(value);
    this->Head = node;
    this->Top = node;
    this->Size = 1;
  }

  ~Stack() {
    delete Head;
    delete Top;
  }

  void push(DataType value) {
    Node<DataType> *node = new Node<DataType>(value);
    if (this->Head == NULL) {
      this->Head = node;
      this->Top = node;
      this->Size++;
      return;
    }

    this->Top->next = node;
    this->Top = node;
    this->Size++;
  }

  DataType pop() {
    if (this->Head == NULL) {
      return NULL;
    }

    if (this->Head->next == NULL) {
      DataType nodeToReturn = this->Top->value;
      delete this->Top;
      this->Head = NULL;
      this->Top = NULL;

      this->Size--;
      return nodeToReturn;
    }

    Node<DataType> *temp = this->Head;
    while (temp->next != this->Top) {
      temp = temp->next;
    }

    DataType nodeToReturn = this->Top->value;
    delete this->Top;
    temp->next = NULL;
    this->Top = temp;
    this->Size--;
    return nodeToReturn;
  }

  DataType top() { return this->Top->value; }

  int size() { return this->Size; }

  bool empty() {
    if (this->Head == NULL) {
      return true;
    } else {
      return false;
    }
  }

  void print() {
    Node<DataType> *temp = this->Head;
    while (temp != NULL) {
      cout << temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }
};

// int main() {
//   return 0;
// }