#include <iostream>
using namespace std;

// Struct of Node for 2-3 Tree
struct Node
{
    Node *child1, *child2, *child3, *child4;
    Node *parent;
    int data[3];
    int count;

    // Function to create a new node
    Node(int key)
    {
        child1 = NULL;
        child2 = NULL;
        child3 = NULL;
        child4 = NULL;
        parent = NULL;
        count = 1;
        data[0] = key;
    }
};

bool isLeaf(Node *root) { return root->child1 == NULL ? true : false; }

void inorder(Node *root)
{
    if (root == NULL)
        return;

    inorder(root->child1);
    if (root->count == 1)
        cout << root->data[0] << " ";
    else
        cout << "(" << root->data[0] << " " << root->data[1] << ") ";
    inorder(root->child3);
}

void preorder(Node *root)
{
    if (root == NULL)
        return;

    if (root->count == 1)
        cout << root->data[0] << " ";
    else
        cout << "(" << root->data[0] << " " << root->data[1] << ") ";
    preorder(root->child1);
    preorder(root->child3);
}

Node *searchNode(Node *root, int key)
{
    if ((root->count == 1 && key == root->data[0]) || (root->count == 2 && (key == root->data[0] || key == root->data[1])))
    {
        cout << "Key already present in the tree" << endl;
        return NULL;
    }

    if (isLeaf(root) == true)
        return root;

    if (key < root->data[0])
        return searchNode(root->child1, key);
    else if (key > root->data[0] && key < root->data[1])
        return searchNode(root->child2, key);
    else
        return searchNode(root->child3, key);
}

void insertNode(Node *root, int key)
{
    if (root->count == 1)
    {
        if (key < root->data[0])
        {
            root->data[1] = root->data[0];
            root->data[0] = key;
        }
        else
            root->data[1] = key;

        root->count = 2;
    }
    else
    {
        if (key < root->data[0])
        {
            root->data[2] = root->data[1];
            root->data[1] = root->data[0];
            root->data[0] = key;
        }
        else if (key > root->data[0] && key < root->data[1])
        {
            root->data[2] = root->data[1];
            root->data[1] = key;
        }
        else
            root->data[2] = key;

        root->count = 3;
    }
}

void split(Node *root, Node *leaf)
{
    if (leaf == root)
    {
        Node *left = new Node(root->data[0]);
        Node *right = new Node(root->data[2]);
        left->child1 = root->child1;
        left->child3 = root->child2;
        right->child1 = root->child3;
        right->child3 = root->child4;
        root->child1 = left;
        root->child2 = NULL;
        root->child3 = right;
        root->child4 = NULL;
        left->parent = root;
        right->parent = root;
        root->data[0] = root->data[1];
        root->count = 1;
        if (isLeaf(left) == false)
        {
            left->child1->parent = left;
            left->child3->parent = left;
            right->child1->parent = right;
            right->child3->parent = right;
        }
        return;
    }
    else
    {
        Node *parent = leaf->parent;
        insertNode(parent, leaf->data[1]);

        if (parent->count == 3)
        {
            Node *left = new Node(leaf->data[0]);
            Node *right = new Node(leaf->data[2]);
            if (leaf == parent->child1)
            {
                parent->child4 = parent->child3;
                parent->child3 = parent->child2;
                parent->child2 = right;
                parent->child1 = left;
            }
            else if (leaf == parent->child2)
            {
                parent->child4 = parent->child3;
                parent->child3 = right;
                parent->child2 = left;
            }
            else
            {
                parent->child4 = right;
                parent->child3 = left;
            }

            left->child1 = leaf->child1;
            left->child3 = leaf->child2;
            right->child1 = leaf->child3;
            right->child3 = leaf->child4;

            if (isLeaf(left) == false)
            {
                left->child1->parent = left;
                left->child3->parent = left;
                right->child1->parent = right;
                right->child3->parent = right;
            }

            split(root, parent);
            delete leaf;
        }
        else
        {
            if (leaf == parent->child1)
            {
                if (parent->child2 != NULL)
                    parent->child3 = parent->child2;

                leaf->count = 1;
                parent->child2 = new Node(leaf->data[2]);
                parent->child2->parent = parent;
            }
            else
            {
                if (parent->child2 != NULL)
                    parent->child1 = parent->child2;

                leaf->count = 1;
                parent->child2 = new Node(leaf->data[0]);
                leaf->data[0] = leaf->data[2];
                parent->child2->parent = parent;
            }
        }
    }
}

void insert(Node *&root, int key)
{
    if (root == NULL)
    {
        root = new Node(key);
        return;
    }

    Node *leaf = searchNode(root, key);

    if (leaf == NULL)
        return;
    insertNode(leaf, key);
    if (leaf->count == 3)
        split(root, leaf);
}

Node *search(Node *root, int key)
{
    if (root == NULL)
    {
        cout << "Key not found." << endl;
        return NULL;
    }

    if (key < root->data[0])
        return search(root->child1, key);
    else if (key == root->data[0])
        return root;
    else if (root->count == 2)
    {
        if (key < root->data[1])
            return search(root->child2, key);
        else if (key == root->data[1])
            return root;
        else
            return search(root->child3, key);
    }
    else
        return search(root->child3, key);
}

Node *inorderSuccessor(Node *inorderSuccessor)
{
    while (inorderSuccessor->child1 != NULL)
        inorderSuccessor = inorderSuccessor->child1;
    return inorderSuccessor;
}

