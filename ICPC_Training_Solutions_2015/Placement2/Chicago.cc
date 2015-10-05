#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

int main() {
    ll R, C;
    for (ll cs = 1; cin >> R >> C; ++cs) {
        vvi grid(R, vi(C));
        
        for (ll i = 0; i < R; ++i) {
            for (ll j = 0; j < C; ++j) {
                char c;
                cin >> ws >> c;
                grid[i][j] = c - '0';
            }
        }

        vvvi best(10, vvi(R, vi(C, INF)));
        vvvii parent(10, vvii(R, vii(C)));
        vvi closest_not_me(R, vi(C, INF));
        for (ll n = 0; n < 10; ++n) {
            queue<ii> q;

            for (ll i = 0; i < R; ++i) {
                for (ll j = 0; j < C; ++j) {
                    if (grid[i][j] == n) {
                        q.push(ii(i, j));
                        best[n][i][j] = 0;
                        parent[n][i][j] = ii(i, j);
                    }
                }
            }
            
            while (!q.empty()) {
                ii cur = q.front();
                q.pop();
                ll r = cur.first;
                ll c = cur.second;

                for (ll i = 0; i < 4; ++i) {
                    ll new_r = r + dr[i];
                    ll new_c = c + dc[i];

                    if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C) {
                        if (best[n][new_r][new_c] != INF) {
                            if (parent[n][new_r][new_c] != parent[n][r][c]) {  //handle rule 1
                                ll p_r = parent[n][r][c].first;
                                ll p_c = parent[n][r][c].second;
                                ll o_r = parent[n][new_r][new_c].first;
                                ll o_c = parent[n][new_r][new_c].second;

                                ll d = abs(p_r - o_r) + abs(p_c - o_c);
                                closest_not_me[p_r][p_c] = min(closest_not_me[p_r][p_c], d);
                                closest_not_me[o_r][o_c] = min(closest_not_me[o_r][o_c], d);
                            }
                        }
                        else {
                            best[n][new_r][new_c] = best[n][r][c]+1;
                            parent[n][new_r][new_c] = parent[n][r][c];
                            q.push(ii(new_r, new_c));
                        }
                    }
                }
            }
        }

        ll non_gaming_effort = 0;
        for (ll n = 0; n < 10; ++n) {
            if (best[n][0][0] != INF) {
                for (ll i = 0; i < R; ++i) {
                    for (ll j = 0; j < C; ++j) {
                        if (grid[i][j] == n) {
                            if (closest_not_me[i][j] != INF) {
                                non_gaming_effort += closest_not_me[i][j]*2;
                            }
                        }
                        else {
                            non_gaming_effort += best[n][i][j]*2;
                        }
                    }
                }
            }
        }

        cout << non_gaming_effort << endl;
    }
    return 0;
}
