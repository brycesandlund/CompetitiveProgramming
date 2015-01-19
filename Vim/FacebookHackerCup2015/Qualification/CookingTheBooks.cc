#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

int main()
{
    LL T;
    cin >> T;

    for (size_t caseNum = 1; caseNum <= T; ++caseNum)
    {
        string num;
        cin >> num;

        LL minNum = stoll(num, NULL);
        LL maxNum = minNum;

        for (size_t i = 0; i < num.size(); ++i)
        {
            for (size_t j = i+1; j < num.size(); ++j)
            {
                swap(num[i], num[j]);

                if (num[0] != '0')
                {
                    minNum = min(minNum, stoll(num, NULL));
                    maxNum = max(maxNum, stoll(num, NULL));
                }

                swap(num[i], num[j]);
            }
        }

        printf("Case #%lu: %lld %lld\n", caseNum, minNum, maxNum);
    }
}
