#include <iostream>
#include <vector>

#define INF 1000000000000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
#define LOGSZ 17

int ft1[(1<<LOGSZ)+1];
int ft2[(1<<LOGSZ)+1];
int N = (1<<LOGSZ);

// add v to value at x
void set(int x, int v, int *tree) {
    while(x <= N) {
        tree[x] += v;
        x += (x & -x);
    }
}

// get cumulative sum up to and including x
int get(int x, int *tree) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= (x & -x);
    }
    return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
int getind(int x, int *tree) {
    int idx = 0, mask = N;
    while(mask && idx < N) {
        int t = idx + mask;
        if(x >= tree[t]) {
            idx = t;
            x -= tree[t];
        }
        mask >>= 1;
    }
    return idx;
}

int main() {
    ll n;
    cin >> n;
    vi n_length(100020, 0);
    vi n_energy(100020, 0);
    vvi energies_at_length(100020);

    vi l(n);

    for (ll i = 0; i < n; ++i) {
        cin >> l[i];
        ++n_length[l[i]];
    }

    vi d(n);
    for (ll i = 0; i < n; ++i) {
        cin >> d[i];
        n_energy[l[i]] += d[i];
        set(d[i], 1, ft1);
        set(d[i], d[i], ft2);
        energies_at_length[l[i]].push_back(d[i]);
    }

    ll total = n;
    ll total_energy = 0;

    ll best = INF;
    for (ll i = 100000; i >= 0; --i) {
        if (n_length[i] > 0) {
            for (ll j = 0; j < energies_at_length[i].size(); ++j) {
                ll cur = energies_at_length[i][j];
                set(cur, -1, ft1);
                set(cur, -cur, ft2);
            }
            
            ll cost = 0;
            if (n_length[i]*2 <= total) {
                ll remove = total - n_length[i]*2+1;
                ll idx = getind(remove, ft1);
                if (get(idx, ft1) < remove) ++idx;
                
                ll extra = get(idx, ft1) - remove;
                cost = get(idx, ft2) - extra*idx;
            }

            best = min(best, cost+total_energy);
            total_energy += n_energy[i];
            total -= n_length[i];
        }
    }

    cout << best << endl;
    return 0;
}
