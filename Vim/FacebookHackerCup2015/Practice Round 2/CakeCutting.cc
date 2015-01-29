#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;


int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll sections = 1;
        ll lines = 0;

        ll N;
        cin >> N;

        for (ll i = 0; i < N; ++i)
        {
            ll ai;
            cin >> ai;

            ll curLines = lines;
            for (ll j = 0; j < ai; ++j)
            {
                sections += curLines;

                if (j != 0)
                    ++curLines;
            }

            sections += curLines+1;
            lines += ai+1;
        }

        printf("Case #%lld: %lld\n", caseNum, sections);
    }
}
