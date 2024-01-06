#include <iostream>
#include <limits.h>
using namespace std;

namespace Node
{
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
    class Doubly
    {
    public:
        DataType value;
        Doubly *previous;
        Doubly *next;

        Doubly()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Doubly(DataType value)
        {
            this->value = value;
            this->previous = NULL;
            this->next = NULL;
        }

        ~Doubly()
        {
            this->previous = NULL;
            this->next = NULL;
        }
    };

    template <typename DataType>
    class SinglyCircular
    {
    public:
        DataType value;
        SinglyCircular *next;

        SinglyCircular()
        {
            this->next = NULL;
        }

        SinglyCircular(DataType value)
        {
            this->value = value;
            this->next = NULL;
        }

        ~SinglyCircular()
        {
            this->next = NULL;
        }
    };

    template <typename DataType>
    class DoublyCircular
    {
    public:
        DataType value;
        DoublyCircular *previous;
        DoublyCircular *next;

        DoublyCircular()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        DoublyCircular(DataType value)
        {
            this->value = value;
            this->previous = NULL;
            this->next = NULL;
        }

        ~DoublyCircular()
        {
            this->previous = NULL;
            this->next = NULL;
        }
    };
}

using namespace Node;
namespace LinkedList
{
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

        DataType popBack()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->End->value;

