#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<char> vc;
typedef vector<vc> vvc;


int main() {
    ll n, m, r, c;
    for (ll cs = 1; cin >> n >> m >> r >> c && n && m && r && c; ++cs) {
        vvc board(n, vc(m));

        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                cin >> ws >> board[i][j];
            }
        }

        ll moves = 0;
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                if (board[i][j] == '1') {
                    ++moves;
                    for (ll k = i; k < i+r; ++k) {
                        for (ll l = j; l < j+c; ++l) {
                            if (k >= n || l >= m) {
                                moves = -1;
                                goto END;
                            }
                            board[k][l] = board[k][l] == '0' ? '1' : '0';
                        }
                    }
                }
            }
        }
END:
        cout << moves << endl;
    }
    return 0;
}
