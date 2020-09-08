#include <iostream>
using namespace std;

struct Node
{
    bool isLeaf;
    int *keys;
    Node **children;
    int count;

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

    void merge(int idx, Node *node)
    {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx + 1];
        child->keys[t - 1] = node->keys[idx];

        for (int i = 0; i < sibling->count; i++)
            child->keys[i + t] = sibling->keys[i];

        if (!child->isLeaf)
        {
            for (int i = 0; i <= sibling->count; i++)
                child->children[i + t] = sibling->children[i];
        }

        for (int i = idx + 1; i < node->count; i++)
            node->keys[i - 1] = node->keys[i];

        for (int i = idx + 2; i <= node->count; i++)
            node->children[i - 1] = node->children[i];

        child->count += sibling->count + 1;
        node->count--;
        delete (sibling);
    }

public:
    BTree(int order)
    {
        root = NULL;
        t = order;
    }

    Node *getRoot() { return root; }

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

    int remove(int key, Node *node)
    {
        if (!root)
            return -1;

        int idx = 0;
        while (idx < node->count && node->keys[idx] < key)
            ++idx;

        if (idx < node->count && node->keys[idx] == key)
        {
            if (node->isLeaf)
            {
                for (int i = idx + 1; i < node->count; ++i)
                    node->keys[i - 1] = node->keys[i];
                node->count--;
            }
            else
            {
                int k = node->keys[idx];
                if (node->children[idx]->count >= t)
                {
                    Node *cur = node->children[idx];
                    while (!cur->isLeaf)
                        cur = cur->children[cur->count];
                    int pred = cur->keys[cur->count - 1];
                    node->keys[idx] = pred;
                    remove(pred, node->children[idx]);
                }
                else if (node->children[idx + 1]->count >= t)
                {
                    Node *cur = node->children[idx + 1];
                    while (!cur->isLeaf)
                        cur = cur->children[0];
                    int succ = cur->keys[0];
                    node->keys[idx] = succ;
                    remove(succ, node->children[idx + 1]);
                }
                else
                {
                    merge(idx, node);
                    remove(k, node->children[idx]);
                }
            }
        }
        else
        {
            if (node->isLeaf)
                return -1;
            bool flag = ((idx == node->count) ? true : false);
            if (node->children[idx]->count < t)
            {
                if (idx != 0 && node->children[idx - 1]->count >= t)
                {
                    Node *child = node->children[idx];
                    Node *sibling = node->children[idx - 1];

                    for (int i = child->count - 1; i >= 0; --i)
                        child->keys[i + 1] = child->keys[i];
                    if (!child->isLeaf)
                    {
                        for (int i = child->count; i >= 0; --i)
                            child->children[i + 1] = child->children[i];
                    }
                    child->keys[0] = node->keys[idx - 1];

                    if (!child->isLeaf)
                        child->children[0] = sibling->children[sibling->count];

                    node->keys[idx - 1] = sibling->keys[sibling->count - 1];
                    child->count++;
                    sibling->count--;
                }
                else if (idx != node->count && node->children[idx + 1]->count >= t)
                {
                    Node *child = node->children[idx];
                    Node *sibling = node->children[idx + 1];
                    child->keys[(child->count)] = node->keys[idx];
                    if (!(child->isLeaf))
                        child->children[(child->count) + 1] = sibling->children[0];

                    node->keys[idx] = sibling->keys[0];
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
                else if (idx != node->count)
                    merge(idx, node);
                else
                    merge(idx - 1, node);
            }

            if (flag && idx > node->count)
                remove(key, node->children[idx - 1]);
            else
                remove(key, node->children[idx]);
        }
        if (root->count == 0)
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

    void inorder(Node *node)
    {
        if (node != NULL)
        {
            int i;
            cout << "(";
            for (i = 0; i < node->count; i++)
            {
                if (!node->isLeaf)
                    inorder(node->children[i]);
                cout << node->keys[i] << " ";
            }
            if (!node->isLeaf)
                inorder(node->children[i]);
            cout << ") ";
        }
    }

    void preorder(Node *node)
    {
        if (node != NULL)
        {
            int i;
            cout << "(";
            for (i = 0; i < node->count; i++)
            {
                cout << node->keys[i] << " ";
                if (!node->isLeaf)
                    preorder(node->children[i]);
            }
            if (!node->isLeaf)
                preorder(node->children[i]);
            cout << ") ";
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
    tree.insert(1, tree.getRoot());
    tree.insert(3, tree.getRoot());
    tree.insert(7, tree.getRoot());
    tree.insert(10, tree.getRoot());
    tree.insert(11, tree.getRoot());
    tree.insert(13, tree.getRoot());
    tree.insert(14, tree.getRoot());
    tree.insert(15, tree.getRoot());
    tree.insert(18, tree.getRoot());
    tree.insert(16, tree.getRoot());
    tree.insert(19, tree.getRoot());
    tree.insert(24, tree.getRoot());
    tree.insert(25, tree.getRoot());
    tree.insert(26, tree.getRoot());
    tree.insert(21, tree.getRoot());
    tree.insert(4, tree.getRoot());
    tree.insert(5, tree.getRoot());
    tree.insert(20, tree.getRoot());
    tree.insert(22, tree.getRoot());
    tree.insert(2, tree.getRoot());
    // tree.insert(17, tree.getRoot());
    // tree.insert(12, tree.getRoot());
    // tree.insert(6, tree.getRoot());
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
            // tree.remove(6, tree.getRoot());
            // tree.remove(13, tree.getRoot());
            // tree.remove(7, tree.getRoot());
            // tree.remove(4, tree.getRoot());
            // tree.remove(2, tree.getRoot());
            // tree.remove(16, tree.getRoot());
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