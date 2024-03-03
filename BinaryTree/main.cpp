#include "BinaryTree.cpp"
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

// Problem: Minimum Time to burn the entire tree :: for fixing this you need to
// make new map
void storeMapping(TreeNode<int> *root, int target, TreeNode<int> *&targetNode,
                  map<TreeNode<int> *, TreeNode<int> *> *&nodeToParent) {
  if (root == NULL) {
    return;
  }

  if (root->value == target) {
    targetNode = root;
  }

  if (root->left != NULL) {
    nodeToParent->insert(make_pair(root->left, root));
    storeMapping(root->left, target, targetNode, nodeToParent);
  }

  if (root->right != NULL) {
    nodeToParent->insert(make_pair(root->right, root));
    storeMapping(root->right, target, targetNode, nodeToParent);
  }
}

int burnTree(TreeNode<int> *targetNode,
             map<TreeNode<int> *, TreeNode<int> *> *nodeToParent) {
  map<TreeNode<int> *, bool> *visited = new map<TreeNode<int> *, bool>();
  Queue<TreeNode<int> *> *container = new Queue<TreeNode<int> *>();

  int seconds = 0;
  container->push(targetNode);
  visited->insert(make_pair(targetNode, true));

  TreeNode<int> *element = NULL;
  TreeNode<int> *parent = NULL;
  while (!container->empty()) {
    element = container->front();
    container->pop();

    parent = nodeToParent->at(element);
    if (parent != NULL && (!visited->count(parent))) {
      container->push(parent);
      visited->insert(make_pair(parent, true));
    }

    if (element->left != NULL && (!visited->count(element->left))) {
      container->push(element->left);
      visited->insert(make_pair(element->left, true));
    }

    if (element->right != NULL && visited->count(element->right)) {
      container->push(element->right);
      visited->insert(make_pair(element->right, true));
    }

    seconds++;
  }

  delete visited;
  delete container;

  return seconds;
}

#include <algorithm>
#include <vector>

void BSTInOrder(TreeNode<int> *root, vector<int> *&inOrder) {
  if (root == NULL) {
    return;
  }

  BSTInOrder(root->left, inOrder);
  inOrder->push_back(root->value);
  BSTInOrder(root->right, inOrder);
}

vector<int> *mergeTwoArrays(vector<int> *array1, vector<int> *array2) {
  if (array1 == NULL) {
    return array2;
  }

  if (array2 == NULL) {
    return array1;
  }

  vector<int> *answer = new vector<int>();
  int i = 0, j = 0;

  while (i < array1->size() && j < array2->size()) {
    if (array1->at(i) <= array2->at(j)) {
      answer->push_back(array1->at(i));
      i++;
    } else {
      answer->push_back(array2->at(j));
      j++;
    }
  }

  while (i < array1->size()) {
    answer->push_back(array1->at(i));
    i++;
  }

  while (j < array2->size()) {
    answer->push_back(array2->at(j));
    j++;
  }

  return answer;
}

TreeNode<int> *inOrderToBST(TreeNode<int> *root, vector<int> *inOrder, int end,
                            int start = 0) {
  if (start > end) {
    return new TreeNode<int>(inOrder->at(start));
  }

  int mid = (start + end) / 2;
  TreeNode<int> *node = new TreeNode<int>(inOrder->at(mid));
  root = node;

  root->left = inOrderToBST(root->left, inOrder, mid - 1, start);
  root->right = inOrderToBST(root->right, inOrder, end, mid + 1);

  return root;
}

void print(vector<int> *array) {
  if (array == NULL) {
    return;
  }

  for (auto it = array->begin(); it != array->end(); it++) {
    cout << (*it) << " ";
  }

  cout << endl;
}

