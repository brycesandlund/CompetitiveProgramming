#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

#define f first
#define s second
#define M 1000000007

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef pair<ii, ll> iii;
typedef vector<iii> viii;
typedef vector<ll> vi;
typedef vector<vi> vvi;



int main() {
    ll n, m;
    cin >> n >> m;

    vvi adj_list(n);

    for (ll i = 0; i < n; ++i) {
        ll p;
        cin >> p;
        --p;
        adj_list[p].push_back(i);
    }

    vi ways(m+1);

}
