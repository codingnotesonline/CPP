#include <iostream>
using namespace std;

template <typename DataType>
class Deque{
private:
    DataType *container;
    int Front;
    int Back;
    int Size;
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
    Deque()
    {
        this->restricted = false;
        this->MaxSize = 10;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    Deque(int size)
    {
        this->restricted = true;
        this->MaxSize = size;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    ~Deque()
    {
        this->restricted = false;
        this->MaxSize = 0;
        this->Front = -1;
        this->Back = -1;
        this->Size = 0;
        delete[] this->container;
    }

    void pushBack(DataType element)
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

    void pushFront(DataType element)
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

        if (this->Front == 0)
        {
            this->Front = this->MaxSize;
        }

        this->Front--;
        this->container[Front] = element;
        this->Size++;
    }

    void popFront()
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

    void popBack()
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

        if ((this->Front > this->Back) && this->Back == 0)
        {
            this->Back = this->MaxSize;
        }

        this->Back--;
        this->Size--;
    }

    void insert(DataType element, int index){

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
class TwoDeques{

};

template <typename DataType>
class NDeques{
    
};

