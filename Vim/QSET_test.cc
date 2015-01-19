#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;

int main()
{
    LL N = 100000, M = 100000;

    cout << N << " " << M << endl;

    for (size_t i = 0; i < N; ++i)
        cout << rand()%10;

    cout << endl;

    for (size_t i = 0; i < M; ++i)
    {
        LL one = rand()%N + 1, two = rand()%N + 1;
        if (rand()%2 == 0)
        {
            cout << 1 << " " << one << " " << two << endl;
        }
        else
        {
            cout << 2 << " " << min(one, two) << " " << max(one, two) << endl;
        }
    }
}
