#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

#define MAX_N (1 << 19)

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll gcd(ll a, ll b, ll &s, ll &t) {
    if (b == 0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
    } else { ll g = gcd(b, a%b, t, s); t -= a/b*s; return g; }
}

ll inverse(ll n, ll mod) {
    ll s, t;
    gcd(n, mod, s, t);
    return (s > 0) ? s : s + mod;
}

const ll mod = 5 * (1 << 25) + 1;   //167772161
const ll root = 243;
const ll root_1 = 114609789;
const ll root_pw = 1<<25;

void fft(vi &a, bool invert) {
    ll n = a.size();

    for (ll i=1, j=0; i<n; ++i) {
        ll bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len=2; len<=n; len<<=1) {
        ll wlen = invert ? root_1 : root;
        for (ll i=len; i<root_pw; i<<=1)
            wlen = ll(wlen * 1LL * wlen % mod);
        for (ll i=0; i<n; i+=len) {
            ll w = 1;
            for (ll j=0; j<len/2; ++j) {
                ll u = a[i+j], v = ll(a[i+j+len/2] * 1LL * w % mod);
                a[i+j] = u+v < mod ? u+v : u+v-mod;
                a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
                w = ll(w * 1LL * wlen % mod);
            }
        }
    }
    if (invert) {
        ll nrev = inverse(n, mod);
        for (ll i=0; i<n; ++i)
            a[i] = ll(a[i] * 1LL * nrev % mod);
    }
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N; ++cs) {
        vi knob(N);
        for (ll i = 0; i < N; ++i) {
            cin >> knob[i];
        }
        
        ll M;
        cin >> M;
        vi hole(M);
        for (ll i = 0; i < M; ++i) {
            cin >> hole[i];
        }

        vi A(MAX_N, 0);
        for (ll i = 0; i < N; ++i) {
            A[knob[i]] = 1;
        }

        A[0] = 1;
        vi B = A;

        fft(A, false);
        fft(B, false);

        vi C(MAX_N);
        for (ll i = 0; i < MAX_N; ++i)
            C[i] = A[i] * B[i] % mod;

        fft(C, true);

        ll reachable = 0;
        for (ll i = 0; i < M; ++i) {
            if (C[hole[i]] > 0)
                ++reachable;
        }

        cout << reachable << endl;
    }
}
