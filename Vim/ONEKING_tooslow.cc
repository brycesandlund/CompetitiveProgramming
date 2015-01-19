#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef pair<size_t, size_t> ii;
typedef vector<ii*> vii;
typedef vector<vii> vvii;

int main()
{
    size_t T;
    scanf("%lu", &T);

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        size_t N;
        scanf("%lu", &N);

        vvii intervalsL(2010);
        vvii intervalsR(2010);

        for (size_t i = 0; i < N; ++i)
        {
            ii* cur = new ii;
            scanf("%lu %lu", &cur->first, &cur->second);
            
            intervalsL[cur->first].push_back(cur);
            intervalsR[cur->second].push_back(cur);
        }

        unordered_set<ii*> killed;
        size_t curL = 0;
        size_t nbombs = 0;

        for (size_t i = 0; i < 2010; ++i)
        {
            for (size_t j = 0; j < intervalsR[i].size(); ++j)
            {
                if (!killed.count(intervalsR[i][j]))
                {
                    ++nbombs;
                    size_t bound = intervalsR[i][j]->second;

                    for (; curL <= bound; ++curL)
                    {
                        killed.insert(intervalsL[curL].begin(), intervalsL[curL].end());
                    }
                }
            }    
        }

        printf("%lu\n", nbombs);
    }
}