            if (this->Head->next == NULL)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
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
            return value;
        }

        DataType popFront()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->Head->value;

            if (this->Head->next == NULL)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
            }

            Singly<DataType> *temp = this->Head;
            this->Head = this->Head->next;
            delete temp;
            this->Size--;
            return value;
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

        DataType erase(int index)
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

            DataType value = curr->value;
            prev->next = curr->next;
            delete curr;
            this->Size--;
            return value;
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
                return;
            }

            return this->Head->value;
        }

        DataType end()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            return this->End->value;
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
                cout << "Linked List is Empty" << endl;
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

    template <typename DataType>
    class DoublyLinkedList
    {
    private:
        Doubly<DataType> *Head;
        Doubly<DataType> *End;
        int TotalSize;
        int Size;

        int FindValue(DataType value)
        {
            Doubly<DataType> *temp = this->Head;

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
        DoublyLinkedList()
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = INT_MAX;
            this->Size = 0;
        }

        DoublyLinkedList(int TotalSize)
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = TotalSize;
            this->Size = 0;
        }

        ~DoublyLinkedList()
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

            Doubly<DataType> *node = new Doubly<DataType>(value);

            if (this->Head == NULL)
            {
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            this->End->next = node;
            node->previous = this->End;
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

            Doubly<DataType> *node = new Doubly<DataType>(value);

            if (this->Head == NULL)
            {
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            node->next = this->Head;
            this->Head->previous = node;
            this->Head = node;
            this->Size++;
        }

        DataType popBack()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->End->value;

            if (this->Head->next == NULL)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
            }

            Doubly<DataType> *temp = this->End->previous;

            temp->next = NULL;
            delete this->End;
            this->End = temp;
            this->Size--;
            return value;
        }

        DataType popFront()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->Head->value;

            if (this->Head->next == NULL)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
            }

            Doubly<DataType> *temp = this->Head;
            this->Head = this->Head->next;
            this->Head->previous = NULL;
            delete temp;
            this->Size--;
            return value;
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

            if (index == (this->Size + 1))
            {
                this->pushBack(value);
                return;
            }

            Doubly<DataType> *temp = this->Head;

            int i = 1;
            while (i < (index - 1))
            {
                temp = temp->next;
                i++;
            }

            Doubly<DataType> *node = new Doubly<DataType>(value);
            node->next = temp->next;
            temp->next->previous = node;
            temp->next = node;
            node->previous = temp;
            this->Size++;
        }

        DataType erase(int index)
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

            if (index == this->Size)
            {
                this->popBack();
                return;
            }

            Doubly<DataType> *prev = NULL;
            Doubly<DataType> *curr = this->Head;

            int i = 1;
            while (i < index)
            {
                prev = curr;
                curr = curr->next;
                i++;
            }

            DataType value = curr->value;
            prev->next = curr->next;
            curr->next->previous = prev;
            delete curr;
            this->Size--;
            return value;
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
                return;
            }

            return this->Head->value;
        }

        DataType end()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            return this->End->value;
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
                cout << "Linked List is Empty" << endl;
                return;
            }

            Doubly<DataType> *prev = NULL;
            Doubly<DataType> *curr = this->Head;

            while (curr != NULL)
            {
                prev = curr;
                curr = curr->next;
                delete prev;
            }
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

            Doubly<DataType> *firstIndexNode = this->Head;
            Doubly<DataType> *secondIndexNode = this->Head;

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

            Doubly<DataType> *temp = this->Head;
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

            Doubly<DataType> *prev = NULL;
            Doubly<DataType> *curr = this->Head;
            Doubly<DataType> *next = NULL;

            this->End = curr;

            while (curr != NULL)
            {
                next = curr->next;
                curr->next = prev;
                curr->previous = next;
                prev = curr;
                curr = next;
            }

            this->Head = prev;
        }
    };

    template <typename DataType>
    class SinglyCircularLinkedList
    {
    private:
        SinglyCircular<DataType> *Head;
        SinglyCircular<DataType> *End;
        int TotalSize;
        int Size;

        int FindValue(DataType value)
        {
            SinglyCircular<DataType> *temp = this->Head;

            int i = 1;
            do
            {
                if (temp->value == value)
                {
                    return i;
                }
                temp = temp->next;
                i++;
            } while (temp != this->Head);

            return -1;
        }

    public:
        SinglyCircularLinkedList()
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = INT_MAX;
            this->Size = 0;
        }

        SinglyCircularLinkedList(int TotalSize)
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = TotalSize;
            this->Size = 0;
        }

        ~SinglyCircularLinkedList()
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

            SinglyCircular<DataType> *node = new SinglyCircular<DataType>(value);

            if (this->Head == NULL)
            {
                node->next = node;
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            node->next = this->Head;
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

            SinglyCircular<DataType> *node = new SinglyCircular<DataType>(value);

            if (this->Head == NULL)
            {
                node->next = node;
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            this->End->next = node;
            node->next = this->Head;
            this->Head = node;
            this->Size++;
        }

        DataType popBack()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->End->value;

            if (this->Head->next == this->Head)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size--;
                return;
            }

            SinglyCircular<DataType> *temp = this->Head;
            while (temp->next != this->End)
            {
                temp = temp->next;
            }

            temp->next = this->End->next;
            delete this->End;
            this->End = temp;
            this->Size--;
            return value;
        }

        DataType popFront()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->End->value;

            if (this->Head->next == this->Head)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size--;
                return;
            }

            SinglyCircular<DataType> *temp = this->Head;
            this->End->next = this->Head->next;
            this->Head = this->Head->next;
            delete temp;
            this->Size--;
            return value;
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

            if (index == (this->Size + 1))
            {
                this->pushBack(value);
                return;
            }

            SinglyCircular<DataType> *temp = this->Head;

            int i = 1;
            while (i < (index - 1))
            {
                temp = temp->next;
                i++;
            }

            SinglyCircular<DataType> *node = new SinglyCircular<DataType>(value);
            node->next = temp->next;
            temp->next = node;
            this->Size++;
        }

        DataType erase(int index)
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            if (index > (this->Size + 1) || index <= 0)
            {
                cout << "Index is Out of Range" << endl;
                return;
            }

            if (index == 1)
            {
                this->popFront();
                return;
            }

            if (index == this->Size)
            {
                this->popBack();
                return;
            }

            SinglyCircular<DataType> *prev = NULL;
            SinglyCircular<DataType> *curr = this->Head;

            int i = 1;
            while (i < index)
            {
                prev = curr;
                curr = curr->next;
                i++;
            }

            DataType value = curr->value;
            prev->next = curr->next;
            delete curr;
            this->Size--;
            return value;
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
                return;
            }

            return this->Head->value;
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
                cout << "Linked List is Empty" << endl;
                return;
            }

            SinglyCircular<DataType> *prev = NULL;
            SinglyCircular<DataType> *curr = this->Head;

            do
            {
                prev = curr;
                curr = curr->next;
                delete prev;
            } while (curr != this->Head);
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

            SinglyCircular<DataType> *firstIndexNode = this->Head;
            SinglyCircular<DataType> *secondIndexNode = this->Head;

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

            SinglyCircular<DataType> *temp = this->Head;
            do
            {
                cout << temp->value << " ";
                temp = temp->next;
            } while (temp != this->Head);
            cout << endl;
        }
    };

    template <typename DataType>
    class DoublyCircularLinkedList
    {
        DoublyCircular<DataType> *Head;
        DoublyCircular<DataType> *End;
        int TotalSize;
        int Size;

        DoublyCircularLinkedList()
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = INT_MAX;
            this->Size = 0;
        }

        DoublyCircularLinkedList(int TotalSize)
        {
            this->Head = NULL;
            this->End = NULL;
            this->TotalSize = TotalSize;
            this->Size = 0;
        }

        ~DoublyCircularLinkedList()
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

            DoublyCircular<DataType> *node = new DoublyCircular<DataType>(value);

            if (this->Head == NULL)
            {
                node->next = node;
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            node->next = this->Head;
            this->Head->previous = node;
            this->End->next = node;
            node->previous = this->End;
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

            DoublyCircular<DataType> *node = new DoublyCircular<DataType>(value);

            if (this->Head == NULL)
            {
                node->next = node;
                this->Head = node;
                this->End = node;
                this->Size++;
                return;
            }

            this->End->next = node;
            node->previous = this->End;
            node->next = this->Head;
            this->Head->previous = node;
            this->Head = node;
            this->Size++;
        }

        DataType popBack()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->End->value;

            if (this->Head->next == this->Head)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
            }

            Doubly<DataType> *temp = this->End->previous;

            temp->next = this->End->next;
            delete this->End;
            this->End = temp;
            this->Head->previous = this->End;
            this->Size--;
            return value;
        }

        DataType popFront()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            DataType value = this->Head->value;

            if (this->Head->next == this->Head)
            {
                delete this->Head;
                this->Head = NULL;
                this->End = NULL;
                this->Size = 0;
                return value;
            }

            Doubly<DataType> *temp = this->Head;
            this->Head = this->Head->next;
            this->Head->previous = this->End;
            this->End->next = this->Head;
            delete temp;
            this->Size--;
            return value;
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

            if (index == (this->Size + 1))
            {
                this->pushBack(value);
                return;
            }

            DoublyCircular<DataType> *temp = this->Head;

            int i = 1;
            while (i < (index - 1))
            {
                temp = temp->next;
                i++;
            }

            DoublyCircular<DataType> *node = new DoublyCircular<DataType>(value);
            node->next = temp->next;
            temp->next->previous = node;
            temp->next = node;
            node->previous = temp;
            this->Size++;
        }

        DataType erase(int index)
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            if (index > (this->Size + 1) || index <= 0)
            {
                cout << "Index is Out of Range" << endl;
                return;
            }

            if (index == 1)
            {
                this->popFront();
                return;
            }

            if (index == this->Size)
            {
                this->popBack();
                return;
            }

            DoublyCircular<DataType> *prev = NULL;
            DoublyCircular<DataType> *curr = this->Head;

            int i = 1;
            while (i < index)
            {
                prev = curr;
                curr = curr->next;
                i++;
            }

            DataType value = curr->value;
            prev->next = curr->next;
            curr->next->previous = prev;
            delete curr;
            this->Size--;
            return value;
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
                return;
            }

            return this->Head->value;
        }

        DataType end()
        {
            if (this->Head == NULL)
            {
                cout << "Linked List is Empty" << endl;
                return;
            }

            return this->End->value;
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
                cout << "Linked List is Empty" << endl;
                return;
            }

            DoublyCircular<DataType> *prev = NULL;
            DoublyCircular<DataType> *curr = this->Head;

            do
            {
                prev = curr;
                curr = curr->next;
                delete prev;
            } while (curr != this->Head);
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

            DoublyCircular<DataType> *firstIndexNode = this->Head;
            DoublyCircular<DataType> *secondIndexNode = this->Head;

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

            DoublyCircular<DataType> *temp = this->Head;
            do
            {
                cout << temp->value << " ";
                temp = temp->next;
            } while (temp != this->Head);
            cout << endl;
        }
    };
}

// int main()
// {

//     return 0;
// }