#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;
typedef vector<LL> vn;


int main()
{
    LL T;
    cin >> T;

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        LL GP, GC, GF;
        cin >> GP >> GC >> GF;

        LL N;
        cin >> N;

        vn P(N), C(N), F(N);

        for (size_t i = 0; i < N; ++i)
        {
            cin >> P[i] >> C[i] >> F[i];
        }

        bool success = false;
        for (LL mask = 0; mask <= (1 << N); ++mask)
        {
            LL curP = 0, curC = 0, curF = 0;

            LL maskCopy = mask;
            for (size_t i = 0; maskCopy != 0; maskCopy >>= 1, ++i)
            {
                if (maskCopy % 2 == 1)
                {
                    curP += P[i];
                    curC += C[i];
                    curF += F[i];
                }
            }

            if (curP == GP && curC == GC && curF == GF)
            {
                success = true;
                break;
            }
        }

        printf("Case #%lu: %s\n", caseNum, success ? "yes" : "no");
    }
}
