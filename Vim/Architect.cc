#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

bool FindMatch(ll i, vvi &adj_list, vi &mr, vi &mc, vb &seen) {
    for (ll j = 0; j < adj_list[i].size(); ++j) {
        ll item = adj_list[i][j];
        if (!seen[item]) {
            seen[item] = true;
            if (mc[item] < 0 || FindMatch(mc[item], adj_list, mr, mc, seen)) {
                mr[i] = item;
                mc[item] = i;
                return true;
            }
        }
    }
    return false;
}

ll BipartiteMatching(vvi &adj_list, vi &mr, vi &mc) {
    ll ct = 0;
    for (ll i = 0; i < adj_list.size(); ++i) {
        vb seen(mc.size(), false);
        if (FindMatch(i, adj_list, mr, mc, seen)) ct++;
    }
    return ct;
}

ll sum2(ll n) {
    ll sum = n % 10;
    n /= 10;
    sum += n % 10;
    n /= 10;
    sum += n % 10;
    return sum; 
}

ll sum1(ll n) {
    return sum2(n / 1000);
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    ll n, m;
    cin >> n >> m;

    vi num1(n), num2(m);
    for (ll i = 0; i < n; ++i)
        cin >> num1[i];
    for (ll j = 0; j < m; ++j)
        cin >> num2[j];

    vvi adj_list(n);
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (sum1(num1[i]) == sum2(num2[j]) || sum2(num1[i]) == sum1(num2[j])) {
                adj_list[i].push_back(j);
            }
        }
    }

    vi mr(n, -1), mc(m, -1);
    ll matched = BipartiteMatching(adj_list, mr, mc);
    cout << matched << endl;

    for (ll i = 0; i < n; ++i) {
        if (mr[i] != -1) {
            if (sum1(num1[i]) == sum2(num2[mr[i]]))
                cout << "AT " << num1[i] << " " << num2[mr[i]] << endl;
            else
                cout << "TA " << num2[mr[i]] << " " << num1[i] << endl;
        }
    }

    cout << endl;
}
