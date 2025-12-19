#include <iostream>
#include <limits.h>
using namespace std;

template <typename DataType>
class QueueNode
{
public:
    DataType value;
    QueueNode *next;

    QueueNode()
    {
        this->next = NULL;
    }

    QueueNode(DataType value)
    {
        this->value = value;
        this->next = NULL;
    }

    QueueNode(DataType value, QueueNode *next)
    {
        this->value = value;
        this->next = next;
    }

    ~QueueNode()
    {
        this->next = NULL;
    }
};

template <typename DataType>
class QueueLinkedList
{
private:
    QueueNode<DataType> *Front;
    QueueNode<DataType> *Back;
    int Size;
    int MaxSize;
    bool restricted;

    int FindValue(DataType value)
    {
        QueueNode<DataType> *temp = this->Head;

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
    QueueLinkedList()
    {
        this->restricted = false;
        this->Front = NULL;
        this->Back = NULL;
        this->MaxSize = INT_MAX;
        this->Size = 0;
    }

    QueueLinkedList(int size)
    {
        this->restricted = true;
        this->Front = NULL;
        this->Back = NULL;
        this->MaxSize = size;
        this->Size = 0;
    }

    ~QueueLinkedList()
    {
        this->restricted = false;
        this->Front = NULL;
        this->Back = NULL;
        this->MaxSize = 0;
        this->Size = 0;
    }

    void enque(DataType element)
    {
        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        QueueNode<DataType> *node = new QueueNode<DataType>(element);
        if (this->Front == NULL)
        {
            this->Front = node;
            this->Back = node;
            this->Size++;
            return;
        }

        this->Back->next = node;
        this->Back = node;
        this->Size++;
    }

    void deque()
    {
        if (this->Front == NULL)
        {
            cout << "Queue Underflow" << endl;
            return;
        }

        if (this->Front->next == NULL)
        {
            delete this->Back;
            this->Front = NULL;
            this->Back = NULL;
            this->Size--;
            return;
        }

        QueueNode<DataType> *node = this->Front;
        this->Front = this->Front->next;

        delete node;
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
            QueueNode<DataType> *node = new QueueNode<DataType>(value);
            node->next = this->Front;
            this->Front = node;
            this->Size++;
            return;
        }

        if (index == (this->Size + 1))
        {
            this->enque(value);
            return;
        }

        QueueNode<DataType> *temp = this->Head;

        int i = 1;
        while (i < (index - 1))
        {
            temp = temp->next;
            i++;
        }

        QueueNode<DataType> *node = new QueueNode<DataType>(value);
        node->next = temp->next;
        temp->next = node;
        this->Size++;
    }

    void erase(int index)
    {
        if (this->Head == NULL)
        {
            cout << "Queue Underflow" << endl;
            return;
        }

        if (index > (this->Size) || index < 1)
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (index == 1)
        {
            this->deque();
            return;
        }

        QueueNode<DataType> *prev = NULL;
        QueueNode<DataType> *curr = this->Head;

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
            cout << "Queue Underflow" << endl;
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

    DataType front()
    {
        return this->Front->value;
    }

    DataType back()
    {
        return this->Back->value;
    }

    int size()
    {
        return this->Size;
    }

    bool empty()
    {
        if (this->Front == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    QueueNode<DataType> *returnHead()
    {
        return this->Front;
    }

    void clear()
    {
        if (this->Front == NULL)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        QueueNode<DataType> *prev, *curr;
        prev = NULL;
        curr = this->Front;

        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }

        this->Front = NULL;
        this->Back = NULL;
        this->Size = 0;
    }

    void print()
    {
        if (this->Front == NULL)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        QueueNode<DataType> *node = this->Front;

        cout << "Front -> ";
        while (node != NULL)
        {
            cout << node->value << " ";
            node = node->next;
        }

        cout << "<- Back";
        cout << endl;
    }
};