#include <iostream>
#include <string>
using namespace std;
#define MAX 256

int *bad_character(string P)
{
    int *last = (int *)calloc(MAX, sizeof(int));
    for (int i = 0; i < MAX; i++)
        last[i] = -1;
    for (int i = 0; i < P.length(); i++)
        last[P[i]] = i;
    return last;
}

int *compute_suffix(string P) // function to compute pie values of each P[j]
{
    int m = P.length(), i, j, k;
    int *pie = (int *)calloc(m, sizeof(int));

    for (j = 1; j <= m; j++)
    {
        for (k = j - 1; k > -1; k--)
        {
            for (i = 0; i < k; i++)
                if (P[m - k + i] != P[m - j + i])
                    break;
            if (i == k)
                break;
        }
        pie[m - j] = j - k;
    }

    return pie;
}

int BoyerMoore(string T, string P) // BooyerMoore function to check pattern matching
{
    int *last = bad_character(P);
    int *pie = compute_suffix(P); // storing the pie values returned by the function
    int m = P.length(), n = T.length();
    int i = m - 1, j = m - 1;
    int k = i;
    while (i < n)
    {
        if (P[j] == T[i])
            if (j == 0)
                return i;
            else
                i = i - 1, j = j - 1;
        else
        {
            i = max(i + m - min(j, 1 + last[T[i]]), pie[P[j]] + k);
            j = m - 1;
            k = i;
        }
    }
    return -1;
}

int main() // driver function
{
    unsigned int i;
    string T, P;
    do
    {
        cout << "Enter the term (T): ";
        cin >> T;
        cout << "Enter the pattern (P): ";
        cin >> P;
        cout << "Pattern occurs at: " << BoyerMoore(T, P);
        cout << "\nEnter 0 to exit, 1 to continue: ";
        cin >> i;
    } while (i);
    cout << "Program successfully exited. Thank You.";
    return 1;
}