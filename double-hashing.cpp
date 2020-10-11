#include <iostream>
#include <utility>
using namespace std;

class Double
{
    int m, prime;
    pair<int, bool> *table;

protected:
    int hash(int k) { return k % m; }
    int hash2(int k) { return (prime - (k % prime)) % m; }

public:
    Double(int size, int p)
    {
        m = size;
        prime = p;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
    }

    int search(int k)
    {
        for (int i = 0; i < m; i++)
        {
            int pos = (hash(k) + i * hash2(k)) % m;
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
            int pos = (hash(k) + i * hash2(k)) % m;
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
    }

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

int main()
{
    int n, i;
    cout << "Enter the size of the hash table: ";
    cin >> n;
    cout << "Enter the prime number for the hash function: ";
    cin >> i;
    Double hashmap(n, i);
    cout << "A Hash Map has been created.\nYou can do the following operations next-\n1. Insert a new key\n2. Search a key\n3. Delete a key\n4. Traverse the hashmap\n5. Delete the hashmap and exit";
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