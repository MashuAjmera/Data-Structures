#include <iostream>
#include <string>
using namespace std;

int *compute_prefix(string P) // function to compute pie values of each P[j]
{
    int m = P.length(), i, j, k;
    int *pie = (int *)calloc(m, sizeof(int));

    for (j = 0; j < m; j++) // finding pie[j]
    {
        // j=2, k=0,i=0
        for (k = j - 1; k >= -1; k--) // checking if P[k] is a suffix of P[j]
        {
            for (i = k; i >= 0; i--) // checking the ith character of P[k]
            {
                if (P[i] != P[j - k + i]) // if they are not equal, it means P[k] is not a suffix of P[j]
                    break;
            }
            if (i == -1) // if they are equal, it means P[k] is a suffix of P[j]
                break;
        }
        pie[j] = k + 1;
    }
    return pie;
}

void KMP(string T, string P) // KMP function to check pattern matching
{
    int n = T.length(), m = P.length(), q = 0;
    int *pie = compute_prefix(P); // storing the pie values returned by the function

    for (int i = 0; i < n; i++)
    {
        while (q > 0 && P[q] != T[i]) // if some character matched and there is a mismatch
            q = pie[q - 1];
        if (P[q] == T[i]) // if the character matches, we look for the next character
            q = q + 1;
        if (q == m) //if all characters matched, we print the value and proceed to look for other matches
        {
            cout << " " << i - m + 1;
            q = pie[q - 1];
        }
    }
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
        cout << "Pattern occurs at:";
        KMP(T, P);
        cout << "\nEnter 0 to exit, 1 to continue: ";
        cin >> i;
    } while (i);
    cout << "Program successfully exited. Thank You.";
    return 1;
}