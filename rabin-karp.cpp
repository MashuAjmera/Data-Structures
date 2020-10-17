#include <iostream>
#include <string>
using namespace std;

void rabinKarp(string T, string P, int M, int d) // Rabin Karp function to check pattern matching
{
    int p = 0, h = 1, i, j, t = 0, m = P.length(), n = T.length();

    for (i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % M; // Calculating the hash of pattern P
        t = (d * t + T[i]) % M; // Calculating the hash of first m terms
    }

    for (i = 0; i < m - 1; i++)
        h = (h * d) % M;

    for (i = 0; i < n - m + 1; i++)
    {
        if (t == p) // if match is found in hash, we compare the terms
        {
            for (j = 0; j < m; j++)
                if (P[j] != T[i + j]) // if two terms do not match, it was a spuious hit
                    break;

            if (j == m) // if not spurious hit, we print the position
                cout << " " << i;
        }

        t = (d * (t - h * T[i]) + T[i + m]) % M; // calculating the hash t[i]

        if (t < 0)
            t = (t + M);
    }
}

int main() // driver function
{
    unsigned int M, d, i;
    string T, P;
    do
    {
        cout << "Enter the term (T): ";
        cin >> T;
        cout << "Enter the pattern (P): ";
        cin >> P;
        // cout << "Enter the modulus value (M): ";
        // cin >> M;
        // cout << "Enter the number of characters (d): ";
        // cin >> d;
        M = 101, d = 256;
        cout << "Pattern occurs at:";
        rabinKarp(T, P, M, d);
        cout << "\nEnter 0 to exit, 1 to continue: ";
        cin >> i;
    } while (i);
    cout << "Program successfully exited. Thank You.";
    return 1;
}