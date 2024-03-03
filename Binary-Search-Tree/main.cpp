#include "SelfBalancedBST_AVL.cpp"
#include <iostream>
using namespace std;

void print(vector<int> *array)
{
  if (array == NULL)
  {
    return;
  }

  for (auto it = array->begin(); it != array->end(); it++)
  {
    cout << (*it) << " ";
  }

  cout << endl;
}

int GetHeight(TreeNode<int> *root)
{
  if (root == NULL)
  {
    return 0;
  }

  return root->height;
}

int GetBalance(TreeNode<int> *root)
{
  if (root == NULL)
  {
    return 0;
  }

  return (GetHeight(root->left) - GetHeight(root->right));
}

int main()
{
  AVLTree<int> *tree = new AVLTree<int>();
  tree->GenerateBinarySearchTree();
  cout << endl
       << endl;
  cout << "Is BST: " << tree->CheckTreeBST() << endl;
  cout << "In Order Traversal: ";
  tree->InOrderTraversal();
  cout << endl;
  cout << "Level Order Traversal: " << endl;
  tree->LevelOrderTraversal();

  TreeNode<int> *temp = tree->ReturnRoot();

  cout << "Binary Search Tree Height: " << tree->BinaryTreeHeight(temp) << endl;
  cout << "Balanced Tree Statistics: " << GetBalance(temp) << endl;
}

// Different Binary Trees && (BST Generation Way 1)
// 4 1 0 1 1 1 2 2 1 3 1 4 2 1 5 1 6 2 2 1 7 2 1 8
// 4 1 14 1 8 1 6 2 2 1 11 1 9 2 1 22 1 20 2 1 21 1 25 1 23 2
// 3 1 0 1 1 1 3 2 1 2 1 5 1 6
// 4 1 0 1 1 1 3 2 2 1 4 2 1 7 1 2 1 5 1 8 2 1 6 2 2
// 4 1 50 1 45 1 35 1 30 2 1 47 2 2 1 58 1 54 2 2 1 61 2 1 67

// Different UnBalanced Binary Trees && (BST Generation Way 2)
// 7