#include <iostream>
#include <utility> // utility header file for pair data structure
using namespace std;

class Cell
{
    int m, prime, a[8], n;  // m is the size of the hash function
    pair<int, bool> *table; // int reresents the key value, bool is the delete flag

protected:
    int hash(int k) // this is the hash function
    {
        int h, key;
        for (int i = 0; i < 8; i++)
        {
            key = k % 2;
            h = a[i] * key;
            k = k / 2;
        }
        return h % m;
    }

    void resize()
    {
        pair<int, bool> temp[m];
        for (int i = 0; i < m; i++)
            temp[i] = table[i];
        m = n * n;
        n = 0;
        for (int i = 0; i < 8; i++)
            a[i] = rand() % 2;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
        for (int i = 0; i < sizeof(temp) / sizeof(temp[0]); i++)
            insert(temp[i].first);
        delete (temp);
    }

public:
    Cell() // contructor of the hashmap, takes size of table as input
    {
        m = 1;
        for (int i = 0; i < 8; i++)
            a[i] = rand() % 2;
        n = 1;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
    }

    int search(int k) // function to search a kay value in the table
    {
        for (int i = 0; i < m; i++)
        {
            int pos = hash(k) + i;
            if (table[pos].first == k)
                return pos; // returns the position of the key value where it is found
            else if (table[pos].first == 0 && table[pos].second == false)
                return -1; // returns -1 when not found
        }
        return -1;
    }

    bool insert(int k) // function to insert a key value in the table
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
                return false; // returns false when the key is already present
        }
        if (m < n * n)
            resize();
        return true; // returns true after insertion
    }

    bool remove(int k) // function to delete a key value from the table
    {
        int pos = search(k);
        if (pos != -1)
        {
            table[pos].first = 0;
            table[pos].second = true;
            n--;
            if (m > n * n)
                resize();
            return true; // returns false when the key is found and deleted
        }
        return false; // returns false when the key is not present
    }

    void traverse() // function to print all the values of the table (for ease of use only)
    {
        for (int i = 0; i < m; i++)
            cout << i << "-> " << table[i].first << " | ";
    }
};

class Perfect
{
    int m;        // m is the size of the hash function
    Cell **table; // int reresents the key value, bool is the delete flag

protected:
    int hash(int k) { return k % m; } // this is the hash function

public:
    Perfect(int size) // contructor of the hashmap, takes size of table as input
    {
        m = size;
        table = (Cell **)calloc(m, sizeof(Cell)); // creates a table of size m
    }

    int search(int k) // function to search a kay value in the table
    {
        int pos = hash(k);
        if (table[pos])
            return table[pos]->search(k); // returns the position of the key value where it is found
        else
            return -1; // returns -1 when not found
    }

    bool insert(int k) // function to insert a key value in the table
    {
        int pos = hash(k);
        if (!table[pos])
            table[pos] = new Cell();
        return table[pos]->insert(k); // calls the return of the cell where to hash and returns the value returned
    };

    bool remove(int k)
    {
        int pos = hash(k);
        if (table[pos])
            return table[pos]->remove(k);
        return false; // calls the return of the cell where to delete and returns the value returned
    }

    void traverse() // function to print all the values of the table (for ease of use only)
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