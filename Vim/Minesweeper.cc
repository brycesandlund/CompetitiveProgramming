#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll n, m;
        cin >> n >> m;

        if (n == 0 && m == 0)
            break;
        
        if (caseNum != 1)
            cout << endl;

        vvc board(n, vc(m));

        for (ll i = 0; i < n; ++i)
            for (ll j = 0; j < m; ++j)
                cin >> board[i][j];

        vvc field(n, vc(m, '0'));

        for (ll i = 0; i < n; ++i)
        {
            for (ll j = 0; j < m; ++j)
            {
                if (board[i][j] == '*')
                {
                    field[i][j] = '*';
                }
                else
                {
                    for (ll i2 = i-1; i2 <= i+1; ++i2)
                    {
                        for (ll j2 = j-1; j2 <= j+1; ++j2)
                        {
                            if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m)
                                continue;

                            if (board[i2][j2] == '*')
                                ++field[i][j];
                        }
                    }
                }
            }
        }

        printf("Field #%lld:\n", caseNum);

        for (ll i = 0; i < n; ++i)
        {
            for (ll j = 0; j < m; ++j)
                cout << field[i][j];

            cout << endl;
        }
    }
}