void rearrange(Node *&root, Node *temp)
{
    if (temp == root)
    {
        root = temp->child1;
        delete temp;
        return;
    }

    Node *sibling;
    if (temp == temp->parent->child1)
    {
        if (temp->parent->child2 != NULL)
            sibling = temp->parent->child2;
        sibling = temp->parent->child3;
    }
    else if (temp == temp->parent->child2)
        sibling = temp->parent->child1;
    else
    {
        if (temp->parent->child2 != NULL)
            sibling = temp->parent->child2;
        sibling = temp->parent->child1;
    }
    Node *parent = temp->parent;

    if (parent->count == 2)
    {
        if (sibling->count == 1)
        {
            if (temp == parent->child1)
            {
                temp->data[0] = parent->data[0];
                temp->data[1] = sibling->data[0];
                parent->data[0] = parent->data[1];
                temp->child2 = sibling->child1;
                temp->child3 = sibling->child2;
                delete sibling;
            }
            else if (temp == parent->child2)
            {
                sibling->data[1] = parent->data[0];
                parent->data[0] = parent->data[1];
                sibling->child3 = temp->child1;
                delete temp;
            }
            else
            {
                temp->data[0] = sibling->data[0];
                temp->data[1] = parent->data[1];
                temp->child3 = temp->child1;
                temp->child1 = sibling->child1;
                temp->child2 = sibling->child2;
                delete sibling;
            }

            parent->count = 1;
            parent->child2 = NULL;
        }
        else
        {
            if (temp == parent->child1)
            {
                temp->data[0] = parent->data[0];
                parent->data[0] = sibling->data[0];
                sibling->data[0] = sibling->data[1];
                temp->child3 = sibling->child1;
                sibling->child1 = sibling->child2;
            }
            else if (temp == parent->child2)
            {
                temp->data[0] = parent->data[0];
                parent->data[0] = sibling->data[1];
                temp->child3 = temp->child1;
                temp->child1 = sibling->child3;
                sibling->child3 = sibling->child2;
            }
            else
            {
                temp->data[0] = parent->data[1];
                parent->data[1] = sibling->data[1];
                temp->child3 = temp->child1;
                temp->child1 = sibling->child3;
                sibling->child3 = sibling->child2;
            }
            sibling->child2 = NULL;
            sibling->count = 1;
        }
    }
    else
    {
        if (sibling->count == 2)
        {
            if (temp == parent->child3)
            {
                temp->data[0] = parent->data[0];
                parent->data[0] = sibling->data[1];
                temp->child3 = temp->child1;
                temp->child1 = sibling->child3;
                sibling->child3 = sibling->child2;
                if (isLeaf(temp) == false)
                    temp->child1->parent = temp;
            }
            else
            {
                temp->data[0] = parent->data[0];
                parent->data[0] = sibling->data[0];
                sibling->data[0] = sibling->data[1];
                temp->child3 = sibling->child1;
                sibling->child1 = sibling->child2;
                if (isLeaf(temp) == false)
                {
                    temp->child3->parent = temp;
                }
            }
            sibling->child2 = NULL;
            sibling->count = 1;
        }
        else
        {
            preorder(parent);
            if (temp == parent->child3)
            {
                sibling->data[1] = parent->data[0];
                sibling->child2 = sibling->child3;
                sibling->child3 = temp->child1;
                if (isLeaf(sibling) == false)
                    sibling->child3->parent = sibling;
                sibling->count = 2;
                delete temp;
            }
            else
            {
                temp->data[0] = parent->data[0];
                temp->data[1] = sibling->data[0];
                temp->child2 = sibling->child1;
                temp->child3 = sibling->child3;
                if (isLeaf(sibling) == false)
                    temp->child3->parent = temp;
                temp->count = 2;
                delete sibling;
            }
            parent->child3 = NULL;
            rearrange(root, parent);
        }
    }
}

void removeNode(Node *&root, Node *node, int key)
{
    if (isLeaf(node) == false)
    {
        Node *inorderSuccessor;
        if (key == node->data[0])
        {
            if (node->child2 != NULL)
                inorderSuccessor = inorderSuccessor(node->child2);
            else
                inorderSuccessor = inorderSuccessor(node->child3);
            swap(node->data[0], inorderSuccessor->data[0]);
        }
        else
        {
            inorderSuccessor = inorderSuccessor(node->child3);
            swap(node->data[1], inorderSuccessor->data[0]);
        }
        removeNode(root, inorderSuccessor, key);
    }
    else
    {
        if (node->count == 2)
        {
            if (key == node->data[0])
                node->data[0] = node->data[1];
            node->count = 1;
        }
        else
            rearrange(root, node);
    }
}

void remove(Node *&root, int key)
{
    Node *node = search(root, key);
    if (node != NULL)
        removeNode(root, node, key);
}

int main()
{
    Node *root = NULL;
    int i = 0, n;
    cout << "A 2-3 Tree has been created.\nYou can do the following operations next-\n1. Insert a new node\n2. Search a node\n3. Delete aa node\n4. Traverse the tree (Inorder)\n5. Traverse the tree (Preorder)\n6. Delete the tree and exit";
    while (1)
    {
        cout << "\nEnter your choice: ";
        cin >> i;
        switch (i)
        {
        case 1:
            cout << "Enter the number to insert: ";
            cin >> n;
            insert(root, n);
            cout << n << " inserted successfully.";
            break;
        case 2:
            cout << "Enter the number to search: ";
            cin >> n;
            if (search(root, n))
                cout << "Node found.";
            else
                cout << "Node not found.";
            break;
        case 3:
            cout << "Enter the number to delete: ";
            cin >> n;
            remove(root, n);
            cout << "Node deleted.";
            break;
        case 4:
            cout << "Inorder traversal of the tree is: ";
            inorder(root);
            break;
        case 5:
            cout << "Preorder traversal of the tree is: ";
            preorder(root);
            break;
        case 6:
            cout << "Program successfully exited. Thank You.";
            return 0;
        default:
            cout << "Please enter the right number to continue.";
        }
    }
}