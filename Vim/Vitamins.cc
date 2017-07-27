#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <fstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
typedef vector<char> vc;

ll find(vi &C, ll x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vi &C, ll x, ll y) { C[find(C, x)] = find(C, y); }

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    ll n, m;
    cin >> n >> m;

    vi UF(n);
    for (ll i = 0; i < n; ++i)
        UF[i] = i;

    vb in(n, false), out(n, false);
    vii less_than;
    for (ll i = 0; i < m; ++i) {
        char c;
        ll a, b;
        string exp;
        cin >> exp;
        sscanf(exp.c_str(), "%lld%c%lld", &a, &c, &b);

        --a; --b;

        if (c == '=') {
            merge(UF, a, b);
        }
        else if (c == '>') {
            swap(a, b);
        }

        if (c != '=') {
            less_than.push_back(ii(a, b));
        }
    }

    vc ans(n, '?');

    for (ll i = 0; i < less_than.size(); ++i) {
        out[find(UF, less_than[i].first)] = true;
        in[find(UF, less_than[i].second)] = true;
    }
    for (ll i = 0; i < n; ++i) {
        if (in[find(UF, i)] && out[find(UF, i)]) {
            ans[find(UF, i)] = 'R';
        }
    }

    for (ll i = 0; i < less_than.size(); ++i) {
        if (ans[find(UF, less_than[i].second)] == 'R') {
            ans[find(UF, less_than[i].first)] = 'B';
        }
        else if (ans[find(UF, less_than[i].first)] == 'R') {
            ans[find(UF, less_than[i].second)] = 'W';
        }
    }

    for (ll i = 0; i < n; ++i) {
        cout << ans[find(UF, i)];
    }
    cout << endl;
}
