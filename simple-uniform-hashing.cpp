#include <iostream>
#include <utility>
using namespace std;

class SUH
{
    int m;
    pair<int, bool> *table;

protected:
    int hash(int k) { return k % m; }

public:
    SUH(int size)
    {
        m = size;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
    }

    int search(int k)
    {
        for (int i = 0; i < m; i++)
        {
            int pos = hash(k + i);
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
            int pos = hash(k + i);
            if (!table[pos].first)
            {
                table[pos].first = k;
                table[pos].second = false;
                return true;
            }
            else if (table[pos].first == k)
                return false;
        }
        return false;
    };

    bool remove(int k)
    {
        int pos = search(k);
        if (pos != -1)
        {
            table[pos].first = 0;
            table[pos].second = false;
            return true;
        }
        else
            return false;
    }

    void traverse()
    {
        for (int i = 0; i < m; i++)
            cout << "\n"
                 << i << ": " << table[i].first;
    }
};

// The driver function
int main()
{
    int n, i;
    cout << "Enter the size of the hash table: ";
    cin >> n;
    SUH hashmap(n);
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