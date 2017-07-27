#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 10000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef pair<ll, ll> ii;
typedef pair<ii, ii> iiii;

ll dx[] = {0, 0, 1, 0, 0, -1};
ll dy[] = {0, 1, 0, 0, -1, 0};
ll dz[] = {1, 0, 0, -1, 0, 0};

int main() {
    ll N;
    cin >> N;

    //z, y, x
    vvvi cubes(N, vvi(N, vi(N)));

    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            for (ll k = 0; k < N; ++k) {
                cin >> cubes[i][j][k];
            }
        }
    }

    ll sx, sy, sz;
    ll fx, fy, fz;
    cin >> sx >> sy >> sz >> fx >> fy >> fz;

    priority_queue<iiii, vector<iiii>, greater<iiii> > pq;
    
    pq.push(iiii(ii(0, sz), ii(sy, sx)));

    vvvi dist(N, vvi(N, vi(N, INF)));
    dist[sz][sy][sx] = cubes[sz][sy][sx];

    while (!pq.empty()) {

        iiii cur = pq.top();
        pq.pop();

        ll z = cur.first.second;
        ll y = cur.second.first;
        ll x = cur.second.second;

        if (x == fx && y == fy && z == fz)
            break;

        for (ll i = 0; i < 6; ++i) {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            ll nz = z + dz[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && nz >= 0 && nz < N) {
                ll n_cost = dist[z][y][x] + cubes[nz][ny][nx];
                if (n_cost < dist[nz][ny][nx]) {
                    pq.push(iiii(ii(n_cost, nz), ii(ny, nx)));
                    dist[nz][ny][nx] = n_cost;
                }
            }
        }
    }

    cout << dist[fz][fy][fx] << endl;
    
    return 0;
}
