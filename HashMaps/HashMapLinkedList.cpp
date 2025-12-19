#include <iostream>
#include <limits.h>
using namespace std;

template <typename DataType>
class Singly
{
public:
    DataType value;
    Singly *next;

    Singly()
    {
        this->next = NULL;
    }

    Singly(DataType value)
    {
        this->value = value;
        this->next = NULL;
    }

    ~Singly()
    {
        this->next = NULL;
    }
};

template <typename DataType>
class SinglyLinkedList
{
private:
    Singly<DataType> *Head;
    Singly<DataType> *End;
    int TotalSize;
    int Size;

    int FindValue(DataType value)
    {
        Singly<DataType> *temp = this->Head;

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
    SinglyLinkedList()
    {
        this->Head = NULL;
        this->End = NULL;
        this->TotalSize = INT_MAX;
        this->Size = 0;
    }

    SinglyLinkedList(int TotalSize)
    {
        this->Head = NULL;
        this->End = NULL;
        this->TotalSize = TotalSize;
        this->Size = 0;
    }

    ~SinglyLinkedList()
    {
        this->clear();
        this->Head = NULL;
        this->End = NULL;
        this->TotalSize = 0;
        this->Size = 0;
    }

    void pushBack(DataType value)
    {
        if (this->Size == this->TotalSize)
        {
            cout << "Linked List Overflow Occured" << endl;
            return;
        }

        Singly<DataType> *node = new Singly<DataType>(value);

        if (this->Head == NULL)
        {
            this->Head = node;
            this->End = node;
            this->Size++;
            return;
        }

        this->End->next = node;
        this->End = node;
        this->Size++;
    }

    void pushFront(DataType value)
    {
        if (this->Size == this->TotalSize)
        {
            cout << "Linked List Overflow Occured" << endl;
            return;
        }

        Singly<DataType> *node = new Singly<DataType>(value);

        if (this->Head == NULL)
        {
            this->Head = node;
            this->End = node;
            this->Size++;
            return;
        }

        node->next = this->Head;
        this->Head = node;
        this->Size++;
    }

    void popBack()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return;
        }

        if (this->Head->next == NULL)
        {
            delete this->Head;
            this->Head = NULL;
            this->End = NULL;
            this->Size = 0;
            return;
        }

        Singly<DataType> *temp = this->Head;
        while (temp->next != this->End)
        {
            temp = temp->next;
        }

        temp->next = NULL;
        delete this->End;
        this->End = temp;
        this->Size--;
    }

    void popFront()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return;
        }

        if (this->Head->next == NULL)
        {
            delete this->Head;
            this->Head = NULL;
            this->End = NULL;
            this->Size = 0;
            return;
        }

        Singly<DataType> *temp = this->Head;
        this->Head = this->Head->next;
        delete temp;
        this->Size--;
    }

    void insert(DataType value, int index)
    {
        if (this->Size == this->TotalSize)
        {
            cout << "Linked List Overflow Occured" << endl;
            return;
        }

        if (index > (this->Size + 1) || index <= 0)
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (index == 1)
        {
            this->pushFront(value);
            return;
        }

        Singly<DataType> *temp = this->Head;

        int i = 1;
        while (i < (index - 1))
        {
            temp = temp->next;
            i++;
        }

        Singly<DataType> *node = new Singly<DataType>(value);
        node->next = temp->next;
        temp->next = node;
        this->Size++;
    }

    void erase(int index)
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return;
        }

        if (index > this->Size || index <= 0)
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (index == 1)
        {
            this->popFront();
            return;
        }

        Singly<DataType> *prev = NULL;
        Singly<DataType> *curr = this->Head;

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
            cout << "Linked List is Empty" << endl;
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

    int size()
    {
        return this->Size;
    }

    DataType head()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return NULL;
        }

        return this->Head->value;
    }

    DataType end()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return NULL;
        }

        return this->End->value;
    }

    Singly<DataType> *returnHead()
    {
        return this->Head;
    }

    bool empty()
    {
        if (this->Head == NULL)
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
        if (this->Head == NULL)
        {
            return;
        }

        Singly<DataType> *prev = NULL;
        Singly<DataType> *curr = this->Head;

        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }

        this->Head = NULL;
        this->End = NULL;
    }

    void swap(int firstIndex, int secondIndex)
    {
        if ((firstIndex > this->Size) || (secondIndex > this->Size))
        {
            cout << "Index is Out of Range" << endl;
            return;
        }

        if (firstIndex == secondIndex)
        {
            cout << "Swapping Cannot Occured Between Same Values" << endl;
        }

        Singly<DataType> *firstIndexNode = this->Head;
        Singly<DataType> *secondIndexNode = this->Head;

        int i = 1, j = 1;
        while (i < firstIndex)
        {
            firstIndexNode = firstIndexNode->next;
            i++;
        }

        while (j < secondIndex)
        {
            secondIndexNode = secondIndexNode->next;
            j++;
        }

        DataType temp = firstIndexNode->value;
        firstIndexNode->value = secondIndexNode->value;
        secondIndexNode->value = temp;
    }

    void print()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return;
        }

        Singly<DataType> *temp = this->Head;
        while (temp != NULL)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void reverse()
    {
        if (this->Head == NULL)
        {
            cout << "Linked List is Empty" << endl;
            return;
        }

        Singly<DataType> *prev = NULL;
        Singly<DataType> *curr = this->Head;
        Singly<DataType> *next = NULL;

        this->End = curr;

        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        this->Head = prev;
    }
};