void LevelOrder(TreeNode<int> *root) {
  if (root == NULL) {
    return;
  }

  Queue<TreeNode<int> *> *container = new Queue<TreeNode<int> *>();
  container->push(root);
  container->push(NULL);

  TreeNode<int> *element = NULL;
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

int treeNodeCount(TreeNode<int> *root) {
  if (root == NULL) {
    return 0;
  }

  int left = treeNodeCount(root->left);
  int right = treeNodeCount(root->right);

  return left + right + 1;
}

bool isTreeCBT(TreeNode<int> *root, int totalNodes, int index = 1) {
  if (root == NULL) {
    return true;
  }

  if (index > totalNodes) {
    return false;
  }

  bool left = isTreeCBT(root->left, totalNodes, 2 * index);
  bool right = isTreeCBT(root->right, totalNodes, 2 * index + 1);

  return left && right;
}

bool isMaxHeap(TreeNode<int> *root) {
  if (root == NULL) {
    return true;
  }

  bool left = true, right = true, leftCheck = true, rightCheck = true;

  left = isMaxHeap(root->left);
  right = isMaxHeap(root->right);

  if (root->left != NULL) {
    leftCheck = root->value >= root->left->value;
  }

  if (root->right != NULL) {
    rightCheck = root->value >= root->right->value;
  }

  if (left && right && leftCheck && rightCheck) {
    return true;
  } else {
    return false;
  }
}

bool isMinHeap(TreeNode<int> *root) {
  if (root == NULL) {
    return true;
  }

  bool left = true, right = true, leftCheck = true, rightCheck = true;

  left = isMinHeap(root->left);
  right = isMinHeap(root->right);

  if (root->left != NULL) {
    leftCheck = root->value <= root->left->value;
  }

  if (root->right != NULL) {
    rightCheck = root->value <= root->right->value;
  }

  if (left && right && leftCheck && rightCheck) {
    return true;
  } else {
    return false;
  }
}

int main() {
  BinaryTree<int> *tree = new BinaryTree<int>();
  tree->GenerateBinaryTree();
  TreeNode<int> *root = tree->ReturnRoot();
  cout << "Checking if Binary Tree is CBT or not: "
       << isTreeCBT(root, treeNodeCount(root)) << endl;
  cout << "Is Max Heap: " << isMaxHeap(root) << endl;
  cout << "Is Min Heap: " << isMinHeap(root) << endl;
  return 0;
}

// int main() {
//   BinaryTree<int> *tree = new BinaryTree<int>();
//   tree->GenerateBinaryTree();

//   TreeNode<int> *targetNode = NULL;
//   TreeNode<int> *root = tree->ReturnRoot();
//   map<TreeNode<int> *, TreeNode<int> *> *nodeToParent =
//       new map<TreeNode<int> *, TreeNode<int> *>();
//   pair<TreeNode<int> *, TreeNode<int> *> temp;
//   temp.first = root;
//   temp.second = NULL;
//   nodeToParent->insert(temp);
//   storeMapping(root, 47, targetNode, nodeToParent);
//   cout << endl;

//   if (targetNode != NULL) {
//     cout << "Number of Seconds to burn the Entire Tree: "
//          << burnTree(targetNode, nodeToParent) << endl;
//   } else {
//     cout << "Target do not found in the Tree!!" << endl;
//   }

//   delete nodeToParent;
//   return 0;
// }

// int main() {
//   BinaryTree<int> *tree1 = new BinaryTree<int>();
//   BinaryTree<int> *tree2 = new BinaryTree<int>();
//   cout << "First Tree: " << endl;
//   tree1->GenerateBinaryTree();
//   cout << endl;
//   fflush(stdin);
//   cout << "Second Tree: " << endl;
//   tree2->GenerateBinaryTree();
//   cout << endl;

//   cout << "Level Order Traversal of Binary Tree 1: " << endl;
//   tree1->LevelOrderTraversal();
//   cout << endl;
//   cout << "Level Order Traversal of Binary Tree 2: " << endl;
//   tree2->LevelOrderTraversal();
//   cout << endl;

//   vector<int> *inOrder1 = new vector<int>();
//   vector<int> *inOrder2 = new vector<int>();
//   BSTInOrder(tree1->ReturnRoot(), inOrder1);
//   BSTInOrder(tree2->ReturnRoot(), inOrder2);
//   vector<int> *answer = mergeTwoArrays(inOrder1, inOrder2);

//   cout << "Printing Merged In Order: " << endl;
//   print(answer);
//   cout << endl;

//   TreeNode<int> *root = NULL;
//   root = inOrderToBST(root, answer, answer->size() - 1);
//   LevelOrder(root);
//   return 0;
// }

// Different Binary Trees
// 4 1 0 1 1 1 2 2 1 3 1 4 2 1 5 1 6 2 2 1 7 2 1 8
// 4 1 14 1 8 1 6 2 2 1 11 1 9 2 1 22 1 20 2 1 21 1 25 1 23 2
// 3 1 0 1 1 1 3 2 1 2 1 5 1 6
// 4 1 0 1 1 1 3 2 2 1 4 2 1 7 1 2 1 5 1 8 2 1 6 2 2
// 4 1 50 1 45 1 35 1 30 2 1 47 2 2 1 58 1 54 2 2 1 61 2 1 67

// Different Complete Binary Trees
// 4 1 27 1 22 1 19 1 16 1 14 1 17 1 13 2 1 24 1 15 2 2 1 18 2 2
// 4 1 0 1 3 1 5 1 6 2 1 4 2 2 1 2 1 7 2 2 1 9 2 2
// 3 1 12 1 4 1 10 1 2 1 7 1 5 2