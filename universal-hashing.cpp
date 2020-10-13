#include <iostream>
#include <utility> // utility header file for pair data structure
using namespace std;

class Universal
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

    void resize(int multiplier)
    {
        pair<int, bool> temp[m];
        for (int i = 0; i < m; i++)
            temp[i] = table[i];
        n = 0;
        m *= multiplier;
        for (int i = 0; i < 8; i++)
            a[i] = rand() % 2;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>));
        for (int i = 0; i < m / multiplier; i++)
            insert(temp[i].first);
        delete (temp);
    }

public:
    Universal() // contructor of the hashmap, takes size of table as input
    {
        m = 1;
        for (int i = 0; i < 8; i++)
            a[i] = rand() % 2;
        n = 0;
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
        if (n >= m)
            resize(2);
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
            if (n <= m / 4)
                resize(0.5);
            return true; // returns false when the key is found and deleted
        }
        return false; // returns false when the key is not present
    }

    void traverse() // function to print all the values of the table (for ease of use only)
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
    Universal hashmap;
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