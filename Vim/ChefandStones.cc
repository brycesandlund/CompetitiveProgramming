#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<size_t> VI;

int main()
{
    size_t T;

    cin >> T;
    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N, K;
    
        cin >> N >> K;

        VI A(N), B(N);

        for (size_t i = 0; i < N; ++i)
        {
            cin >> A[i];
        }

        size_t maxProfit = 0;
        for (size_t i = 0; i < N; ++i)
        {
            cin >> B[i];

            size_t cur = K / A[i] * B[i];
            maxProfit = max(maxProfit, cur);
        }

        cout << maxProfit << endl;
    }
}
