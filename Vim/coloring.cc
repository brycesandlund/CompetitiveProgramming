#include <iostream>
#include <vector>

#define M 1000000007

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a < 0) {
        ll r = egcd(-a, b, x, y);
        x *= -1;
        return r;
    }
    if (b < 0) {
        ll r = egcd(a, -b, x, y);
        y *= -1;
        return r;
    }
    ll u = y = 0, v = x = 1;
    while (b) {
        ll q = a/b, r = a % b;
        a = b, b = r;
        ll m = u, n = v;
        u = x - q*u, v = y - q*v;
        x = m, y = n;
    }
    return a;
}

ll modinv(ll a, ll n) {
    ll x, y, g = egcd(a, n, x, y);
    if (g != 1) return -1;
    x %= n;
    if (x < 0) x += n;
    return x;
}

ll nCk_p(ll n, ll c, ll p) {
    if (c > n)
        return 0;
    
    ll num = 1;
    ll den = 1;
    for (ll i = 1; i <= c; ++ i) {
        num = (num * n) % p;
        --n;
        den = (den * i) % p;
    }
    return (modinv(den, p) * num) % p;
}

ll pow_mod(ll n, ll e) {
    if (e == 1)
        return n;
    else if (e % 2 == 0) {
        ll small = pow_mod(n, e/2);
        return (small * small) % M;
    }
    else {
        return (n * pow_mod(n, e-1)) % M;
    }
}

int main() {
    ll n, m, k;
    cin >> n >> m >> k;

    vi ways(n+1, 0);
    vi ways_col(n+1, 0);
    for (ll i = 1; i <= n; ++i) {
        ways[i] = pow_mod(n, i);
        ways_col[i] = (ways_col[i-1] + ways[i]) % M;
    }
    
    vvi ways_less(m+1, vi(n+1, 1));
    
    for (ll i = 1; i <= m; ++i)
        ways_less[i][1] = 1;

    for (ll i = 1; i <= m; ++ i)
        for (ll j = 2; j <= n; ++j) {
            ways_less[i][j] = (ways_less[i-1][j] * ways_col[j]) % M;
        }

    ll ans = 0;
    cerr << ways[1] << endl;

    for (ll i = 1; i <= n; ++i) {
        ll cur_ans = (ways[i]*ways[i]) % M;
        if (m > 2)
            cur_ans = (cur_ans * ways_less[m-2][i]) % M;
        cur_ans = (cur_ans * nCk_p(k, i, M)) % M;

        ans = (ans + cur_ans) % M;
    }

    cout << ans << endl;

    return 0;
}
