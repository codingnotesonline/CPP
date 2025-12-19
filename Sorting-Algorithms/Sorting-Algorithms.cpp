#include <iostream>
#include "../HashMaps/HashMaps-Chaining.cpp"
using namespace std;

// always define the data type for array as int *, char *, float *, etc
template <typename DataType>
class SortingAlgorithms
{
private:
    DataType FindMax(DataType *container, int size)
    {
        DataType max = container[0];
        for (int i = 1; i < size; i++)
        {
            if (container[i] > max)
            {
                max = container[i];
            }
        }

        return max;
    }

    void MergeContainers(DataType *container, int start, int mid, int end)
    {
        int size1 = mid - start + 1;
        int size2 = end - mid;

        DataType *container1 = new DataType[size1];
        DataType *container2 = new DataType[size2];

        int index = 0;
        for (int i = start; i < (start + size1); i++)
        {
            container1[index++] = container[i];
        }

        index = 0;
        for (int j = (mid + 1); j < (mid + size2 + 1); j++)
        {
            container2[index++] = container[j];
        }

        index = start;
        int i = 0;
        int j = 0;

        while (i < size1 && j < size2)
        {
            if (container1[i] < container2[j])
            {
                container[index++] = container1[i++];
            }
            else
            {
                container[index++] = container2[j++];
            }
        }

        while (i < size1)
        {
            container[index++] = container1[i++];
        }

        while (j < size2)
        {
            container[index++] = container2[j++];
        }

        delete[] container1;
        delete[] container2;
    }

    void MergeSortAlgorithm(DataType *container, int start, int end)
    {
        if (start >= end)
        {
            return;
        }

        int mid = (start + end) / 2;
        this->MergeSortAlgorithm(container, start, mid);
        this->MergeSortAlgorithm(container, mid + 1, end);
        this->MergeContainers(container, start, mid, end);
    }

    int FindPivot(DataType *container, int start, int end)
    {
        DataType pivotElement = container[start];

        int count = 0;
        for (int i = start + 1; i <= end; i++)
        {
            if (container[i] <= pivotElement)
            {
                count++;
            }
        }

        int pivotIndex = start + count;
        this->swap(container[start], container[pivotIndex]);

        int i = start;
        int j = end;

        while (i < pivotIndex && j > pivotIndex)
        {
            if (container[i] <= pivotElement)
            {
                i++;
            }

            if (container[j] > pivotElement)
            {
                j--;
            }

            if (container[i] > pivotElement && container[j] <= pivotElement)
            {
                this->swap(container[i++], container[j--]);
                
            }

            // if(i < pivotIndex && j > pivotIndex){
            //     this->swap(container[i++], container[j--]);
            // }
        }

        return pivotIndex;
    }

    void QuickSortAlgorithm(DataType *container, int start, int end)
    {
        if (start >= end)
        {
            return;
        }

        int pivot = this->FindPivot(container, start, end);
        this->QuickSortAlgorithm(container, start, pivot - 1);
        this->QuickSortAlgorithm(container, pivot + 1, end);
    }

    void swap(DataType &element1, DataType &element2)
    {
        DataType temp;
        temp = element1;
        element1 = element2;
        element2 = temp;
    }

public:
    void BubbleSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        DataType temporary;

        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (container[j] > container[j + 1])
                {
                    this->swap(container[j], container[j + 1]);
                }
            }
        }
    }

    void SelectionSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        DataType temporary;
        int smallest;

        for (int i = 0; i < size; i++)
        {
            smallest = i;
            for (int j = i + 1; j < size; j++)
            {
                if (container[j] < container[smallest])
                {
                    smallest = j;
                }
            }

            if (smallest != i)
            {
                temporary = container[i];
                container[i] = container[smallest];
                container[smallest] = temporary;
            }
        }
    }

    void InsertionSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        DataType element;
        int j;
        for (int i = 1; i < size; i++)
        {
            element = container[i];
            j = i - 1;

            while (j >= 0 && container[j] > element)
            {
                container[j + 1] = container[j];
                j--;
            }

            if ((j + 1) != i)
            {
                container[j + 1] = element;
            }
        }
    }

    // shell sort is advanced/enhanced version of insertion sort
    void ShellSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        int gap = 3;

        DataType element;
        int j;

        while (gap > 0)
        {
            for (int i = gap; i < size; i += gap)
            {
                element = container[i];
                j = i - gap;

                while (j >= 0 && container[j] > element)
                {
                    container[j + gap] = container[j];
                    j -= gap;
                }

                if ((j + gap) != i)
                {
                    container[j + gap] = element;
                }
            }
            gap--;
        }
    }

    void MergeSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        this->MergeSortAlgorithm(container, 0, size - 1);
    }

    void QuickSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        this->QuickSortAlgorithm(container, 0, size - 1);
    }

    // equation: arr[0]>=arr[1]<=arr[2]>=arr[3]<=arr[4]...
    void WaveSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        DataType element;
        for (int i = 1; i < size - 1; i++)
        {
            if (container[i] > container[i - 1])
            {
                this->swap(container[i], container[i - 1]);
            }

            if (container[i] > container[i + 1])
            {
                this->swap(container[i], container[i + 1]);
            }
        }
    }

    void CountSort(DataType *container, int size)
    {
        if (size <= 1)
        {
            return;
        }

        HashMapsChaining<DataType, int> frequency;
        DataType max = this->FindMax(container, size);
        DataType element;
        for (int i = 0; i < size; i++)
        {
            element = container[i];
            frequency[element]++;
        }

        int count;
        int index = 0;
        for (int i = 0; i <= max; i++)
        {
            count = frequency[i];
            if (count != 0)
            {
                for (int j = 0; j < count; j++)
                {
                    container[index++] = i;
                }
            }
        }
    }

    // NOTE: Radix Sort = Bucket Sort
    // count sort is for sorting small numbers && radix sort is for sorting large numbers
    void RadixSort(DataType *container, int size)
    {
        
    }

    void print(DataType *container, int size)
    {
        if (size <= 0)
        {
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << container[i] << " ";
        }
        cout << endl;
    }
};

// Sorting class is only applicable with integers(int) because sorting is mostly performed on integers/strings (lexographical order only)
int main()
{
    int arr[] = {9, 2, 46, 24, 63, 18, 4, 13, 14, 50, 70};
    // int arr[] = {2, 2, 0, 0, 1, 1, 4, 1, 4, 0, 7, 4, 4, 1, 7, 2};
    // int arr[] = {3, 5, 7, 5, 2, 4, 9, 0, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    SortingAlgorithms<int> link;
    link.print(arr, size);
    link.ShellSort(arr, size);
    link.print(arr, size);
    return 0;
}