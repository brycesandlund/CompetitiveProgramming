#include <iostream>

using namespace std;

int main()
{
    size_t T;
    cin >> T;

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N;
        cin >> N;

        size_t free = N;
        size_t total = 0;

        for (size_t i = 0; i < N; ++i)
        {
            size_t cur;
            cin >> cur;

            total += cur;
            if (cur == 0)
                --free;
        }

        if (total < 100 || total - free >= 100)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
}
