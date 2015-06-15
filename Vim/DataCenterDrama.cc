#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;


int main() {
    ll n, m;
    cin >> n >> m;

    vii adjList(n);
    for (ll i = 0; i < m; ++i) {
        ll a_i, b_i;
        cin >> a_i >> b_i;
        --a_i;
        --b_i;
        adjList[a_i].push_back(b_i);
        adjList[b_i].push_back(a_i);
    }
}
