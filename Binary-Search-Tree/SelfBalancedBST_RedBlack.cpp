#include "../BinaryTree/Queue_BinaryTree.cpp"
#include "../String/String.cpp"
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

enum Color
{
    RED,
    BLACK,
    DOUBLEBLACK
};

template <typename DataType>
class TreeNode
{
public:
    DataType value;
    int color;
    TreeNode<DataType> *left;
    TreeNode<DataType> *right;
    TreeNode<DataType> *parent;

    TreeNode()
    {
        this->color = RED;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }

    TreeNode(DataType value)
    {
        this->value = value;
        this->color = RED;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }

    ~TreeNode()
    {
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }
};

template <typename DataType>
class RedBlackTree
{
private:
    TreeNode<DataType> *root;

    void GetPreOrderTree(TreeNode<DataType> *root,
                         vector<TreeNode<DataType> *> *&container)
    {
        if (root == NULL)
        {
            return;
        }

        container->push_back(root);
        this->GetPreOrderTree(root->left, container);
        this->GetPreOrderTree(root->right, container);
    }

    void DeleteTree()
    {
        vector<TreeNode<DataType> *> *container =
            new vector<TreeNode<DataType> *>();
        this->GetPreOrderTree(this->root, container);

        for (int i = 0; i < container->size(); i++)
        {
            delete container->at(i);
        }

        delete container;
    }

    void RotateLeft(TreeNode<DataType> *&root)
    {
        TreeNode<DataType> *rootParent = root->parent;
        TreeNode<DataType> *rightChild = root->right;
        TreeNode<DataType> *leftChild = rightChild->left;

        rightChild->left = root;
        root->parent = rightChild;

        root->right = leftChild;
        // checking if root->right->left == NULL, then do not access parent of it
        if (leftChild != NULL)
        {
            leftChild->parent = root;
        }

        // rightChild->parent = rootParent;
        if (rootParent != NULL && rootParent->left == root)
        {
            rootParent->left = rightChild;
        }
        
        if(rootParent != NULL && rootParent->right == root)
        {
            rootParent->right = rightChild;
        }

        root = rightChild;
        root->parent = rootParent;
        // rightChild->parent = rootParent;
    }

    void RotateRight(TreeNode<DataType> *&root)
    {
        TreeNode<DataType> *rootParent = root->parent;
        TreeNode<DataType> *leftChild = root->left;
        TreeNode<DataType> *rightChild = leftChild->right;

        leftChild->right = root;
        root->parent = leftChild;

        root->left = rightChild;
        // checking if root->left->right == NULL, then do not access parent of it
        if (rightChild != NULL)
        {
            rightChild->parent = root;
        }

        // leftChild->parent = rootParent;
        if (rootParent != NULL && rootParent->left == root)
        {
            rootParent->left = leftChild;
        }
        
        if(rootParent != NULL && rootParent->right == root)
        {
            rootParent->right = leftChild;
        }

        root = leftChild;
        root->parent = rootParent;
        // leftChild->parent = rootParent;
    }

    String PerformRotation(TreeNode<DataType> *&node)
    {
        String temp;

        // Generating the cases
        if (node->parent->left == node)
        {
            temp.pushBack('L');
        }
        else
        {
            temp.pushBack('R');
        }

        if (node->parent->parent->left == node->parent)
        {
            temp.pushFront('L');
        }
        else
        {
            temp.pushFront('R');
        }

        // checking the cases and applying rotations
        if (temp == "LL")
        {
            this->RotateRight(node->parent->parent);
        }
        else if (temp == "LR")
        {
            this->RotateLeft(node->parent);
            // after the upper line the node will come at one level upper, therefore the lower line look like this
            this->RotateRight(node->parent);
        }
        else if (temp == "RR")
        {
            cout << "We are going to perform rotate left rotations" << endl;
            cout<<"node->parent->parent: "<<node->parent->parent->value<<endl;
            this->RotateLeft(node->parent->parent);
        }
        else
        {
            this->RotateRight(node->parent);
            // after the upper line the node will come at one level upper, therefore the lower line look like this
            this->RotateLeft(node->parent);
        }

        return temp;
    }

    // Red Black Tree (RBT)
    void CheckRBTProperties(TreeNode<DataType> *&root)
    {
        if (root == NULL)
        {
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            this->CheckAfterInsertion(root);
            return;
        }

        this->CheckRBTProperties(root->left);
        this->CheckRBTProperties(root->right);
    }

    void Recolor(TreeNode<DataType> *&node)
    {
        if (node->color == RED)
        {
            node->color = BLACK;
        }
        else
        {
            node->color = RED;
        }
    }

    void RecolorNodes(TreeNode<DataType> *&node, String temp)
    {
        if (temp == "LL")
        {
            this->Recolor(node->parent);
            this->Recolor(node->parent->right);
        }
        else if (temp == "LR")
        {
            this->Recolor(node->left);
            this->Recolor(node->right);
        }
        else if (temp == "RR")
        {
            this->Recolor(node->parent);
            this->Recolor(node->parent->left);
        }
        else
        {
            this->Recolor(node->left);
            this->Recolor(node->right);
        }
    }

