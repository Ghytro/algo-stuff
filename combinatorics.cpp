#include <bits/stdc++.h>

using namespace std;

unsigned long long factorial(int n)
{
    if (n < 0)
    {
        printf("Error M1: Couldn't count the factorial of a negative number.\n");
        exit(NULL);
    }
    if (n <= 1)
        return n;
    return factorial(n - 1) * n;
}

unsigned long long P(int n)
{
    return factorial(n);
}

unsigned long long rep_P(vector<int> counter)
{
    int n = 0;
    unsigned long long denominator = 1;
    for (auto x: counter)
    {
        if (x < 0)
        {
            printf("Error M2: The counter value cannot be negative.\n");
            exit(NULL);
        }

        if (x != 0)
        {
            denominator *= factorial(x);
            ++n;
        }
    }

    return factorial(n) / denominator;
}

unsigned long long C(int n, int k)
{
    if (n == k)
        return 1;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

unsigned long long A(int n, int k)
{
    if (n == k)
        return 1;
    return factorial(n) / factorial(n - k);
}

unsigned long long rep_A(int n, int k)
{
    return pow(n, k);
}

int main()
{
    return 0;
}
