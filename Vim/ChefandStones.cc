#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;
typedef vector<LL> vi;

int main()
{
    size_t T;

    cin >> T;
    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N;
        LL K;
    
        cin >> N >> K;

        vi A(N);

        for (size_t i = 0; i < N; ++i)
        {
            cin >> A[i];
        }

        LL maxProfit = 0;
        for (size_t i = 0; i < N; ++i)
        {
            LL bi;
            cin >> bi;

            LL cur = K / A[i] * bi;
            maxProfit = max(maxProfit, cur);
        }

        cout << maxProfit << endl;
    }
}
