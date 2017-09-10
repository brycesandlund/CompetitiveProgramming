#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define M 1000000007

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
    
vi two_pow_arr(500010);

ll two_pow(ll x) {
    if (x >= 0)
        return two_pow_arr[x];
    else
        return 0;
}

int main() {
    two_pow_arr[0] = 1;
    for (ll i = 1; i < 500010; ++i)
        two_pow_arr[i] = (two_pow_arr[i-1] * 2) % M;


    string S;
    cin >> S;
    ll left_ones = 0;
    ll left_qs = 0;
    ll total_qs = 0;
    
    for (ll i = 0; i < S.size(); ++i) {
        if (S[i] == '?')
            ++total_qs;
    }

    ll ans = 0;
    for (ll i = 0; i < S.size(); ++i) {
        if (S[i] != '1') {
            ll q_right = total_qs - left_qs;
            if (S[i] == '?')
                --q_right;

            ans = (ans + (left_qs*two_pow(left_qs-1))%M * two_pow(q_right))%M;
            ans = (ans + two_pow(left_qs + q_right) * left_ones)%M;
        }
        if (S[i] == '1')
            ++left_ones;
        if (S[i] == '?')
            ++left_qs;
    }

    cout << ans << endl;
}
