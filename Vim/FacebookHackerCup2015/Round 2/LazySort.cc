#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

bool solve(vi &nums)
{
    ll lowN = nums[0];
    ll highN = nums[0];
    ll front = 1;
    ll back = nums.size()-1;

    while (front <= back)
    {
        if (nums[front] == lowN-1)
        {
            ++front;
            --lowN;
        }
        else if (nums[front] == highN+1)
        {
            ++front;
            ++highN;
        }
        else if (nums[back] == lowN-1)
        {
            --back;
            --lowN;
        }
        else if (nums[back] == highN+1)
        {
            --back;
            ++highN;
        }
        else
            return false;
    }

    return true;
}

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll N;
        cin >> N;

        vi nums(N);

        for (ll i = 0; i < N; ++i)
            cin >> nums[i];

        bool success = solve(nums);
        if (!success)
        {
            vi numsR(nums.rbegin(), nums.rend());
            success = solve(numsR);
        }

        printf("Case #%lld: %s\n", caseNum, success ? "yes" : "no");
    }
}
