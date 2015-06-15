#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll R, C;
        cin >> R >> C;

        vvi grid(R, vi(C));
        for (ll i = 0; i < R; ++i) {
            for (ll j = 0; j < C; ++j) {
                char ch;
                cin >> ws >> ch;
                if (ch == '>')
                    grid[i][j] = 0;
                else if (ch == 'v')
                    grid[i][j] = 1;
                else if (ch == '<')
                    grid[i][j] = 2;
                else if (ch == '^')
                    grid[i][j] = 3;
                else
                    grid[i][j] = -1;
            }
        }

        ll ans = 0;
        bool success = true;
        for (ll i = 0; i < R; ++i) {
            for (ll j = 0; j < C; ++j) {
                if (grid[i][j] != -1) {
                    bool okay = false;
                    for (ll l = 1; l < max(R, C); ++l) {
                        ll r = i + dr[grid[i][j]]*l;
                        ll c = j + dc[grid[i][j]]*l;
                        
                        if (r < 0 || r >= R || c < 0 || c >= C) {
                            break;
                        }
                        else if (grid[r][c] != -1) {
                            okay = true;
                            break;
                        }
                    }

                    if (!okay) {
                        for (ll k = 0; k < 4; ++k) {
                            for (ll l = 1; l < max(R, C); ++l) {
                                ll r = i + dr[k]*l;
                                ll c = j + dc[k]*l;

                                if (r < 0 || r >= R || c < 0 || c >= C) {
                                    break;
                                }
                                else if (grid[r][c] != -1) {
                                    okay = true;
                                    ++ans;
                                    goto RESOLVE;
                                }
                            }
                        }
                    }

RESOLVE:
                    if (!okay) {
                        success = false;
                        goto END;
                    }
                }
            }
        }

END:
        if (success) {
            printf("Case #%lld: %lld\n", cs, ans);
        }
        else {
            printf("Case #%lld: IMPOSSIBLE\n", cs);
        }
    }
    return 0;
}
