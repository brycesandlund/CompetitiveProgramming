#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

ll n, k;

ll best(ll r, ll c, vvi &memo, vvi &board) {
    if (memo[r][c] != -1)
        return memo[r][c];
    
    ll max_dol = 0;
    for (ll i = 0; i < 4; ++i) {
        for (ll j = 1; j <= k; ++j) {
            ll new_r = r+dr[i]*j;
            ll new_c = c+dc[i]*j;

            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < n) {
                if (board[new_r][new_c] > board[r][c]) {
                    max_dol = max(max_dol, best(new_r, new_c, memo, board));
                }
            }
        }
    }
    return memo[r][c] = max_dol + board[r][c];
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        cin >> n >> k;

        vvi board(n, vi(n));
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                cin >> board[i][j];
            }
        }

        vvi memo(n, vi(n, -1));
        if (cs != 1)
            cout << endl;
        cout << best(0, 0, memo, board) << endl;
    }
    return 0;
}
