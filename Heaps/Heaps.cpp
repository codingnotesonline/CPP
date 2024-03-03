#include <iostream>
#include <queue>
using namespace std;

template <typename DataType> class HeapFunctions;

template <typename DataType> class Heap {
private:
  HeapFunctions<DataType> *Functions;
  DataType *Array;
  int TotalNodes;
  bool MinHeap;
  int ArraySize = 5;

  void InitializeArray() {
    this->ArraySize += this->ArraySize;
    this->Array = new DataType[ArraySize];
  }

  bool IsArrayFull() {
    if (this->TotalNodes == (this->ArraySize - 2)) {
      return true;
    } else {
      return false;
    }
  }

  void ReInitializeArray() {
    DataType *tempArray = this->Array;
    int tempSize = this->ArraySize;
    this->InitializeArray();

    for (int i = 1; i < tempSize; i++) {
      this->Array[i] = tempArray[i];
    }

    delete[] tempArray;
  }

  void HeapifyAfterPush(int Index) {
    if (this->TotalNodes <= 1) {
      return;
    }

    if (Index > 1) {
      if (!this->MinHeap) {
        int smallest = Index;
        int parent = Index / 2;

        if (smallest <= this->TotalNodes &&
            (this->Array[smallest] > this->Array[parent])) {
          swap(this->Array[smallest], this->Array[parent]);
          smallest = parent;
          this->HeapifyAfterPush(smallest);
        } else {
          return;
        }
      } else {
        int largest = Index;
        int parent = Index / 2;

        if (largest <= this->TotalNodes &&
            (this->Array[largest] < this->Array[parent])) {
          swap(this->Array[largest], this->Array[parent]);
          largest = parent;
          this->HeapifyAfterPush(largest);
        } else {
          return;
        }
      }
    }
  }

  void HeapifyAfterPop(int Index) {
    if (Index >= 1) {
      if (!this->MinHeap) {
        int largest = Index;
        int leftChild = 2 * Index;
        int rightChild = 2 * Index + 1;

        if (leftChild <= this->TotalNodes &&
            (this->Array[leftChild] > this->Array[largest])) {
          largest = leftChild;
        }

        if (rightChild <= this->TotalNodes &&
            (this->Array[rightChild] > this->Array[largest])) {
          largest = rightChild;
        }

        if (largest != Index) {
          swap(this->Array[largest], this->Array[Index]);
          this->HeapifyAfterPop(largest);
        }
      } else {
        int smallest = Index;
        int leftChild = 2 * Index;
        int rightChild = 2 * Index + 1;

        if (leftChild <= this->TotalNodes &&
            (this->Array[leftChild] < this->Array[smallest])) {
          smallest = leftChild;
        }

        if (rightChild <= this->TotalNodes &&
            (this->Array[rightChild] < this->Array[smallest])) {
          smallest = rightChild;
        }

        if (smallest != Index) {
          swap(this->Array[smallest], this->Array[Index]);
          this->HeapifyAfterPop(smallest);
        }
      }
    }
  }

public:
  Heap() {
    this->InitializeArray();
    this->TotalNodes = 0;
    this->MinHeap = false;
    this->Functions = new HeapFunctions<DataType>(this->MinHeap);
    this->Array[0] = -1;
  }

  Heap(bool MinHeap) {
    this->InitializeArray();
    this->TotalNodes = 0;
    this->MinHeap = MinHeap;
    this->Functions = new HeapFunctions<DataType>(this->MinHeap);
    this->Array[0] = -1;
  }

  ~Heap() {
    delete[] this->Array;
    delete this->Functions;
    this->TotalNodes = 0;
  }

  void push(DataType element) {
    if (this->IsArrayFull()) {
      this->ReInitializeArray();
    }

    this->TotalNodes++;
    this->Array[TotalNodes] = element;

    this->HeapifyAfterPush(this->TotalNodes);
  }

  DataType pop() {
    if (this->TotalNodes == 0) {
      return -1;
    }

    DataType NodeToReturn;
    NodeToReturn = this->Array[1];
    this->Array[1] = this->Array[TotalNodes];
    this->TotalNodes--;

    this->HeapifyAfterPop(1);

    return NodeToReturn;
  }

  void sort() {
    this->Functions->HeapSort(this->Array, this->TotalNodes);
    this->MinHeap = true;
    this->Functions->ChangeHeapOrder(true);
  }

  int HeapOrder() {
    if (!this->MinHeap) {
      return 0;
    } else {
      return 1;
    }
  }

  int size() { return this->TotalNodes; }

  void print() { this->Functions->PrintHeap(this->Array, this->TotalNodes); }

  void PrintLevelOrder() {
    this->Functions->PrintHeapLevelOrder(this->Array, this->TotalNodes);
  }

  DataType top() { return this->Array[1]; }

  bool empty() {
    if (this->TotalNodes == 0) {
      return true;
    } else {
      return false;
    }
  }

  DataType *ReturnArray() { return (&this->Array[1]); }
};

