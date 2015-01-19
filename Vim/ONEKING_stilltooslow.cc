#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<size_t, size_t> ii;
typedef vector<ii> vii;

int main()
{
    size_t T;
    scanf("%lu", &T);

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N;
        scanf("%lu", &N);

        vii intervalsL(N);
        vii intervalsR(N);

        multiset<ii> alive;

        for (size_t i = 0; i < N; ++i)
        {
            ii cur;
            scanf("%lu %lu", &cur.first, &cur.second);
            
            intervalsL[i] = cur;
            intervalsR[i].first = cur.second;
            intervalsR[i].second = cur.first;
            alive.insert(cur);
        }

        sort(intervalsL.begin(), intervalsL.end());
        sort(intervalsR.begin(), intervalsR.end());

        size_t curL = 0;
        size_t nbombs = 0;

        for (size_t i = 0; i < N; ++i)
        {
            ii flipped(intervalsR[i].second, intervalsR[i].first);
            
            if (alive.count(flipped))
            {
                ++nbombs;
                alive.erase(alive.find(flipped));
                size_t bound = intervalsR[i].first;

                for (; curL < N && intervalsL[curL].first <= bound; ++curL)
                {
                    if (alive.count(intervalsL[curL]))
                        alive.erase(alive.find(intervalsL[curL]));
                }
            }    
        }

        printf("%lu\n", nbombs);
    }
}
