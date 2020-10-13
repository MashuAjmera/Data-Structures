#include <iostream>
#include <utility> // function to delete a key value from the table
using namespace std;

class Double
{
    int m, prime;           // m is the size of the hash function, prime is a prime number for the second hash function
    pair<int, bool> *table; // int reresents the key value, bool is the delete flag

protected:
    int hash(int k) { return k % m; }                      // this is the first hash function
    int hash2(int k) { return (prime - (k % prime)) % m; } // this is the second hash function

public:
    Double(int size, int p) // contructor of the hashmap, takes size of the table and prime number to use in the second hash function as input
    {
        m = size;
        prime = p;
        table = (pair<int, bool> *)calloc(m, sizeof(pair<int, bool>)); // creates a table of size m
    }

    int search(int k) // function to search a kay value in the table
    {
        for (int i = 0; i < m; i++)
        {
            int pos = (hash(k) + i * hash2(k)) % m;
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
            int pos = (hash(k) + i * hash2(k)) % m;
            if (!table[pos].first)
            {
                table[pos].first = k;
                table[pos].second = false;
                return true; // returns true after insertion
            }
            else if (table[pos].first == k)
                return false; // returns false when the key is already present
        }
        return false;
    }

    bool remove(int k) // function to delete a key value from the table
    {
        int pos = search(k);
        if (pos != -1)
        {
            table[pos].first = 0;
            table[pos].second = true;
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