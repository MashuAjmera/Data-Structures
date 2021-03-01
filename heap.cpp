#include <iostream>
#include <cmath>
using namespace std;

class MaxHeap
{
    int *arr;
    int size;
    int capacity;

    void heapify(int i)
    {
        int maximum = i;
        if (2 * i + 1 < size && arr[2 * i + 1] > arr[maximum])
            maximum = 2 * i + 1;
        if (2 * i + 2 < size && arr[2 * i + 2] > arr[maximum])
            maximum = 2 * i + 2;
        if (maximum != i)
        {
            swap(arr[i], arr[maximum]);
            heapify(maximum);
        }
    }

public:
    MaxHeap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        arr = new int[capacity];
    }

    MaxHeap(int capacity, int arr[])
    {
        this->capacity = capacity;
        size = capacity;
        this->arr = arr;
    }

    void insert(int k)
    {
        arr[size] = k;

        for (int i = size; i > 0; i = i / 2)
        {
            if (arr[i / 2] < arr[i])
            {
                swap(arr[i / 2], arr[i]);
            }
            else
                break;
        }
        size++;
    }

    int getMax()
    {
        return arr[0];
    }

    int extractMax()
    {
        swap(arr[0], arr[size - 1]);
        size--;
        heapify(0);

        return arr[size];
    }

    void sort()
    {
        int l = size;
        for (int i = 0; i < l; i++)
        {
            extractMax();
        }
        size = l;
        display();
    }

    void makeHeap()
    {
        for (int i = size - 1; i >= 0; i--)
        {
            heapify(i);
        }
    }

    void display()
    {
        cout << "\nThe heap is:";
        for (int i = 0; i < size; i++)
        {
            cout << " " << arr[i];
        }
    }
};

int main()
{
    MaxHeap h(11);
    h.insert(10);
    h.insert(20);
    h.insert(15);
    h.insert(30);
    h.insert(40);
    h.display();
    cout << "\nMax value is: " << h.getMax();
    h.sort();
    h.makeHeap();
    h.display();
    cout << "\nPopped out: " << h.extractMax();
    h.display();

    int arr[] = {10, 20, 15, 30, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    MaxHeap h2(n, arr);
    h2.makeHeap();
    h2.display();
    cout << "\nPopped out: " << h2.extractMax();
    h2.display();
    return 0;
}