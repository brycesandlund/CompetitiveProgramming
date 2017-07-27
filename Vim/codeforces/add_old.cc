#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll transform(ll num) {
    stringstream ss;
    ss << num;
    string str;
    ss >> str;

    sort(str.rbegin(), str.rend());
    stringstream ss2;
    ss2 << str;
    ss2 >> num;

    return num;
}

int main() {
    ll n;
    cin >> n;

    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll sumMax = 0;
    for (ll shift = 0; shift < (1 << n); ++shift) {
        ll cur = 0;
        for (ll copy = shift, i = 0; i < n; copy /= 2, ++i) {
            cur += a[i];
            if (copy % 2 == 1) {
                cur = transform(cur);
            }
        }

        sumMax = max(sumMax, cur);
    }

    cout << sumMax << endl;
}
