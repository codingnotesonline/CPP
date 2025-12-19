#include <iostream>
#include <limits.h>
using namespace std;

template <typename DataType>
class PriorityQueueNode
{
public:
    DataType value;
    int priority;

    PriorityQueueNode()
    {
        this->priority = INT_MIN;
    }

    PriorityQueueNode(int priority)
    {
        this->priority = priority;
    }

    PriorityQueueNode(DataType value, int priority)
    {
        this->value = value;
        this->priority = priority;
    }
};

template <typename DataType>
class PriorityQueue
{
private:
    PriorityQueueNode<DataType> **container;
    int MaxSize;
    int Size;
    int Front;
    int Back;
    bool restricted;

    void ReInitializeArray()
    {
        PriorityQueueNode<DataType> **oldContainer = this->container;
        int oldMaxSize = this->MaxSize;
        this->MaxSize += this->MaxSize;
        this->container = new PriorityQueueNode<DataType> *[MaxSize];
        
        for (int i = 0; i < this->MaxSize; i++)
        {
            this->container[i] = NULL;
        }

        int index = 0;
        for (int i = this->Front; i < oldMaxSize; i++)
        {
            this->container[index++] = oldContainer[i];
        }

        if (this->Front > this->Back)
        {
            for (int i = 0; i <= this->Back; i++)
            {
                this->container[index++] = oldContainer[i];
            }
        }

        this->Front = 0;
        this->Back = index - 1;

        delete[] oldContainer;
    }

public:
    PriorityQueue()
    {
        this->restricted = false;
        this->MaxSize = 10;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new PriorityQueueNode<DataType> *[MaxSize];
        for (int i = 0; i < this->MaxSize; i++)
        {
            this->container[i] = NULL;
        }
    }

    PriorityQueue(int size)
    {
        this->restricted = true;
        this->MaxSize = size;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new PriorityQueueNode<DataType> *[MaxSize];
        for (int i = 0; i < this->MaxSize; i++)
        {
            this->container[i] = NULL;
        }
    }

    ~PriorityQueue()
    {
        for (int i = 0; i < this->MaxSize; i++)
        {
            if (this->container[i] != NULL)
            {
                delete this->container[i];
            }
        }
        this->restricted = false;
        this->MaxSize = 0;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        delete[] this->container;
    }

    void enque(DataType element, int priority)
    {
        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Priority Queue Overflow" << endl;
            return;
        }

        if (!this->restricted && (this->Size == (this->MaxSize - 1)))
        {
            this->ReInitializeArray();
        }

        PriorityQueueNode<DataType> *node = new PriorityQueueNode<DataType>(element, priority);
        if (this->Front == -1)
        {
            this->Front++;
            this->Back++;

            this->container[Back] = node;
            this->Size++;
            return;
        }

        int tempBack = this->Back;
        PriorityQueueNode<DataType> *tempNode;

