#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

vii get_neighbors(ll r, ll c) {
    vii neighbors(6);
    for (ll i = 0; i < 4; ++i) {
        neighbors[i] = ii(r+dr[i], c+dc[i]);
    }
    if (c % 2 == 0) {
        neighbors[4] = ii(r+1, c+1);
        neighbors[5] = ii(r+1, c-1);
    }
    else {
        neighbors[4] = ii(r-1, c+1);
        neighbors[5] = ii(r-1, c-1);
    }
    return neighbors;
}

int main() {
    vvi board(1000, vi(1000, -1));
    vvi dist(1000, vi(1000, INF));
    ii origin(500, 500);

    queue<ii> q;
    q.push(origin);
    dist[origin.first][origin.second] = 0;
    for (ll i = 0; i < 11000; ++i) {
        ii cur = q.front();
        q.pop();
        ll r = cur.first;
        ll c = cur.second;

        vii neighbors = get_neighbors(r, c);
        for (ll i = 0; i < neighbors.size(); ++i) {
            ll new_r = neighbors[i].first;
            ll new_c = neighbors[i].second;

            if (dist[new_r][new_c] == INF) {
                dist[new_r][new_c] = dist[r][c]+1;
                q.push(ii(new_r, new_c));
            }
        }
    }

    vi amount(5, 0);
    ii cur = origin;
    vi resource(12000); //resource of ith tile
    for (ll i = 0; i < 11000; ++i) {
        ll r = cur.first;
        ll c = cur.second;

        vii neighbors = get_neighbors(r, c);
        ii next(0, 0);  //should have INF dist
        vb present(5, false);
        for (ll i = 0; i < neighbors.size(); ++i) {
            ll new_r = neighbors[i].first;
            ll new_c = neighbors[i].second;
            if (board[new_r][new_c] == -1) {
                if (dist[new_r][new_c] < dist[next.first][next.second] || (dist[new_r][new_c] == dist[next.first][next.second] && new_r < next.first)) {
                    next = ii(new_r, new_c);
                }
            }

            if (board[new_r][new_c] != -1)
                present[board[new_r][new_c]] = true;
        }

        ll best_r = -1;
        for (ll i = 0; i < 5; ++i) {
            if (!present[i]) {
                if (best_r == -1 || amount[i] < amount[best_r]) {
                    best_r = i;
                }
            }
        }
        board[r][c] = best_r;
        ++amount[best_r];
        resource[i] = best_r;

        cur = i == 0 ? ii(500, 501) : next;
    }

    ll c;
    cin >> c;
    for (ll cs = 1; cs <= c; ++cs) {
        ll n;
        cin >> n;
        cout << resource[n-1]+1 << endl;
    }
    return 0;
}
