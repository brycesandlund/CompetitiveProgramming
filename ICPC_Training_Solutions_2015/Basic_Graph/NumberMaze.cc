#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

int main() {
    ll nMazes;
    cin >> nMazes;

    for (ll cs = 1; cs <= nMazes; ++cs) {
        ll N, M;
        cin >> N >> M;
    
        vvi maze(N, vi(M));
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < M; ++j) {
                cin >> maze[i][j];
            }
        }

        priority_queue<iii, viii, greater<iii> > pq;
        pq.push(iii(maze[0][0], ii(0, 0)));
        ll ans = -1;

        vvi best(N, vi(M, INF));
        while (!pq.empty()) {
            iii cur = pq.top();
            pq.pop();

            ll cost = cur.first;
            ll r = cur.second.first;
            ll c = cur.second.second;

            if (cost > best[r][c])
                continue;

            if (r == N-1 && c == M-1) {
                ans = cost;
                break;
            }

            for (ll i = 0; i < 4; ++i) {
                ll new_r = r + dr[i];
                ll new_c = c + dc[i];
                
                if (new_r < 0 || new_r >= N || new_c < 0 || new_c >= M)
                    continue;

                ll new_cost = cost + maze[new_r][new_c];

                if (new_cost < best[new_r][new_c]) {
                    pq.push(iii(new_cost, ii(new_r, new_c)));
                    best[new_r][new_c] = new_cost;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
