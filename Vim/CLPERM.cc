#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
typedef vector<LL> vi;

int main()
{
    size_t T;
    scanf("%lu", &T);

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        LL N;
        size_t K;
        scanf("%lld %lu", &N, &K);

        vi nums(K);
        for (size_t i = 0; i < K; ++i)
            scanf("%lld", &nums[i]);

        sort(nums.begin(), nums.end());

        LL sum = 0;
        LL last = -1;
        for (size_t i = 0; i < K; ++i)
        {
            LL total = nums[i] * (nums[i]-1) / 2;

            if (nums[i] > total - sum)
            {
                last = nums[i];
                break;
            }

            sum += nums[i];
        }

        if (last == -1)
            last = N * (N+1) / 2 - sum + 1;

        if (last % 2 == 1)
            printf("Chef\n");
        else
            printf("Mom\n");
    }
}
