#include <iostream>
using namespace std;

int totalSize = 10;

void ReInitializeArray(int *&container)
{
    int *temp = container;
    int tempSize = totalSize;
    totalSize += totalSize;

    container = new int[totalSize];
    for (int i = 0; i < tempSize; i++)
    {
        container[i] = temp[i];
    }

    delete[] temp;
}

void InsertAtRightPlace(int *&container, int num, int &size)
{
    if (size == 0)
    {
        container[size] = num;
        size++;
        return;
    }

    if (size == (totalSize - 1))
    {
        ReInitializeArray(container);
    }

    int i = size - 1;
    while (i >= 0 && (container[i] > num))
    {
        container[i + 1] = container[i];
        i--;
    }
    i++;
    container[i] = num;
    size++;
}

float findMedian(int *&container, int size)
{
    if (size == 0)
    {
        cout << "No Elements Found!!" << endl;
        return 0;
    }

    if (size == 1)
    {
        return container[0];
    }

    bool Odd = size % 2;
    int mid = size / 2;
    if (Odd)
    {
        return container[mid];
    }
    else
    {
        int mid_2 = (size - 1) / 2;
        float answer = (container[mid] + container[mid_2]) / 2.0;
        return answer;
    }
}

// for each loop in c++ applied on thoe data structures that have a proper begin and end functions
void printSeries(int *container, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << container[i] << " ";
    }
    cout << endl;
}

int main()
{
    int size = 0;
    int *container = new int[totalSize];
    float median;
    int num;
    int choice;

    do
    {
        cout << "Choose from the following: " << endl;
        cout << "1): Add Number" << endl;
        cout << "0): Quit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Number here: ";
            cin >> num;
            InsertAtRightPlace(container, num, size);
            median = findMedian(container, size);

            printSeries(container, size);
            cout << "Median: " << median << endl;
            cout << endl;
        }
        else
        {
            cout << "Quiting..." << endl;
            break;
        }

    } while (true);

    return 0;
}
