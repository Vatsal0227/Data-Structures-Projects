#include "BinarySearchTree.h"


int main()
{

    FILE* fileIn = fopen("largeInput.txt", "r");

    char buffer[1024];

    if(fileIn == NULL)
    {
        printf("ERROR: Could not open \n");
        return -1;
    }
    
    BinarySearchTree tree = newBinarySearchTree();

    while(!feof(fileIn))
    {
        char* bufcopy;
        int temp;
        Element value;

        fgets(buffer, 1024, fileIn);
        
        strcpy(bufcopy, buffer);

        char* token = strtok(bufcopy, " ");

        if(strcmp(token, "CREATE") == 0)
        {
            token = strtok(NULL, " ");

            sscanf(token, "%d", &value.accountNumber);
            value.accountBalance = 0.00;

            temp = insert(tree, value);
        }
        else if(strcmp(token, "SALE") == 0)
        {
            token = strtok(NULL, " ");
            sscanf(token, "%d", &value.accountNumber);

            token = strtok(NULL, " ");
            sscanf(token, "%lf", &value.accountBalance);

            NodeT* p = search(tree->root, value.accountNumber);
            if(p != NULL)
            {
                p->element.accountBalance += value.accountBalance;
            }

        }
        else if(strcmp(token, "PRINT") == 0)
        {
           token = strtok(NULL, " ");
           
           if(token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
           
            if(strcmp(token, "INORDER") == 0)
            {
                printInOrder(tree->root);
            }
            else if(strcmp(token, "PREORDER") == 0)
            {
                printPreOrder(tree->root);
            }

        }
    }
  
    freeBinarySearchTree(tree);
  
    return 0;
}
