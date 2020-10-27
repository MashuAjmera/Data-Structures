#include <iostream>
#include <algorithm> // importing algorithm to apply sorting
using namespace std;
#define CHAR_SIZE 256 // number of general charater inputs possible from keyboard

struct Node
{
    Node *children[CHAR_SIZE];
    bool isLeaf;

    Node() // function to create a new tree node
    {
        isLeaf = false;
        for (int i = 0; i < CHAR_SIZE; i++)
            children[i] = NULL;
    }
};

class SuffixTree
{
    string *s;
    Node *root;

protected:
    void insert(string P) // function to specify new string as suffix
    {
        Node *node = root;
        for (int i = 0; i < P.length(); i++)
        {
            int index = P[i];
            if (!node->children[index])
                node->children[index] = new Node(); // the string is not present hence new node is created
            node = node->children[index];
        }
        node->isLeaf = true; // the Node traversed must be the leaf node
    }

public:
    SuffixTree(string T) // constructor function to make a suffix tree
    {
        root = new Node();
        int n = T.length();
        s = (string *)calloc(n, sizeof(string));
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                s[i] += T[j];
        sort(s, s + n); //sorting the array of suffices in lexicographic order
        for (int i = 0; i < n; i++)
            insert(s[i]);
    }

    bool search(string P) // function to search the suffix
    {
        Node *node = root;
        for (int i = 0; i < P.length(); i++)
        {
            int index = P[i];
            if (!node->children[index]) // no child in the index hence not present
                return false;
            node = node->children[index];
        }
        return (node != NULL && node->isLeaf); // if the last leaf travered is leaf then present
    }
};

int main() // driver function
{
    string T, P;
    cout << "Enter the term (T): ";
    cin >> T;
    SuffixTree tree(T); // contruct the suffix tree for T
    // while (1)
    // {
    cout << "Enter the suffix to search (P): ";
    cin >> P;
    tree.search(P) ? cout << "Suffix found.\n" : cout << "Suffix not found.\n"; // Search for different strings
    // }
    return 0;
}