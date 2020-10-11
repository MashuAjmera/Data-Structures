#include <iostream>
using namespace std;

// Struct of Node for B Tree
struct Node
{
    bool isLeaf;
    int *keys;
    Node **children;
    int count;

    // Constructor function to create a new node
    Node(int t, bool leaf)
    {
        count = 0;
        isLeaf = leaf;
        keys = new int[2 * t - 1];
        children = new Node *[2 * t];
    }
};

class BTree
{
    Node *root;
    int t;

protected:
    // Function to split a node if number of keys exceed 2t-1
    void split(int i, Node *parent, Node *node)
    {
        int j;
        Node *temp = new Node(t, node->isLeaf);
        for (j = 0; j < t - 1; j++)
        {
            temp->keys[j] = node->keys[t + j];
            if (!node->isLeaf)
                temp->children[j] = node->children[t + j];
        }
        temp->count = t - 1;
        node->count = t - 1;
        for (j = node->count; j > i; j--)
        {
            parent->keys[j] = parent->keys[j - 1];
            parent->children[j + 1] = parent->children[j];
        }
        parent->keys[i] = node->keys[t - 1];
        parent->children[i + 1] = temp;
        parent->count += 1;
    }

    // Function to split a node if number of keys gets less than t-1
    void merge(int index, Node *node)
    {
        Node *child = node->children[index];
        Node *sibling = node->children[index + 1];
        child->keys[t - 1] = node->keys[index];

        for (int i = 0; i < sibling->count; i++)
            child->keys[i + t] = sibling->keys[i];

        if (!child->isLeaf)
        {
            for (int i = 0; i <= sibling->count; i++)
                child->children[i + t] = sibling->children[i];
        }

        for (int i = index + 1; i < node->count; i++)
            node->keys[i - 1] = node->keys[i];

        for (int i = index + 2; i <= node->count; i++)
            node->children[i - 1] = node->children[i];

        child->count += sibling->count + 1;
        node->count--;
        delete (sibling);
    }

public:
    // Constructor function to create a B-Tree of order t
    BTree(int order)
    {
        root = NULL;
        t = order;
    }

    // function to get root pointer
    Node *getRoot() { return root; }

    // Function to find a key
    Node *search(int key, Node *node)
    {
        int i;
        for (i = 0; i < node->count && key < node->keys[i]; i++)
            ;
        if (key == node->keys[i])
            return node;
        else if (!node->isLeaf)
            return search(key, node->children[i]);
        else
            return NULL;
    }

    // Function to insert a new key in the tree
    void insert(int key, Node *node)
    {
        if (root == NULL)
        {
            root = new Node(t, true);
            root->count = 1;
            root->keys[0] = key;
        }
        else if (node == root && root->count == 2 * t - 1)
        {
            Node *temp = new Node(t, false);
            temp->children[0] = root;
            split(0, temp, root);
            if (temp->keys[0] < key)
                insert(key, temp->children[1]);
            else
                insert(key, temp->children[0]);
            root = temp;
        }
        else if (node->isLeaf)
        {
            int i;
            for (i = node->count - 1; i >= 0 && node->keys[i] > key; i--)
                node->keys[i + 1] = node->keys[i];
            node->count += 1;
            node->keys[i + 1] = key;
        }
        else
        {
            int i;
            for (i = node->count - 1; i >= 0 && node->keys[i] > key; i--)
                ;
            if (node->children[i + 1]->count == 2 * t - 1)
            {
                split(i + 1, node, node->children[i + 1]);
                if (node->keys[i + 1] < key)
                    i++;
            }
            insert(key, node->children[i + 1]);
        }
    }

