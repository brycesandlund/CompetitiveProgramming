#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll idx_of(vi &arr, ll val) {
    for (ll i = 0; i < arr.size(); ++i) {
        if (arr[i] == val)
            return i;
    }
    while (true) {
    
    }
}

int main() {
    ll n, m, k;
    cin >> n >> m >> k;

    vi items(k);

    for (ll i = 0; i < k; ++i) {
        ll pl;
        cin >> pl;
        --pl;
        items[i] = pl;
    }

    vvi a(n, vi(m));
    for (ll i = 0; i < n; ++i)
        for (ll j = 0; j < m; ++j) {
            cin >> a[i][j];
            --a[i][j];
        }

    ll t = 0;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            ll idx = idx_of(items, a[i][j]);
            t += idx+1;
            items.erase(items.begin()+idx);
            items.insert(items.begin(), a[i][j]);
        
            
            //for (ll q = 0; q < k; ++q)
            //    cerr << items[q] << " ";
            //cerr << endl;
            

            //cerr << idx+1 << endl;
        }
    }

    cout << t << endl;

    return 0;
}
