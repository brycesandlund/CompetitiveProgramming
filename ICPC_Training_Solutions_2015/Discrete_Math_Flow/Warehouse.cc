#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef pair<ll, ll> ii;

// BEGIN
///////////////////////////////////////////////////////////////////////////
// Min cost bipartite matching via shortest augmenting paths
//
// This is an O(n^3) implementation of a shortest augmenting path
// algorithm for finding min cost perfect matchings in dense
// graphs.  In practice, it solves 1000x1000 problems in around 1
// second.
//
//   cost[i][j] = cost for pairing left node i with right node j
//   Lmate[i] = index of right node that left node i pairs with
//   Rmate[j] = index of left node that right node j pairs with
//
// The values in cost[i][j] may be positive or negative.  To perform
// maximization, simply negate the cost[][] matrix.
///////////////////////////////////////////////////////////////////////////

typedef vector<int> vi;
typedef vector<vi> vvi;

double MinCostMatching(const vvi &cost, vi &Lmate, vi &Rmate) {
    int n = int(cost.size());
    
    // construct dual feasible solution
    vi u(n);
    vi v(n);
    for (int i = 0; i < n; i++) {
        u[i] = cost[i][0];
        for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
    }
    for (int j = 0; j < n; j++) {
        v[j] = cost[0][j] - u[0];
        for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
    }
    
    // construct primal solution satisfying complementary slackness
    Lmate = vi(n, -1);
    Rmate = vi(n, -1);
    int mated = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Rmate[j] != -1) continue;
            if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
                Lmate[i] = j;
                Rmate[j] = i;
                mated++;
                break;
            }
        }
    }
    
    vi dist(n);
    vi dad(n);
    vi seen(n);
    
    // repeat until primal solution is feasible
    while (mated < n) {
        
        // find an unmatched left node
        int s = 0;
        while (Lmate[s] != -1) s++;
        
        // initialize Dijkstra
        fill(dad.begin(), dad.end(), -1);
        fill(seen.begin(), seen.end(), 0);
        for (int k = 0; k < n; k++)
            dist[k] = cost[s][k] - u[s] - v[k];
        
        int j = 0;
        while (true) {
            
            // find closest
            j = -1;
            for (int k = 0; k < n; k++) {
                if (seen[k]) continue;
                if (j == -1 || dist[k] < dist[j]) j = k;
            }
            seen[j] = 1;
            
            // termination condition
            if (Rmate[j] == -1) break;
            
            // relax neighbors
            const int i = Rmate[j];
            for (int k = 0; k < n; k++) {
                if (seen[k]) continue;
                const double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (dist[k] > new_dist) {
                    dist[k] = new_dist;
                    dad[k] = j;
                }
            }
        }
        
        // update dual variables
        for (int k = 0; k < n; k++) {
            if (k == j || !seen[k]) continue;
            const int i = Rmate[k];
            v[k] += dist[k] - dist[j];
            u[i] -= dist[k] - dist[j];
        }
        u[s] += dist[j];
        
        // augment along path
        while (dad[j] >= 0) {
            const int d = dad[j];
            Rmate[j] = Rmate[d];
            Lmate[Rmate[j]] = j;
            j = d;
        }
        Rmate[j] = s;
        Lmate[s] = j;
        
        mated++;
    }
    
    double value = 0;
    for (int i = 0; i < n; i++)
        value += cost[i][Lmate[i]];
    
    return value;
}

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

ll h, w;
ll x_counter = 0;
ll b_counter = 0;

vi get_dist(ll start_r, ll start_c, vvc &grid, vvi &grid_num) {
    queue<ii> q;
    q.push(ii(start_r, start_c));
    vvi dist(h, vi(w, INF));
    dist[start_r][start_c] = 0;
    vi final_dist(x_counter, INF);

    while (!q.empty()) {
        ll r = q.front().first;
        ll c = q.front().second;
        q.pop();

        if (grid[r][c] == 'X') {
            final_dist[grid_num[r][c]] = dist[r][c];
        }

        for (ll i = 0; i < 4; ++i) {
            ll new_r = r + dr[i];
            ll new_c = c + dc[i];    
            
            if (new_r < 0 || new_r >= h || new_c < 0 || new_c >= w)
                continue;

            if (grid[new_r][new_c] == '#')
                continue;
            
            if (dist[r][c]+1 < dist[new_r][new_c]) {
                dist[new_r][new_c] = dist[r][c]+1;
                q.push(ii(new_r, new_c));
            }
        }
    }

    return final_dist;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        cin >> h >> w;

        vvc grid(h, vc(w));
        vvi grid_num(h, vi(w, -1));
        for (ll i = 0; i < h; ++i) {
            for (ll j = 0; j < w; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == 'B')
                    grid_num[i][j] = b_counter++;
                if (grid[i][j] == 'X')
                    grid_num[i][j] = x_counter++;
            }
        }

        vvi cost(x_counter, vi(x_counter));

        for (ll i = 0; i < h; ++i) {
            for (ll j = 0; j < w; ++j) {
                if (grid[i][j] == 'B') {
                    cost[grid_num[i][j]] = get_dist(i, j, grid, grid_num);
                }
            }
        }
        
        vi Lmate, Rmate;
        cout << MinCostMatching(cost, Lmate, Rmate) << endl;
    }
    return 0;
}
