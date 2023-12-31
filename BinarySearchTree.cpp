#include "Queue_BinaryTree.cpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename DataType> class TreeNode {
public:
  DataType value;
  TreeNode<DataType> *left;
  TreeNode<DataType> *right;

  TreeNode() {
    this->left = NULL;
    this->right = NULL;
  }

  TreeNode(DataType value) {
    this->value = value;
    this->left = NULL;
    this->right = NULL;
  }

  ~TreeNode() {
    this->left = NULL;
    this->right = NULL;
  }
};

template <typename DataType> class BinarySearchTree {
private:
  TreeNode<DataType> *root;

  void GenerateTree(TreeNode<DataType> *&root, int *levelNodeCount, int height,
                    int levelCount = 0) {
    if (levelCount == height) {
      return;
    }

    cout << endl;
    cout << "Level: " << levelCount << "\t\t"
         << "Node: " << levelNodeCount[levelCount] << endl;
    levelNodeCount[levelCount]++;
    int choice;
    cout << "Select from the Following: " << endl;
    cout << "1): Enter Data here" << endl;
    cout << "2): Keep it NULL" << endl;
    cout << "Enter your Choice here: ";
    cin >> choice;

    if (choice == 1) {
      DataType value;
      cout << endl;
      cout << "Enter Data here: ";
      cin >> value;
      TreeNode<DataType> *node = new TreeNode<DataType>(value);
      root = node;

      this->GenerateTree(root->left, levelNodeCount, height, levelCount + 1);
      this->GenerateTree(root->right, levelNodeCount, height, levelCount + 1);
    } else {
      return;
    }
  }

  void GetPreOrderTree(TreeNode<DataType> *root,
                       vector<TreeNode<DataType> *> *&container) {
    if (root == NULL) {
      return;
    }

    container->push_back(root);
    this->GetPreOrderTree(root->left, container);
    this->GetPreOrderTree(root->right, container);
  }

  void DeleteTree() {
    vector<TreeNode<DataType> *> *container =
        new vector<TreeNode<DataType> *>();
    this->GetPreOrderTree(this->root, container);

    for (int i = 0; i < container->size(); i++) {
      delete container->at(i);
    }

    delete container;
  }

  void GetInOrder(TreeNode<DataType> *root, vector<DataType> *&result) {
    if (root == NULL) {
      return;
    }

    this->GetInOrder(root->left, result);
    result->push_back(root->value);
    this->GetInOrder(root->right, result);
  }

  TreeNode<DataType> *BuildBST(vector<DataType> *result, int end,
                               int start = 0) {
    if (start > end) {
      return NULL;
    }

    int mid = (start + end) / 2;
    TreeNode<DataType> *root = new TreeNode<DataType>();
    root->value = result->at(mid);
    root->left = this->BuildBST(result, mid - 1, start);
    root->right = this->BuildBST(result, end, mid + 1);

    return root;
  }

  void MakeBST(TreeNode<DataType> *root) {
    vector<DataType> *result = new vector<DataType>();
    this->GetInOrder(this->root, result);

    sort(result->begin(), result->end());

    this->DeleteTree();

    this->root = this->BuildBST(result, result->size() - 1);

    delete result;
  }

  bool CheckBST(TreeNode<DataType> *root) {
    if (root == NULL) {
      return true;
    }

    bool left = true, right = true, leftCheck = true, rightCheck = true;

    left = this->CheckBST(root->left);
    right = this->CheckBST(root->right);

    if (root->left != NULL) {
      leftCheck = (root->left->value <= root->value);
    }

    if (root->right != NULL) {
      rightCheck = (root->right->value >= root->value);
    }

    if (left && right && leftCheck && rightCheck) {
      return true;
    } else {
      return false;
    }
  }

  void PreOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    cout << root->value << " ";
    this->PreOrder(root->left);
    this->PreOrder(root->right);
  }

  void InOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    this->InOrder(root->left);
    cout << root->value << " ";
    this->InOrder(root->right);
  }

  void PostOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    this->PostOrder(root->left);
    this->PostOrder(root->right);
    cout << root->value << " ";
  }

  void LevelOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    Queue<TreeNode<DataType> *> *container = new Queue<TreeNode<DataType> *>();
    container->push(root);
    container->push(NULL);

    TreeNode<DataType> *element = NULL;
    while (!container->empty()) {
      element = container->front();
      container->pop();

      if (element == NULL) {
        cout << endl;
        if (!container->empty()) {
          container->push(NULL);
        }
      } else {
        cout << element->value << " ";

        if (element->left != NULL) {
          container->push(element->left);
        }

        if (element->right != NULL) {
          container->push(element->right);
        }
      }
    }

    delete container;
  }

  void MorrisPreOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    TreeNode<DataType> *predecessor = NULL;
    while (root != NULL) {
      if (root->left == NULL) {
        cout << root->value << " ";
        root = root->right;
      } else {
        predecessor = root->left;
        while (predecessor->right != NULL && predecessor->right != root) {
          predecessor = predecessor->right;
        }

        if (predecessor->right == NULL) {
          predecessor->right = root;
          cout << root->value << " ";
          root = root->left;
        } else {
          predecessor->right = NULL;
          root = root->right;
        }
      }
    }
  }

  void MorrisInOrder(TreeNode<DataType> *root) {
    if (root == NULL) {
      return;
    }

    TreeNode<DataType> *predecessor = NULL;
    while (root != NULL) {
      if (root->left == NULL) {
        cout << root->value << " ";
        root = root->right;
      } else {
        predecessor = root->left;
        while (predecessor->right != NULL && predecessor->right != root) {
          predecessor = predecessor->right;
        }

        if (predecessor->right == NULL) {
          predecessor->right = root;
          root = root->left;
        } else {
          predecessor->right = NULL;
          cout << root->value << " ";
          root = root->right;
        }
      }
    }
  }

  void MorrisPostOrder(
      TreeNode<DataType> *root) { // fix this, its not working properly
    if (root == NULL) {
      return;
    }

    TreeNode<DataType> *copy = root;
    TreeNode<DataType> *predecessor = NULL;
    while (root != NULL) {
      if (root->left == NULL) {
        root = root->right;
      } else {
        predecessor = root->left;
        while (predecessor->right != NULL && predecessor->right != root) {
          predecessor = predecessor->right;
        }

        if (predecessor->right == NULL) {
          predecessor->right = root;
          root = root->left;
        } else {
          cout << predecessor->value << " ";
          TreeNode<DataType> *temp = NULL;
        }
      }
    }
  }

