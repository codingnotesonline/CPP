#include <iostream>
using namespace std;

template <typename DataType>
class Queue
{
private:
    DataType *container;
    int Size;
    int Front;
    int Back;
    int MaxSize;
    bool restricted;

    void ReInitializeArray()
    {
        DataType *oldContainer = this->container;
        int oldMaxSize = this->MaxSize;
        this->MaxSize += this->MaxSize;
        this->container = new DataType[MaxSize];

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

    int FindValue(DataType element){
        int index = -1;
        for (int i = 0; i < this->Size; i++)
        {
            if (this->container[i] == element)
            {
                index = (i + 1);
                break;
            }
        }
        
        return index;
    }

public:
    Queue()
    {
        this->restricted = false;
        this->MaxSize = 10;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    Queue(int size)
    {
        this->restricted = true;
        this->MaxSize = size;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    ~Queue()
    {
        this->restricted = false;
        this->MaxSize = 0;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        delete[] this->container;
    }

    void enque(DataType element)
    {
        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        if (!this->restricted && (this->Size == (this->MaxSize - 1)))
        {
            this->ReInitializeArray();
        }

        if (this->Front == -1)
        {
            this->Front++;
            this->Back++;

            this->container[Back] = element;
            this->Size++;
            return;
        }

        if ((this->Back + 1) == this->MaxSize)
        {
            this->Back = -1;
        }

        this->Back++;
        this->container[Back] = element;
        this->Size++;
    }

    void deque()
    {
        if (this->Front == -1)
        {
            cout << "Queue Underflow" << endl;
            return;
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

    void insert(DataType element, int index){
        if (index < 1 || index > this->Size)
        {
            cout << "Index Exception Out of bound" << endl;
            return;
        }

        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        if (!this->restricted && (this->Size == (this->MaxSize - 1)))
        {
            this->ReInitializeArray();
        }

        if(this->Front == -1){
            this->enque(element);
            return;
        }

        if(index == (this->Size + 1)){
            this->enque(element);
            return;
        }

        int insertAt = this->Front + index;
        if(index > this->MaxSize){
            index = 0 + (index - this->MaxSize);
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

    void erase(int index){

    }

    void remove(DataType element){
        
    }

    DataType front()
    {
        return this->container[Front];
    }

    DataType back()
    {
        return this->container[Back];
    }

    DataType *begin(){
        if(this->Front == -1){
            return NULL;
        }

        return &this->container[Front];
    }

    DataType *end(){
        if(this->Front == -1){
            return NULL;
        }

        return &this->container[Back];
    }

    int size()
    {
        return this->Size;
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

    void clear(){
        if(this->Front == -1){
            cout<<"Queue is empty"<<endl;
            return;
        }

        if(!this->restricted){
            this->MaxSize = 10;
            delete[] this->container;
            this->container = new DataType[MaxSize];
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
                cout << this->container[i] << " ";
            }

            for (int i = 0; i <= this->Back; i++)
            {
                cout << this->container[i] << " ";
            }
        }
        else{
            for(int i=this->Front;i<=this->Back;i++){
                cout << this->container[i] << " ";
            }
        }

        cout << "<- Back";
        cout << endl;
    }
};

template <typename DataType>
class TwoQueues
{
};

template <typename DataType>
class NQueues
{
};

int main()
{
    Queue<int> container;
    container.enque(0);
    container.enque(1);
    container.enque(2);
    container.enque(3);
    container.enque(4);
    container.enque(5);
    container.enque(6);
    container.enque(7);
    container.enque(8);
    container.deque();
    container.deque();
    container.deque();
    container.enque(9);
    container.enque(10);
    container.enque(11);
    container.enque(12);
    container.enque(13);
    container.enque(14);
    container.enque(15);

    container.deque();
    container.deque();

    container.print();
    return 0;
}