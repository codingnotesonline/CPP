#include <iostream>
#include <limits.h>
using namespace std;

template <typename DataType>
class StackNode
{
public:
    DataType value;
    StackNode *next;

    StackNode()
    {
        this->next = NULL;
    }

    StackNode(DataType value)
    {
        this->value = value;
        this->next = NULL;
    }

    StackNode(DataType value, StackNode *next)
    {
        this->value = value;
        this->next = next;
    }

    ~StackNode()
    {
        this->next = NULL;
    }
};

template <typename DataType>
class StackLinkedList
{
private:
    StackNode<DataType> *Head;
    StackNode<DataType> *Top;
    int Size;
    int MaxSize;
    bool restricted;

    void printStack(StackNode<DataType> *node)
    {
        if (node == NULL)
        {
            return;
        }

        this->printStack(node->next);
        cout << node->value << " ";
    }

    int FindValue(DataType value)
    {
        StackNode<DataType> *temp = this->Head;

        int i = 1;
        while (temp != NULL)
        {
            if (temp->value == value)
            {
                return i;
            }
            temp = temp->next;
            i++;
        }

        return -1;
    }

public:
    StackLinkedList()
    {
        this->restricted = false;
        this->Head = NULL;
        this->Top = NULL;
        this->MaxSize = INT_MAX;
        this->Size = 0;
    }

    StackLinkedList(int size)
    {
        this->restricted = true;
        this->Head = NULL;
        this->Top = NULL;
        this->MaxSize = size;
        this->Size = 0;
    }

    ~StackLinkedList()
    {
        this->restricted = false;
        this->Head = NULL;
        this->Top = NULL;
        this->MaxSize = 0;
        this->Size = 0;
    }

    void push(DataType element)
    {
        if (restricted && this->Size == this->MaxSize)
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        StackNode<DataType> *node = new StackNode<DataType>(element);
        if (this->Top == NULL)
        {
            this->Top = node;
            this->Head = node;
            this->Size++;
            return;
        }

        this->Top->next = node;
        this->Top = node;
        this->Size++;
    }

    void pop()
    {
        if (this->Top == NULL)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        if (this->Head->next == NULL)
        {
            delete this->Head;
            this->Head = NULL;
            this->Top = NULL;
            this->Size--;
            return;
        }

        StackNode<DataType> *curr = this->Head;
        while (curr->next != this->Top)
        {
            curr = curr->next;
        }

        curr->next = NULL;
        delete this->Top;
        this->Top = curr;
        this->Size--;
    }

    void insert(DataType value, int index)
    {
        if (index > (this->Size + 1) || index < 1)
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (this->restricted && this->Size == this->MaxSize)
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        if (index == 1)
        {
            StackNode<DataType> *node = new StackNode<DataType>(value);
            node->next = this->Head;
            this->Head = node;
            this->Size++;
            return;
        }

        if (index == (this->Size + 1))
        {
            this->push(value);
            return;
        }

        StackNode<DataType> *temp = this->Head;

        int i = 1;
        while (i < (index - 1))
        {
            temp = temp->next;
            i++;
        }

        StackNode<DataType> *node = new StackNode<DataType>(value);
        node->next = temp->next;
        temp->next = node;
        this->Size++;
    }

    void erase(int index)
    {
        if (this->Head == NULL)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        if (index > (this->Size) || index < 1)
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (index == 1)
        {
            StackNode<DataType> *node = this->Head;
            this->Head = this->Head->next;
            delete node;
            this->Size--;
            return;
        }

        if (index == this->Size)
        {
            this->pop();
            return;
        }

        StackNode<DataType> *prev = NULL;
        StackNode<DataType> *curr = this->Head;

        int i = 1;
        while (i < index)
        {
            prev = curr;
            curr = curr->next;
            i++;
        }

        prev->next = curr->next;
        delete curr;
        this->Size--;
    }

    void remove(DataType value)
    {
        if (this->Head == NULL)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        int index = this->FindValue(value);

        if (index == -1)
        {
            cout << "Value does not Exist" << endl;
        }
        else
        {
            this->erase(index);
        }
    }

    DataType top()
    {
        return this->Top->value;
    }

    int size()
    {
        return this->Size;
    }

    bool empty()
    {
        if (this->Top == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void clear()
    {
        if (this->Top == NULL)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        StackNode<DataType> *prev, *curr;
        prev = NULL;
        curr = this->Head;

        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }

        this->Head = NULL;
        this->Top = NULL;
        this->Size = 0;
    }

    StackNode<DataType> *returnHead()
    {
        return this->Head;
    }

    void print()
    {
        if (this->Top == NULL)
        {
            cout << "Stack is empty" << endl;
            return;
        }
        StackNode<DataType> *temp = this->Head;

        cout << "Top -> ";

        this->printStack(temp);
        cout << endl;
    }
};