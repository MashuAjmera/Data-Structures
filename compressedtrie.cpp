#include <iostream>
#include <algorithm>
using namespace std;
#define CHAR_SIZE 256

struct Node
{
    int index, start, end;
    Node *child[CHAR_SIZE];

    Node(int index = -1, int start = -1, int end = -1) // function to create a new tree node
    {
        this->index = index;
        this->start = start;
        this->end = end;
        for (int i = 0; i < CHAR_SIZE; i++)
            child[i] = NULL;
    }
};

class CompressedTree
{
    int n;
    string *s;
    Node *root;

protected:
    void insert(int index) // function to specify new string as suffix
    {
        int i = 0;
        Node *node = root;
        int idx = s[index][i];   // converting char into ASCII
        while (node->child[idx]) // if node child with that ASCII exists
        {
            int j;
            for (j = node->child[idx]->start; j < node->child[idx]->end && s[node->child[idx]->index][j] == s[index][i]; j++, i++) // reading all the characters compressed by that node utill they match with pattern
                ;
            if (j == node->child[idx]->end) // if all characters matched in that node
            {
                node = node->child[idx]; // mark this child as node
                idx = s[index][++i];     // and look for the next node child
            }
            else // if all characters did not match in that node, the node will have to be splitted
            {
                Node *temp = node->child[idx]; // make a temporary node of that node child
                node->child[idx] = new Node(node->child[idx]->index, node->child[idx]->start, j);
                node->child[idx]->child[s[node->child[idx]->index][j]] = temp;
                temp->start = j;
                node->child[idx]->child[s[index][i]] = new Node(index, i, s[index].length());
                return;
            }
        }
        node->child[idx] = new Node(index, i, s[index].length()); // if all nodes travered and still more characters in pattern is left, create a new node thild for all the remaining patterns
    }

public:
    CompressedTree(string T) // constructor function to make a compressed tree for suffix matching
    {
        root = new Node();
        n = T.length();
        s = (string *)calloc(n, sizeof(string));
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                s[i] += T[j];
            }
        }
        sort(s, s + n); //sorting the array of suffices in lexicographic order
        for (int i = 0; i < n; i++)
            insert(i);
    }

    bool search(string P) // function to search the suffix
    {
        int i = 0;
        Node *node = root;
        int idx = P[i];          // converting char into ASCII
        while (node->child[idx]) // if node child with that ASCII exists
        {
            int j;
            // reading all the characters compressed by that node utill they match with pattern
            for (j = node->child[idx]->start; j < node->child[idx]->end && s[node->child[idx]->index][j] == P[i]; j++, i++)
                ;
            if (j == node->child[idx]->end) // if all characters matched in that node
            {
                node = node->child[idx]; // mark this child as node
                idx = P[i];              // and look for the next node child
            }
            else
                return false; // if all characters did not match in that node, it means the patter doesnt match
        }

        if (i == P.length()) // if all nodes travered and no more characters in pattern is left, the pattern exist
            return true;
        else // if all nodes travered and still more characters in pattern is left, that means it doesnt exist in the suffix tree
            return false;
    }
};

int main() // driver function
{
    string T, P;
    cout << "Enter the term (T): ";
    cin >> T;
    CompressedTree tree(T); // contruct the compressed tree for T sufix matching
    while (1)
    {
        cout << "Enter the suffix to search (P): ";
        cin >> P;
        tree.search(P) ? cout << "Suffix found.\n" : cout << "Suffix not found.\n";
    }
    return 0;
}