public:
  BinarySearchTree() { this->root = NULL; }

  ~BinarySearchTree() { this->root = NULL; }

  void GenerateBinaryTree() {
    int height = 0;

    cout << "Enter the Height of Binary Tree: " << endl;
    cin >> height;

    int *levelNodeCount = new int[height];

    for (int i = 0; i < height; i++) {
      levelNodeCount[i] = 0;
    }

    this->GenerateTree(this->root, levelNodeCount, height);

    delete[] levelNodeCount;
  }

  void GenerateBinarySearchTree() {
    int height = 0;

    cout << "Enter the Height of Binary Search Tree: " << endl;
    cin >> height;

    int *levelNodeCount = new int[height];

    for (int i = 0; i < height; i++) {
      levelNodeCount[i] = 0;
    }

    this->GenerateTree(this->root, levelNodeCount, height);

    this->MakeTreeBST();

    delete[] levelNodeCount;
  }

  int BinaryTreeHeight(TreeNode<DataType> *root) {
    if (root == NULL) {
      return 0;
    }

    int left = this->BinaryTreeHeight(root->left);
    int right = this->BinaryTreeHeight(root->right);

    return max(left, right) + 1;
  }

  void MakeTreeBST() {
    if (root == NULL) {
      return;
    }

    if (root->left == NULL && root->right == NULL) {
      return;
    }

    if (!(this->CheckTreeBST())) {
      this->MakeBST(this->root);
    }
  }

  bool CheckTreeBST() {
    if (root == NULL) {
      return true;
    }

    if (root->left == NULL && root->right == NULL) {
      return true;
    }

    return this->CheckBST(this->root);
  }

  TreeNode<DataType> *ReturnRoot() { return this->root; }

  void PreOrderTraversal() { this->PreOrder(this->root); }

  void InOrderTraversal() { this->InOrder(this->root); }

  void PostOrderTraversal() { this->PostOrder(this->root); }

  void LevelOrderTraversal() { this->LevelOrder(this->root); }

  void MorrisPreOrderTraversal() { this->MorrisPreOrder(this->root); }

  void MorrisInOrderTraversal() { this->MorrisInOrder(this->root); }

  void MorrisPostOrderTraversal() {
    // also fix this and write code for it
  }
};

// int main()
// {

//     return 0;
// }