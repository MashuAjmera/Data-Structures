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
    //root is made private so that functions outside cannot modify it
    Node *root;

protected:
    // function to right rotate a subtree
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

    // function to left rotate a subtree
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

    // function to interchange colors of 2 nodes
    void swapColors(Node *x, Node *y)
    {
        bool temp = x->color;
        x->color = y->color;
        y->color = temp;
    }

    // function to check if insertion led to any anomaly
    void checkInsert(Node *node)
    {
        if (node == root)
            node->color = false;
        else if (node->parent->color != false) // parent is red
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
            if (u != NULL && u->color == true) //uncle and parent are red
            {
                u->color = p->color = false;
                g->color = true; //make grandparent red
                checkInsert(g);
            }
            else // parent is red, uncle is black
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

    // funtion to fix the double black condition after deletion
    void fixDoubleBlack(Node *node)
    {
        if (node != root) // case 1
        {
            Node *s, *p = node->parent;
            if (node->parent->left == node)
                s = p->right;
            else
                s = p->left;

            if (s == NULL) // case 2
                fixDoubleBlack(p);
            else if (s->color == true) // case 3: sibling is red
            {
                p->color = true;
                s->color = false;
                if (s == p->left)
                    rightRotate(p);
                else
                    leftRotate(p);
                fixDoubleBlack(node);
            }
            else if (s->left != NULL && s->left->color == true) // sibling is black
            {
                if (s == p->left) // case 4: left left
                {
                    s->left->color = s->color;
                    s->color = p->color;
                    rightRotate(p);
                }
                else // case 5: right left
                {
                    s->left->color = p->color;
                    rightRotate(s);
                    leftRotate(p);
                }
            }
            else if (s->right != NULL && s->right->color == true) // sibling is black
            {
                if (s == p->left) // mirror of case 4: left right
                {
                    s->right->color = p->color;
                    leftRotate(s);
                    rightRotate(p);
                }
                else // case 5 mirror: right right
                {
                    s->right->color = s->color;
                    s->color = p->color;
                    leftRotate(p);
                }
            }
            else // case 6: sibling is black and both its children are black
            {
                s->color = true;
                if (p->color == false)
                    fixDoubleBlack(p);
                else
                    p->color = false;
            }
        }
    }

    // function to delete a node
    void removeNode(Node *node)
    {
        if (node->left != NULL && node->right != NULL) //both left and right child exists
        {
            Node *u = node->left; // find inorder predecessor
            while (u->right != NULL)
                u = u->right;
            node->data = u->data;
            removeNode(u);
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                if (node == root)
                    root = NULL;
                else // node is leaf
                {
                    if (node->parent->left == node)
                        node->parent->left = NULL;
                    else
                        node->parent->right = NULL;
                    if (node->color == false)
                        fixDoubleBlack(node);
                }
            }
            else
            {
                Node *u;
                if (node->left == NULL)
                    u = node->right;
                else
                    u = node->left;
                u->parent = node->parent;
                if (node != root)
                {
                    if (node->parent->left == node)
                        node->parent->left = u;
                    else
                        node->parent->right = u;
                }
                if (node->color == false && u->color == false)
                    fixDoubleBlack(u);
                else
                    u->color = false;
            }
            delete node;
        }
    }

public:
    // constructor function of a new tree
    RBT() { root = NULL; }

    // function to get root pointer
    Node *getRoot() { return root; }

    // function to search a node
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

    // function to insert a new node
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

    // function to identify which node to delete
    int remove(int n)
    {
        if (root != NULL)
        {
            Node *temp = search(n, root);
            if (temp->data == n)
            {
                removeNode(temp);
                return 1;
            }
        }
        return -1;
    }

    // function to traverse the tree inorder
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
            n = tree.insert(n);
            if (n == 1)
                cout << n << " inserted successfully.";
            else
                cout << n << " already present in tree.";
            break;
        case 2:
            cout << "Enter the number to search: ";
            cin >> n;
            if (tree.search(n, tree.getRoot()) != NULL && tree.search(n, tree.getRoot())->data == n)
                cout << "Node found.";
            else
                cout << "Node not found.";
            break;
        case 3:
            cout << "Enter the number to delete: ";
            cin >> n;
            n = tree.remove(n);
            if (n == 1)
                cout << "Node deleted.";
            else
                cout << "Node not found.";
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