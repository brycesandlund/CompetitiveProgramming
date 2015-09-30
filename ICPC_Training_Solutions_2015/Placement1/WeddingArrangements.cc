#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll count(ll l, ll r, vi &a) {
    if (l == r)
        return 0;
    
    ll m = (l+r)/2;
    ll left = count(l, m, a);
    ll right = count(m+1, r, a);

    vi a2;
    ll lpt = l, rpt = m+1;
    ll mid = 0;
    ll l_size = m-l+1;
    while (lpt <= m || rpt <= r) {
        if (rpt > r || (lpt <= m && a[lpt] < a[rpt])) {
            a2.push_back(a[lpt]);
            ++lpt;
        }
        else {
            a2.push_back(a[rpt]);
            ++rpt;
            mid += (l_size - (lpt-l));
        }
    }
    for (ll i = l; i <= r; ++i) {
        a[i] = a2[i-l];
    }
    return left+right+mid;
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N && N; ++cs) {
        unordered_map<string, ll> mp;
        for (ll i = 0; i < N; ++i) {
            string person;
            cin >> person;
            mp[person] = i;
        }

        vi a(N);
        for (ll i = 0; i < N; ++i) {
            string person;
            cin >> person;
            a[i] = mp[person];
        }

        cout << count(0, N-1, a) << endl;
    }
}
