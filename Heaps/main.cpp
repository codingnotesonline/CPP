#include "Heaps.cpp"
#include <iostream>
#include <queue>
using namespace std;

int KthSmallestElement(int *arr, int size, int k)
{
  // steps to do
  // 1): put 1st kth element in the Max Heap
  // 2): (k/k+1) element < heap.top()
  // (2 (condition) == true)? (pop heap then push element): move on
  Heap<int> *container = new Heap<int>();

  for (int i = 0; i < k; i++)
  {
    container->push(arr[i]);
  }

  for (int j = k; j < size; j++)
  {
    if (arr[j] < container->top())
    {
      container->pop();
      container->push(arr[j]);
    }
  }

  int kthSmallest = container->top();
  delete container;

  return kthSmallest;
}

int *mergeTwoMaxHeaps(int *arr1, int *arr2, int s1, int s2)
{
  if (s1 <= 0 || s2 <= 0)
  {
    return NULL;
  }

  Heap<int> *container = new Heap<int>(0);

  for (int i = 0; i < s1; i++)
  {
    container->push(arr1[i]);
  }

  for (int j = 0; j < s2; j++)
  {
    container->push(arr2[j]);
  }

  return container->ReturnArray();
}

int *mergeTwoMinHeaps(int *arr1, int *arr2, int s1, int s2)
{
  if (s1 <= 0 || s2 <= 0)
  {
    return NULL;
  }

  Heap<int> *container = new Heap<int>(1);

  for (int i = 0; i < s1; i++)
  {
    container->push(arr1[i]);
  }

  for (int j = 0; j < s2; j++)
  {
    container->push(arr2[j]);
  }

  return container->ReturnArray();
}

void printArray(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << arr[i] << " ";
  }

  cout << endl;
}

int sigNum(int a, int b){
  if(a == b){
    return 0;
  }
  else if(a > b){
    return 1;
  }
  else{
    return -1;
  }
}

void CalculateMedian(Heap<int> &maxHeap, Heap<int> &minHeap, int num, float &median)
{
  int expression = sigNum(maxHeap.size(), minHeap.size());
  switch (expression)
  {
  case 0:
    if (num > median)
    {
      minHeap.push(num);
      median = minHeap.top();
    }
    else
    {
      maxHeap.push(num);
      median = maxHeap.top();
    }
    break;
  case 1:
    if (num > median)
    {
      minHeap.push(num);
      median = (maxHeap.top() + minHeap.top()) / 2.0;
    }
    else
    {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
      maxHeap.push(num);
      median = (maxHeap.top() + minHeap.top()) / 2.0;
    }
    break;
  case -1:
    if (num > median)
    {
      maxHeap.push(minHeap.top());
      minHeap.pop();
      minHeap.push(num);
      median = (maxHeap.top() + minHeap.top()) / 2.0;
    }
    else
    {
      maxHeap.push(num);
      median = (maxHeap.top() + minHeap.top()) / 2.0;
    }
    break;
  }
}

// max heap will be stored in descending order
// min heap will be stored in ascending order
void printSeries(Heap<int> maxHeap, Heap<int> minHeap)
{
  int *arr1 = maxHeap.ReturnArray();
  int *arr2 = minHeap.ReturnArray();

  for (int i = (maxHeap.size() - 1); i >= 0; i--)
  {
    cout << arr1[i] << " ";
  }

  for (int j = 0; j < minHeap.size(); j++)
  {
    cout << arr2[j] << " ";
  }
  cout << endl;
}

int main()
{
  // 0 for MaxHeap, 1 for MinHeap
  // int arr[] = {2, 6, 1, 9, 0, 4};
  // int size = sizeof(arr)/sizeof(arr[0]);

  // printArray(arr, size);
  // cout<<"Kth Smallest Element is: "<<KthSmallestElement(arr, size, 4)<<endl;

  // int arr1[] = {7, 5, 3, 1, 0};
  // int arr2[] = {6, 4, 2};

  // int s1 = sizeof(arr1)/sizeof(arr1[0]);
  // int s2 = sizeof(arr2)/sizeof(arr2[0]);

  // printArray(mergeTwoMaxHeaps(arr1, arr2, s1, s2), s1+s2);

  // try to solve the problem in this question 
  Heap<int> maxHeap;
  Heap<int> minHeap(1);
  float median = 0;
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
      CalculateMedian(maxHeap, minHeap, num, median);

      printSeries(maxHeap, minHeap);
      cout << "Median: " << median << endl;
      cout << endl;
    }
    else
    {
      cout << "Quiting..." << endl;
      break;
    }

  } while (true);
}