        // if the front is greater than the back, i.e: queue is circular
        if (this->Front > this->Back)
        {
            // first handle the elements from 0 to back
            while (tempBack >= 0)
            {
                tempNode = this->container[tempBack];
                if (tempNode->priority >= priority)
                {
                    this->container[tempBack + 1] = node;
                    this->Size++;
                    this->Back++;
                    return;
                }

                this->container[tempBack + 1] = tempNode;
                tempBack--;
            }

            // if priority is still greater
            if (tempBack == -1)
            {
                tempBack = this->MaxSize - 1;
                this->container[0] = this->container[tempBack];
                tempBack--;
            }

            // now start matching priority from MaxSize - 1 to front
            while (tempBack >= this->Front)
            {
                tempNode = this->container[tempBack];
                if (tempNode->priority >= priority)
                {
                    this->container[tempBack + 1] = node;
                    this->Size++;
                    this->Back++;
                    return;
                }

                this->container[tempBack + 1] = tempNode;
                tempBack--;
            }

            // if element has the highest priority
            this->container[tempBack + 1] = node;
            this->Size++;
            this->Back++;
        }
        else
        {
            // if queue is straight forward

            // if we are at the end of container then check that the ndoe we have to insert has the lowest priority
            if (tempBack == this->MaxSize - 1)
            {
                tempNode = this->container[tempBack];
                this->Back = 0;

                if (tempNode->priority >= priority)
                {
                    this->container[Back] = node;
                    this->Size++;
                    return;
                }
                else
                {
                    this->container[Back] = tempNode;
                    tempBack--;
                }
            }
            else
            {
                this->Back++;
            }

            // traverse the whole container and check the priority and insert the node where it should be
            while (tempBack >= this->Front)
            {
                tempNode = this->container[tempBack];
                if (tempNode->priority >= priority)
                {
                    this->container[tempBack + 1] = node;
                    this->Size++;
                    return;
                }

                this->container[tempBack + 1] = tempNode;
                tempBack--;
            }

            // if element has the highest priority
            this->container[tempBack + 1] = node;
            this->Size++;
        }
    }

    void deque()
    {
        if (this->Front == -1)
        {
            cout << "Priority Queue Underflow" << endl;
        }

        if (this->Size == 1)
        {
            this->Front = -1;
            this->Back = -1;
            this->Size--;
            return;
        }

        if ((this->Front > this->Back) && this->Front == (this->MaxSize - 1))
        {
            this->Front = -1;
        }

        this->Front++;
        this->Size--;
    }

    int size()
    {
        return this->Size;
    }

    PriorityQueueNode<DataType> front()
    {
        if (this->Front == -1)
        {
            return PriorityQueueNode<DataType>();
        }

        return this->container[Front];
    }

    PriorityQueueNode<DataType> back()
    {
        if (this->Front == -1)
        {
            return PriorityQueueNode<DataType>();
        }

        return this->container[Back];
    }

    PriorityQueueNode<DataType> *begin()
    {
        if (this->Front == -1)
        {
            return &PriorityQueueNode<DataType>();
        }

        return &this->container[Front];
    }

    PriorityQueueNode<DataType> *end()
    {
        if (this->Front == -1)
        {
            return &PriorityQueueNode<DataType>();
        }

        return &this->container[Back];
    }

    bool empty()
    {
        if (this->Back == -1)
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
        if (this->Front == -1)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        if (this->restricted)
        {
            for (int i = 0; i < this->MaxSize; i++)
            {
                if (this->container[i] != NULL)
                {
                    delete this->container[i];
                }
            }
        }

        if (!this->restricted)
        {
            for (int i = 0; i < this->MaxSize; i++)
            {
                if (this->container[i] != NULL)
                {
                    delete this->container[i];
                }
            }
            this->MaxSize = 10;
            delete[] this->container;
            this->container = new PriorityQueueNode<DataType> *[MaxSize];
        }

        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
    }

    void print()
    {
        if (this->Front == -1)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Front -> ";

        if (this->Front > this->Back)
        {
            for (int i = this->Front; i < this->MaxSize; i++)
            {
                cout << "(" << this->container[i]->value << ", " << this->container[i]->priority << ")" << " ";
            }

            for (int i = 0; i <= this->Back; i++)
            {
                cout << "(" << this->container[i]->value << ", " << this->container[i]->priority << ")" << " ";
            }
        }
        else
        {
            for (int i = this->Front; i <= this->Back; i++)
            {
                cout << "(" << this->container[i]->value << ", " << this->container[i]->priority << ")" << " ";
            }
        }

        cout << "<- Back";
        cout << endl;
    }
};

template <typename DataType>
class TwoPriorityQueues
{
};

template <typename DataType>
class NPriorityQueues
{
};

int main()
{
    PriorityQueue<int> queue;
    queue.enque(10, 4);
    queue.enque(15, 2);
    queue.enque(1, 0);
    queue.enque(20, 6);
    queue.enque(8, 1);
    queue.enque(80, 1);
    queue.enque(13, 3);
    queue.enque(100, 10);

    queue.print();
    return 0;
}