template <typename DataType> class HeapFunctions {
private:
  bool MinHeap;

  void BuildMaxHeap(DataType *&arr, int index, int size) {
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= size) {
      BuildMaxHeap(arr, left, size);
    }

    if (right <= size) {
      BuildMaxHeap(arr, right, size);
    }

    int parent = index / 2;
    if (parent >= 1) {
      if (arr[index] > arr[parent]) {
        swap(arr[index], arr[parent]);
      }
    } else {
      return;
    }
  }

  void BuildMinHeap(DataType *&arr, int index, int size) {
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= size) {
      BuildMinHeap(arr, left, size);
    }

    if (right <= size) {
      BuildMinHeap(arr, right, size);
    }

    int parent = index / 2;
    if (parent >= 1) {
      if (arr[index] < arr[parent]) {
        swap(arr[index], arr[parent]);
      }
    } else {
      return;
    }
  }

  void AsscendingHeapSort(DataType *&arr, int size) {
    while (size > 1) {
      swap(arr[1], arr[size]);
      size--;

      this->Heapify(arr, size, 1);
    }
  }

  void DesscendingHeapSort(DataType *&arr, int size) {
    while (size > 1) {
      swap(arr[1], arr[size]);
      size--;

      this->Heapify(arr, size, 1);
    }
  }

  void AsscendingSort(DataType *&arr, int size) {
    BuildMaxHeap(arr, 1, size);

    AsscendingHeapSort(arr, size);
  }

  void DesscendingSort(DataType *&arr, int size) {
    BuildMinHeap(arr, 1, size);

    DesscendingHeapSort(arr, size);
  }

public:
  HeapFunctions() { this->MinHeap = false; }

  HeapFunctions(bool MinHeap) { this->MinHeap = MinHeap; }

  void Heapify(DataType *&Array, int Size, int Index) {
    if (Index >= 1) {
      if (!this->MinHeap) {
        int largest = Index;
        int leftChild = 2 * Index;
        int rightChild = 2 * Index + 1;

        if (leftChild <= Size && (Array[leftChild] > Array[largest])) {
          largest = leftChild;
        }

        if (rightChild <= Size && (Array[rightChild] > Array[largest])) {
          largest = rightChild;
        }

        if (largest != Index) {
          swap(Array[largest], Array[Index]);
          this->Heapify(Array, Size, largest);
        }
      } else {
        int smallest = Index;
        int leftChild = 2 * Index;
        int rightChild = 2 * Index + 1;

        if (leftChild <= Size && (Array[leftChild] < Array[smallest])) {
          smallest = leftChild;
        }

        if (rightChild <= Size && (Array[rightChild] < Array[smallest])) {
          smallest = rightChild;
        }

        if (smallest != Index) {
          swap(Array[smallest], Array[Index]);
          this->Heapify(Array, Size, smallest);
        }
      }
    }
  }

  void HeapSort(DataType *&Array, int size) {
    if (!this->MinHeap) {
      this->AsscendingSort(Array, size);
    } else {
      this->DesscendingSort(Array, size);
    }
  }

  void ChangeHeapOrder(bool MinHeap) { this->MinHeap = MinHeap; }

  void PrintHeap(DataType *Array, int size) {
    for (int i = 1; i <= size; i++) {
      cout << Array[i] << " ";
    }

    cout << endl;
  }

  void PrintHeapLevelOrder(DataType *Array, int size) {
    if (size < 1) {
      return;
    }

    queue<DataType> *container = new queue<DataType>();
    container->push(1);
    container->push(-1);

    DataType element;
    DataType left, right;
    while (!container->empty()) {
      element = container->front();
      container->pop();

      if (element == -1) {
        cout << endl;
        if (!container->empty()) {
          container->push(-1);
        }
      } else {
        cout << Array[element] << " ";
        left = 2 * element;
        right = 2 * element + 1;

        if (left <= size) {
          container->push(left);
        }

        if (right <= size) {
          container->push(right);
        }
      }
    }

    delete container;
  }
};

// int main() { return 0; }