#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<bool> vb;
typedef vector<vb> vvb;


int main() {
    ll n;
    cin >> n;

    vvc board(n, vc(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> ws >> board[i][j];
        }
    }

    vvb valid(2*n-1, vb(2*n-1, false));
    for (ll i = 0; i < valid.size(); ++i) {
        for (ll j = 0; j < valid[i].size(); ++j) {
            ll dr = i - (n-1);
            ll dc = j - (n-1);

            for (ll k = 0; k < n; ++k) {
                for (ll l = 0; l < n; ++l) {
                    if (board[k][l] == 'o') {
                        ll r = k+dr;
                        ll c = l+dc;

                        if (r >= 0 && r < n && c >= 0 && c < n) {
                            if (board[r][c] == '.') {
                                valid[i][j] = false;
                                goto NEXT;
                            }
                            else if (board[r][c] == 'x') {
                                valid[i][j] = true;
                            }
                        }
                    }
                }
            }
NEXT:;
        }
    }

    bool success = true;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            if (board[i][j] == 'x') {
                bool works = false;
                for (ll k = 0; k < valid.size(); ++k) {
                    for (ll l = 0; l < valid[k].size(); ++l) {
                        if (valid[k][l]) {
                            ll dr = k - (n-1);
                            ll dc = l - (n-1);

                            ll r = i-dr;
                            ll c = j-dc;

                            if (r >= 0 && r < n && c >= 0 && c < n) {
                                if (board[r][c] == 'o') {
                                    works = true;
                                }
                            }
                        }
                    }
                }
                
                if (!works) {
                    success = false;
                }
            }
        }
    }

/*
    for (ll i = 0; i < valid.size(); ++i) {
        for (ll j = 0; j < valid[i].size(); ++j) {
            if (valid[i][j]) {
                success = true;
            }
        }
    }
    */

    if (success) {
        cout << "YES" << endl;
        for (ll i = 0; i < valid.size(); ++i) {
            for (ll j = 0; j < valid[i].size(); ++j) {
                if (i == n-1 && j == n-1) {
                    cout << 'o';
                }
                else if (valid[i][j]) {
                    cout << 'x';
                }
                else {
                    cout << '.';
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
