#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    bool color; // black: false, red: true
    Node *right, *left, *parent;

    //Function to create a new node
    Node(int n)
    {
        this->data = n;
        this->left = this->right = this->parent = NULL;
        this->color = true;
    }
};

class RBT
{
    Node *root;

protected:
    void rightRotate(Node *node)
    {
        Node *temp = node->left;
        node->left = temp->right;
        if (node->left != NULL)
            node->left->parent = node;
        temp->parent = node->parent;
        if (node == root)
            root = temp;
        else if (node == node->parent->left)
            node->parent->left = temp;
        else
            node->parent->right = temp;
        temp->right = node;
        node->parent = temp;
    }

    void leftRotate(Node *node)
    {
        Node *temp = node->right;
        node->right = temp->left;
        if (node->right != NULL)
            node->right->parent = node;
        temp->parent = node->parent;
        if (node == root)
            root = temp;
        else if (node == node->parent->left)
            node->parent->left = temp;
        else
            node->parent->right = temp;
        temp->left = node;
        node->parent = temp;
    }

    void swapColors(Node *x, Node *y)
    {
        bool temp = x->color;
        x->color = y->color;
        y->color = temp;
    }

    void checkInsert(Node *node)
    {
        if (node == root)
            node->color = false;
        else if (node->parent->color != false)
        {
            Node *p = node->parent; // parent
            Node *g = p->parent;    // grandparent
            Node *u;                //parent's sibling
            if (p == NULL || g == NULL)
                return;
            else if (p->data > g->data)
                u = g->left;
            else
                u = g->right;
            if (u != NULL && u->color == true)
            {
                u->color = p->color = false;
                g->color = true;
                checkInsert(g);
            }
            else
            {
                if (p == g->left)
                {
                    if (node == p->left) //LL
                        swapColors(p, g);
                    else // LR
                    {
                        leftRotate(p);
                        swapColors(node, g);
                    }
                    rightRotate(g);
                }
                else
                {
                    if (node == p->right) //RR
                        swapColors(p, g);
                    else // RL
                    {
                        rightRotate(p);
                        swapColors(node, g);
                    }
                    leftRotate(g);
                }
            }
        }
    }

public:
    RBT() { root = NULL; }

    Node *getRoot() { return root; }

    Node *search(int n, Node *node)
    {
        if (node == NULL)
            return NULL;
        else if (node->data < n && node->right != NULL)
            return search(n, node->right);
        else if (node->data > n && node->left != NULL)
            return search(n, node->left);
        return node;
    }

    int insert(int n)
    {
        Node *node = new Node(n);
        if (root == NULL)
            root = node;
        else
        {
            Node *temp = search(n, root);
            if (temp->data == n)
                return -1;
            else if (temp->data > n)
                temp->left = node;
            else
                temp->right = node;
            node->parent = temp;
            checkInsert(node);
        }
        return 1;
    }

    void remove(int n)
    {
    }

    void traverse(Node *node)
    {
        if (node == NULL)
            return;
        traverse(node->left);
        cout << node->data << " ";
        traverse(node->right);
    }
};

// Main Function to take user input and display results
int main()
{
    RBT tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);
    int i, n;
    cout << "A Red Black Tree has been created.\nYou can do the following operations next-\n1. Insert a new node\n2. Search a node\n3. Delete aa node\n4. Traverse the tree (Inorder)\n5. Delete the tree and exit";
    while (1)
    {
        cout << "\nEnter your choice: ";
        cin >> i;
        switch (i)
        {
        case 1:
            cout << "Enter the number to insert: ";
            cin >> n;
            tree.insert(n);
            cout << n << " inserted successfully.";
            break;
        case 2:
            cout << "Enter the number to search: ");
            cin >> i;
            if (tree.search(n, tree.getRoot()) != NULL)
                cout << "Node found.";
            else
                cout << "Node not found.";
            break;
        case 3:
            cout << "Enter the number to delete: ";
            cin >> i;
            tree.remove(n);
            cout << "Operation performed.";
            break;
        case 4:
            cout << "Inorder traversal of the tree is: ";
            tree.traverse(tree.getRoot());
            break;
        case 5:
            cout << "Program successfully exited. Thank You.";
            return 0;
        default:
            cout << "Please enter the right number to continue.";
        }
    }
}