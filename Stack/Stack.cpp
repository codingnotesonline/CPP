#include <iostream>
using namespace std;

template <typename DataType>
class Stack
{
private:
    DataType *container;
    int Top;
    int Size;
    int MaxSize;
    bool restricted;

    void ReInitializeArray()
    {
        this->MaxSize += this->MaxSize;
        DataType *oldContainer = this->container;
        this->container = new DataType[MaxSize];

        for (int i = 0; i < this->Size; i++)
        {
            this->container[i] = oldContainer[i];
        }

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
    Stack()
    {
        this->restricted = false;
        this->MaxSize = 10;
        this->Top = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    Stack(int size)
    {
        this->restricted = true;
        this->MaxSize = size;
        this->Top = -1;
        this->Size = 0;
        this->container = new DataType[MaxSize];
    }

    ~Stack()
    {
        this->restricted = false;
        this->MaxSize = 0;
        this->Top = -1;
        this->Size = 0;
        delete[] this->container;
    }

    void push(DataType element)
    {
        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        if (!this->restricted && (this->Size == (this->MaxSize - 1)))
        {
            this->ReInitializeArray();
        }

        this->Top++;
        this->container[Top] = element;
        this->Size++;
    }

    void pop()
    {
        if (this->Top == -1)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        this->Top--;
        this->Size--;
    }

    // calculating fromt the bottom
    void insert(DataType element, int index)
    {
        if (index < 1 || index > this->Size)
        {
            cout << "Index Exception Out of bound" << endl;
            return;
        }

        if (this->restricted && (this->Size == this->MaxSize))
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        if (this->Top == -1)
        {
            this->push(element);
            return;
        }

        if (!this->restricted && (this->Size == (this->MaxSize - 1)))
        {
            this->ReInitializeArray();
        }

        if (index == (this->Size + 1))
        {
            this->push(element);
            return;
        }

        int tempSize = this->Size - 1;
        for (int i = tempSize; i >= (index - 1); i--)
        {
            this->container[i + 1] = this->container[i];
        }

        this->container[index - 1] = element;
        this->Size++;
        this->Top++;
    }

    void erase(int index)
    {
        if (index < 1 || index > this->Size)
        {
            cout << "Index Exception Out of bound" << endl;
            return;
        }

        if (this->Top == -1)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        if (index == this->Size)
        {
            this->pop();
            return;
        }

        for (int i = index; i <= this->Size; i++)
        {
            this->container[i - 1] = this->container[i];
        }

        this->Size--;
        this->Top--;
    }

    void remove(DataType element)
    {
        if (this->Top == -1)
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        int index = this->FindValue(element);

        if (index == -1)
        {
            cout << "Value does not Exist" << endl;
        }
        else{
            this->erase(index);
        }
    }

    DataType top()
    {
        return this->container[Top];
    }

    DataType *begin()
    {
        if (this->Top == -1)
        {
            return NULL;
        }

        return &this->container[0];
    }

    DataType *end()
    {
        if (this->Top == -1)
        {
            return NULL;
        }

        return &this->container[Top];
    }

    int size()
    {
        return this->Size;
    }

    bool empty()
    {
        if (this->Top == -1)
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
        if (this->Top == -1)
        {
            cout << "Stack is empty" << endl;
            return;
        }

        if (!this->restricted)
        {
            this->MaxSize = 10;
            delete[] this->container;
            this->container = new DataType[MaxSize];
        }

        this->Top = -1;
        this->Size = 0;
    }

    void print()
    {
        if (this->Top == -1)
        {
            cout << "Stack is empty" << endl;
            return;
        }

        cout << "Top -> ";

        for (int i = (this->Size - 1); i >= 0; i--)
        {
            cout << this->container[i] << " ";
        }
        cout << endl;
    }
};

template <typename DataType>
class TwoStacks
{
};

template <typename DataType>
class NStacks
{
};

// int main(){
//     Stack<string> __1;
//     __1.push("1");
//     __1.push("10");
//     __1.push("100");
//     __1.push("1000");
//     __1.push("10000");
//     __1.push("100000");
//     return 0;
// }