    void CheckAfterInsertion(TreeNode<DataType> *&node)
    {
        if (node->parent->color == BLACK)
        {
            cout << "node's parent color is black" << endl;
            return;
        }

        if (node->parent->color == RED)
        {
            cout << "node's parent color is red" << endl;
            if (node->parent->parent->left == node->parent)
            {
                cout << "we inserted node at left side" << endl;
                if (node->parent->parent->right != NULL && node->parent->parent->right->color == RED)
                {
                    cout << "node->parent->parent->right != NULL" << endl;
                    node->parent->color = BLACK;
                    node->parent->parent->right->color = BLACK;

                    TreeNode<DataType> *temp = node->parent->parent;
                    cout << "we are entering in the loop" << endl;
                    cout << "before that: " << endl;
                    cout << "Tree Traversal: " << endl;
                    this->LevelOrder(this->root);
                    sleep(10);
                    if(temp != this->root){
                        this->Recolor(temp);
                        this->CheckAfterInsertion(temp);
                    }
                }
                else
                {
                    cout << "node->parent->parent->right == NULL. Perform Rotations" << endl;
                    String temp = this->PerformRotation(node);
                    this->RecolorNodes(node, temp);
                    cout << "We have performed the rotations" << endl;
                    sleep(3);
                    cout << "after rotation: traversal: " << endl;
                    this->LevelOrder(this->root);
                }
            }
            else
            {
                cout << "we inserted node at right side" << endl;
                if (node->parent->parent->left != NULL && node->parent->parent->left->color == RED)
                {
                    cout << "node->parent->parent->left != NULL" << endl;
                    node->parent->color = BLACK;
                    node->parent->parent->left->color = BLACK;

                    TreeNode<DataType> *temp = node->parent->parent;

                    if(temp != this->root){
                        this->Recolor(temp);
                        this->CheckAfterInsertion(temp);
                    }
                }
                else
                {
                    cout << "node->parent->parent->left == NULL. Perform Rotations" << endl;
                    cout << "node's value: " << node->value << endl;
                    String temp = this->PerformRotation(node);
                    this->RecolorNodes(node, temp);
                    cout << "We have performed the rotations" << endl;
                    sleep(3);
                    cout << "after rotation: traversal: " << endl;
                    this->LevelOrder(this->root);
                }
            }
        }
    }

    void Insert(TreeNode<DataType> *&root, TreeNode<DataType> *parent, DataType value)
    {
        if (root == NULL)
        {
            TreeNode<DataType> *node = new TreeNode<DataType>(value);
            root = node;
            root->parent = parent;
            cout << "Inserted " << value << endl;
            cout << "before checking: traversal: " << endl;
            this->LevelOrder(this->root);
            this->CheckAfterInsertion(root);
            cout << "after checking: " << endl;

            if (root->parent != NULL && root->parent->parent != NULL)
            {
                cout << "node's value: " << root->value << endl;
                cout << "node's parent: " << root->parent->value << ", and it's color: " << root->parent->color << endl;
                cout << "node's parent parent: " << root->parent->parent->value << ", and it's color: " << root->parent->parent->color << endl;
                sleep(10);
            }

            cout << "after checking: traversal: " << endl;
            this->LevelOrder(this->root);
            sleep(5);
            return;
        }

        if (root->value > value)
        {
            this->Insert(root->left, root, value);
        }
        else if (root->value < value)
        {
            this->Insert(root->right, root, value);
        }
        else
        {
            cout << "Duplicate values are not allowed in the Tree!!" << endl;
            return;
        }
    }

    bool Search(TreeNode<DataType> *root, DataType value)
    {
        if (root == NULL)
        {
            return false;
        }

        if (root->value == value)
        {
            return true;
        }
        else if (root->value > value)
        {
            return this->Search(root->left, value);
        }
        else
        {
            return this->Search(root->right, value);
        }
    }

    void LevelOrder(TreeNode<DataType> *root)
    {
        if (root == NULL)
        {
            return;
        }

        Queue<TreeNode<DataType> *> *container = new Queue<TreeNode<DataType> *>();
        container->push(root);
        container->push(NULL);

        TreeNode<DataType> *element = NULL;
        while (!container->empty())
        {
            element = container->front();
            container->pop();

            if (element == NULL)
            {
                cout << endl;
                if (!container->empty())
                {
                    container->push(NULL);
                }
            }
            else
            {
                cout << element->value << "(" << ((element->color == RED) ? "R" : (element->color == BLACK) ? "B"
                                                                                                            : "DB") << ")" << " ";

                if (element->left != NULL)
                {
                    container->push(element->left);
                }

                if (element->right != NULL)
                {
                    container->push(element->right);
                }
            }
        }

        delete container;
    }

public:
    RedBlackTree()
    {
        this->root = NULL;
    }

    ~RedBlackTree()
    {
        this->DeleteTree();
        this->root = NULL;
    }

    void InsertNode(DataType value)
    {
        if (this->root == NULL)
        {
            TreeNode<DataType> *node = new TreeNode<DataType>(value);
            node->color = BLACK;
            this->root = node;
            return;
        }

        this->Insert(this->root, NULL, value);
    }

    void DeleteNode(DataType value)
    {
    }

    bool SearchNode(DataType value)
    {
        return this->Search(this->root, value);
    }

    void LevelOrderTraversal() { this->LevelOrder(this->root); }
};

int main()
{
    RedBlackTree<int> tree;
    tree.InsertNode(20);
    tree.InsertNode(10);
    tree.InsertNode(30);
    tree.InsertNode(35);
    tree.InsertNode(25);
    tree.InsertNode(40);
    tree.InsertNode(5);
    tree.InsertNode(45);
    tree.InsertNode(34);

    cout << "Level Order Traversal: " << endl
         << endl;
    tree.LevelOrderTraversal();
    return 0;
}