#include "BinarySearchTree.h"

BinarySearchTree newBinarySearchTree()
{
    BinarySearchTree newBST = (BinarySearchTree)malloc(sizeof(BinarySearchTreeImp));

    newBST->root = NULL;

    return newBST;
}

void freeBinarySearchTree(BinarySearchTree tree)
{
    freeAllNodes(tree->root);

    free(tree);
}

void freeAllNodes(NodeT* root)
{
    if(root == NULL) return;

    freeAllNodes(root->left);

    freeAllNodes(root->right);

    free(root);
}

NodeT* allocateNode(Element value)
{
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));

    newNode->element = value;

    newNode->left = NULL;

    newNode->right = NULL;

    return newNode;
}

NodeT *search(NodeT* root, int searchValue)
{
    if(root == NULL || root->element.accountNumber == searchValue) return root;

    if(searchValue < root->element.accountNumber)
    {
        return search(root->left, searchValue);
    }
    else return search(root->right, searchValue);
}

int insert(BinarySearchTree tree, Element value)
{
    if(tree->root == NULL)
    {
        NodeT* newNode = allocateNode(value);
        tree->root = newNode;
        return TRUE;
    }
        else insertRec(tree->root, value);
}

void insertRec(NodeT *root, Element value)
{
    if(root->element.accountNumber == value.accountNumber) return;
    if(value.accountNumber < root->element.accountNumber)
    {
        if(root->left == NULL)
        {
            NodeT* newNode = allocateNode(value);
            root->left = newNode;
            return;
        }
        else insertRec(root->left, value);
    }
    else
    {
        if(root->right == NULL)
        {
            NodeT* newNode = allocateNode(value);
            root->right = newNode;
            return;
        }
        else
        {
            insertRec(root->right, value);
        }
    }
}

void printInOrder(NodeT* root)
{
    if(root == NULL) return;

    printInOrder(root->left);

    printf("%d, %.2lf\n", root->element.accountNumber, root->element.accountBalance);

    printInOrder(root->right);
}

void printPreOrder(NodeT* root)
{
    if(root == NULL) return;
    
    printf("%d, %.2lf\n", root->element.accountNumber, root->element.accountBalance);
    
    printPreOrder(root->left);

    printPreOrder(root->right);
}

