#include <iostream>
#include <utility>
using namespace std;

class Cell
{
    int m, prime, a, n;
    pair<int, bool> *table;

protected:
    int hash(int k) { return a * k % m; }

    void resize()
    {
        pair<int, bool> temp[m];
        for (int i = 0; i < m; i++)
        {
            temp[i] = table[i];
        }
        m = n * n;
        n = 0;
        a = rand() % prime;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
        for (int i = 0; i < sizeof(temp) / sizeof(temp[0]); i++)
        {
            insert(temp[i].first);
        }
        delete (temp);
    }

public:
    Cell(int p)
    {
        m = 1;
        prime = p;
        a = rand() % prime;
        n = 1;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
    }

    int search(int k)
    {
        for (int i = 0; i < m; i++)
        {
            int pos = hash(k) + i;
            if (table[pos].first == k)
                return pos;
            else if (table[pos].first == 0 && table[pos].second == false)
                return -1;
        }
        return -1;
    }

    bool insert(int k)
    {
        for (int i = 0; i < m; i++)
        {
            int pos = hash(k) + i;
            if (table[pos].first == 0)
            {
                table[pos].first = k;
                table[pos].second = false;
                n++;
                break;
            }
            else if (table[pos].first == k)
                return false;
        }
        if (m < n * n)
            resize();
        return true;
    }

    bool remove(int k)
    {
        int pos = search(k);
        if (pos != -1)
        {
            table[pos].first = 0;
            table[pos].second = false;
            n--;
            if (m > n * n)
                resize();
            return true;
        }
        return false;
    }

    void traverse()
    {
        for (int i = 0; i < m; i++)
            cout << i << "-> " << table[i].first << " | ";
    }
};

class Perfect
{
    int m;
    Cell **table;

protected:
    int hash(int k) { return k % m; }

public:
    Perfect(int size)
    {
        m = size;
        table = (Cell **)calloc(m, sizeof(Cell));
    }

    int search(int k)
    {
        int pos = hash(k);
        if (table[pos])
            return table[pos]->search(k);
        else
            return -1;
    }

    bool insert(int k)
    {
        int pos = hash(k);
        if (!table[pos])
            table[pos] = new Cell(7);
        return table[pos]->insert(k);
    };

    bool remove(int k)
    {
        int pos = hash(k);
        if (table[pos])
            return table[pos]->remove(k);
        return false;
    }

    void traverse()
    {
        for (int i = 0; i < m; i++)
        {
            cout << "\nTraversal of cell " << i << ": ";
            if (table[i])
                table[i]->traverse();
        }
    }
};

// The driver function
int main()
{
    int n, i;
    cout << "Enter the size of the hash table: ";
    cin >> n;
    Perfect hashmap(n);
    cout << "A Hash Map has been created.\nYou can do the following operations next-\n1. Insert a new key\n2. Search a key\n3. Delete a key\n4. Traverse the hashmap\n5. Delete the table and exit";
    while (1)
    {
        cout << "\nEnter your choice: ";
        cin >> i;
        switch (i)
        {
        case 1:
            cout << "Enter the number to insert: ";
            cin >> n;
            hashmap.insert(n) ? cout << n << " inserted successfully." : cout << n << " already present.";
            break;
        case 2:
            cout << "Enter the number to search: ";
            cin >> n;
            hashmap.search(n) == -1 ? cout << "Key not found." : cout << "Key found.";
            break;
        case 3:
            cout << "Enter the key to delete: ";
            cin >> n;
            hashmap.remove(n) ? cout << "Key deleted." : cout << "Key not found.";
            break;
        case 4:
            cout << "The traversal of the hashmap is: ";
            hashmap.traverse();
            break;
        case 5:
            cout << "Program successfully exited. Thank You.";
            return 1;
        default:
            cout << "Please enter the right number to continue.";
        }
    }
}