#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n, k;
    cin >> n >> k;
    multiset<ll, greater<ll> > a;
    for (ll i = 0; i < k; ++i) {
        ll num;
        cin >> num;
        a.insert(num);
    }

    ll quads = n;
    ll doubles = n*2;

    while (quads > 0 && !a.empty()) {
        --quads;
        ll maximum = *a.begin();
        if (maximum >= 4) {
            a.erase(a.begin());
            if (maximum > 4)
                a.insert(maximum-4);
        }
        else if (maximum == 3) {
            a.erase(a.begin());
        }
        else if (maximum <= 2) {
            ll minimum = *a.rbegin();
            if (minimum == 1) {
                a.erase(prev(a.end()));
                a.erase(a.begin());
            }
            else if (a.size() == 1) {
                a.erase(a.begin());
            }
            else if (minimum == 2) {
                a.erase(a.begin());
                a.erase(prev(a.end()));
                a.insert(1);
            }
        }
    }

    while (doubles > 0 && !a.empty()) {
        --doubles;
        ll maximum = *a.begin();
        if (maximum >= 2) {
            a.erase(a.begin());
            if (maximum > 2)
                a.insert(maximum-2);
        }
        else if (maximum == 1) {
            a.erase(a.begin());
        }
    }

    if (a.empty())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
