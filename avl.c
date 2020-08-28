// Importing Libraries
#include <stdio.h>
#include <stdlib.h>

// Data structure of Tree Node
struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

// Max Function
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to calculate height of the tree
int height(struct Node *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

// Function to calculate balance factor of node
int balanceFactor(struct Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to right rotate subtree
struct Node *rightRotate(struct Node *node)
{
    struct Node *subtree = node->left;
    struct Node *child = subtree->right;
    subtree->right = node;
    node->left = child;
    node->height = max(height(node->left), height(node->right)) + 1;
    subtree->height = max(height(subtree->left), height(subtree->right)) + 1;
    return subtree;
}

// Function to left rotate subtree
struct Node *leftRotate(struct Node *node)
{
    struct Node *subtree = node->right;
    struct Node *child = subtree->left;
    subtree->left = node;
    node->right = child;
    node->height = max(height(node->left), height(node->right)) + 1;
    subtree->height = max(height(subtree->left), height(subtree->right)) + 1;
    return subtree;
}

// Function to balance the tree
struct Node *balance(struct Node *node)
{
    int balance = balanceFactor(node);
    if (balance > 1) // _L Case
    {
        if (balanceFactor(node->left) < 0) // RL Case
            node->left = leftRotate(node->left);
        return rightRotate(node); // LL Case
    }
    else if (balance < -1) // _R Case
    {
        if (balanceFactor(node->right) > 0) //LR Case
            node->right = rightRotate(node->right);
        return leftRotate(node); //RR Case
    }
    return node;
}

// Function to create a new node
struct Node *create(int n)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = n;
    new->left = NULL;
    new->right = NULL;
    new->height = 0;
    return new;
}

// Function to insert a new node in the tree
struct Node *insert(int n, struct Node *node)
{
    if (node == NULL)
        return create(n);
    else if (n > node->data)
        node->right = insert(n, node->right);
    else if (n < node->data)
        node->left = insert(n, node->left);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    return balance(node);
}

// Function to find a node
struct Node *find(int n, struct Node *node)
{
    if (node == NULL)
        return NULL;
    else if (n > node->data)
        return find(n, node->right);
    else if (n < node->data)
        return find(n, node->left);
    else
        return node;
}

// Function to delete a node from the tree
struct Node *delete (int n, struct Node *node)
{
    if (node == NULL)
        return node;
    else if (n > node->data)
        node->right = delete (n, node->right);
    else if (n < node->data)
        node->left = delete (n, node->left);
    else
    {
        struct Node *temp;
        if (node->left == NULL) // no left node or no child
            temp = node->right;
        else if (node->right == NULL) // no right node
            temp = node->left;
        else // both children present
        {
            temp = node->left;
            // calculating maximum of left subtree
            while (temp->right != NULL)
                temp = temp->right;
            node->data = temp->data;
            node->left = delete (temp->data, node->left);
            return node;
        }
        free(node);
        return temp;
    }
    return balance(node);
}

// Function to traverse the tree- inorder
void inorder(struct Node *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to traverse the tree- preorder
void preorder(struct Node *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Main Function to take user input and display results
void main()
{
    struct Node *root;
    int n;
    printf("This is a program to work with an AVL Tree.\nEnter the first value to create an AVL Tree: ");
    scanf("%d", &n);
    root = create(n);
    printf("AVL tree created successfully with root value %d.\nThese are the following operations you can do next-\n1. Insert a new element\n2. Delete an element\n3. Traverse the tree (Inorder)\n4. Traverse the tree (Preorder)\n5. Find a node\n6. Delete the tree and exit", n);
    while (1)
    {
        printf("\nEnter your choice: ");
        int i;
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            printf("Enter the number to insert: ");
            scanf("%d", &n);
            root = insert(n, root);
            printf("%d inserted successfully.", n);
            break;
        case 2:
            printf("Enter the number to delete: ");
            scanf("%d", &n);
            root = delete (n, root);
            printf("Operation performed.", n);
            break;
        case 3:
            printf("Inorder traversal of the tree is: ");
            inorder(root);
            break;
        case 4:
            printf("Preorder traversal of the tree is: ");
            preorder(root);
            break;
        case 5:
            printf("Enter the number to find: ");
            scanf("%d", &n);
            if (find(n, root) != NULL)
                printf("Node found.");
            else
                printf("Node not found.");
            break;
        case 6:
            printf("Program successfully exited. Thank You.");
            return;
        default:
            printf("Please enter the right number to continue.");
        }
    }
}