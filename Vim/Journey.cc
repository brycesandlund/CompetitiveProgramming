#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

vvi adj_list;
ll n;
vb visited;

double e_length(ll u) {
    visited[u] = true;
    
    ll options = 0;
    for (ll i = 0; i < adj_list[u].size(); ++i) {
        ll v = adj_list[u][i];

        if (!visited[v]) {
            ++options;
        }
    }
    
    double ans = 0;
    for (ll i = 0; i < adj_list[u].size(); ++i) {
        ll v = adj_list[u][i];

        if (!visited[v]) {
            ans += 1.0/options * (e_length(v) + 1);
        }
    }

    return ans;
}

int main() {
    cin >> n;

    adj_list = vvi(n);
    for (ll i = 0; i < n-1; ++i) {
        ll u, v;
        cin >> u >> v;
        --u; --v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    visited = vb(n, false);
    cout << fixed;
    cout << setprecision(15) << e_length(0) << endl;
}