    // Function to delete a key from the tree
    int remove(int key, Node *node)
    {
        if (!root)
            return -1;

        int index = 0;
        while (index < node->count && node->keys[index] < key)
            ++index;
        // if node contains the key
        if (index < node->count && node->keys[index] == key)
        {
            if (node->isLeaf) // if node containing the key is a leaf node
            {
                for (int i = index + 1; i < node->count; ++i)
                    node->keys[i - 1] = node->keys[i];
                node->count--;
            }
            else // if node containing the key is not a leaf node
            {
                int k = node->keys[index];
                if (node->children[index]->count >= t) // if left child of key has more than minimum number of keys
                {
                    Node *temp = node->children[index];
                    while (!temp->isLeaf)
                        temp = temp->children[temp->count];
                    int pred = temp->keys[temp->count - 1];
                    node->keys[index] = pred;
                    remove(pred, node->children[index]);
                }
                else if (node->children[index + 1]->count >= t) // if right child of key has more than minimum nuber of keys
                {
                    Node *temp = node->children[index + 1];
                    while (!temp->isLeaf)
                        temp = temp->children[0];
                    int succ = temp->keys[0];
                    node->keys[index] = succ;
                    remove(succ, node->children[index + 1]);
                }
                else // if both children of key donot have more than minimum number of keys, we merge the key with the children
                {
                    merge(index, node);
                    remove(k, node->children[index]);
                }
            }
        }
        else // if node doesn't contain the tree
        {
            if (node->isLeaf)
                return -1;
            bool flag = ((index == node->count) ? true : false);
            if (node->children[index]->count < t)
            {
                if (index != 0 && node->children[index - 1]->count >= t)
                {
                    Node *child = node->children[index];
                    Node *sibling = node->children[index - 1];

                    for (int i = child->count - 1; i >= 0; --i)
                        child->keys[i + 1] = child->keys[i];
                    if (!child->isLeaf)
                    {
                        for (int i = child->count; i >= 0; --i)
                            child->children[i + 1] = child->children[i];
                    }
                    child->keys[0] = node->keys[index - 1];

                    if (!child->isLeaf)
                        child->children[0] = sibling->children[sibling->count];

                    node->keys[index - 1] = sibling->keys[sibling->count - 1];
                    child->count++;
                    sibling->count--;
                }
                else if (index != node->count && node->children[index + 1]->count >= t)
                {
                    Node *child = node->children[index];
                    Node *sibling = node->children[index + 1];
                    child->keys[(child->count)] = node->keys[index];
                    if (!(child->isLeaf))
                        child->children[(child->count) + 1] = sibling->children[0];

                    node->keys[index] = sibling->keys[0];
                    for (int i = 1; i < sibling->count; ++i)
                        sibling->keys[i - 1] = sibling->keys[i];
                    if (!sibling->isLeaf)
                    {
                        for (int i = 1; i <= sibling->count; ++i)
                            sibling->children[i - 1] = sibling->children[i];
                    }
                    child->count += 1;
                    sibling->count -= 1;
                }
                else if (index != node->count) // if index is not the rightmost key
                    merge(index, node);
                else // if index is the rightmost key
                    merge(index - 1, node);
            }

            if (flag && index > node->count)
                remove(key, node->children[index - 1]);
            else
                remove(key, node->children[index]);
        }
        if (root->count == 0) // if after deletion root becomes empty
        {
            Node *temp = root;
            if (root->isLeaf)
                root = NULL;
            else
                root = root->children[0];
            delete temp;
        }
        return 1;
    }

    // Function to traverse the tree- inorder
    void inorder(Node *node)
    {
        if (node != NULL)
        {
            int i;
            cout << " (";
            for (i = 0; i < node->count; i++)
            {
                if (!node->isLeaf)
                    inorder(node->children[i]);
                cout << " " << node->keys[i];
            }
            if (!node->isLeaf)
                inorder(node->children[i]);
            cout << " )";
        }
    }

    // Function to traverse the tree- preorder
    void preorder(Node *node)
    {
        if (node != NULL)
        {
            int i;
            cout << " (";
            for (i = 0; i < node->count; i++)
            {
                cout << " " << node->keys[i];
                if (!node->isLeaf)
                    preorder(node->children[i]);
            }
            if (!node->isLeaf)
                preorder(node->children[i]);
            cout << " )";
        }
    }
};

// Main Function to take user input and display results
int main()
{
    int i, n;
    cout << "Enter the order of the BTree: ";
    cin >> n;
    BTree tree(n);
    cout << "A BTree has been created.\nYou can do the following operations next-\n1. Insert a new node\n2. Search a node\n3. Delete aa node\n4. Traverse the tree (Inorder)\n5. Traverse the tree (Preorder)\n6. Delete the tree and exit";
    while (1)
    {
        cout << "\nEnter your choice: ";
        cin >> i;
        switch (i)
        {
        case 1:
            cout << "Enter the number to insert: ";
            cin >> n;
            tree.insert(n, tree.getRoot());
            cout << n << " inserted successfully.";
            break;
        case 2:
            cout << "Enter the number to search: ";
            cin >> n;
            if (tree.search(n, tree.getRoot()))
                cout << "Node found.";
            else
                cout << "Node not found.";
            break;
        case 3:
            cout << "Enter the number to delete: ";
            cin >> n;
            n = tree.remove(n, tree.getRoot());
            if (n == 1)
                cout << "Node deleted.";
            else
                cout << "Node not found.";
            break;
        case 4:
            cout << "Inorder traversal of the tree is: ";
            tree.inorder(tree.getRoot());
            break;
        case 5:
            cout << "Preorder traversal of the tree is: ";
            tree.preorder(tree.getRoot());
            break;
        case 6:
            cout << "Program successfully exited. Thank You.";
            return 0;
        default:
            cout << "Please enter the right number to continue.";
        }
    }
}