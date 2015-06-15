#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef pair<ll, ll> ii;
typedef pair<ii, ii> iiii;

int main() {
    ll N, M;
    cin >> N >> M;
    vvb grid(N, vb(M, false));

    ll startr, startc, endr, endc;
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < M; ++j) {
            char c;
            cin >> ws >> c;

            if (c == '#') {
                grid[i][j] = true;
            }
            else if (c == 'C') {
                startr = i;
                startc = j;
            }
            else if (c == 'D') {
                endr = i;
                endc = j;
            }
        }
    }

    priority_queue<iiii, vector<iiii>, greater<iiii> > open;
    vvvb visited(N, vvb(M, vb(2, false)));
    open.push(iiii(ii(0, 0), ii(startr, startc)));

    ll sol = -1;
    while (!open.empty()) {
        ll r = open.top().second.first;
        ll c = open.top().second.second;
        ll cost = open.top().first.first;
        ll g = open.top().first.second;
        open.pop();
        //cerr << r << " " << c << " " << cost << " " << g << endl; 

        if (r < 0 || r >= N || c < 0 || c >= M) continue;
        if (grid[r][c]) continue;
        
        if (r == endr && c == endc) {
            sol = cost;
            goto END;
        }
        
        ll newr;
        ll dr = g == 0 ? 1 : -1;
        for (ll i = 1; true; ++i) {
            newr = r + i*dr;
            if (newr < 0 || newr >= N) break; 
            if (newr == endr && c == endc) {
                sol = cost;
                goto END;
            }
            if (grid[newr][c]) {
                newr -= dr;
                break;
            }
        }
        
        r = newr;
        //cerr << r << " " << c << " " << cost << " " << g << endl; 

        if (r < 0 || r >= N || c < 0 || c >= M) continue;
        if (visited[r][c][g]) continue;
       
        visited[r][c][g] = true;
        if (r == endr && c == endc) {
            sol = cost;
            goto END;
        }

       open.push(iiii(ii(cost, g), ii(r, c+1)));
       open.push(iiii(ii(cost, g), ii(r, c-1)));
       open.push(iiii(ii(cost+1, !g), ii(r, c)));
    }
END:
    cout << sol << endl;
}
