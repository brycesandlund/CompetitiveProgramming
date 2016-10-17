#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

#define EP 1e-10

using namespace std;

#define MAXN (1 << 18)

typedef long long ll;
typedef complex<double> T;
typedef vector<T> vt;
typedef vector<ll> vi;

void FFT(vt &a, bool invert) {
    ll n = a.size();

    for (ll i=1, j=0; i<n; ++i) {
        ll bit = n >> 1;
        for(; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    
    for (ll len=2; len<=n; len<<=1) {
        double ang = 2*M_PI/len * (invert ? -1 : 1);
        T wlen (cos(ang), sin(ang));
        for (ll i = 0; i < n; i += len) {
            T w(1);
            for (ll j = 0; j < len/2; ++j) {
                T u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert)
        for (ll i = 0; i < n; ++i)
            a[i] /= n;
}

int main() {
    ll N;
    cin >> N;
    vi Fint(MAXN, 0);

    for (ll i = 0; i < N; ++i) {
        ll cur;
        cin >> cur;

        if (cur >= 0)
            ++Fint[cur];
        else
            ++Fint[MAXN+cur];
    }

    vt F(Fint.begin(), Fint.end());

    FFT(F, false);
    vt H(MAXN, 0);
    
    for (ll i = 0; i < MAXN; ++i) {
        H[i] = F[i] * F[i];
    }

    FFT(H, true);

    vi Hint(MAXN);
    
    for (ll i = 0; i < MAXN; ++i) {
        Hint[i] = (ll)(H[i].real() + .5 + EP);
        if (i > 0) {
            if (Fint[i] > 0) {
                Hint[i] -= 2*Fint[0];
            }
        }
    }

    for (ll i = 1; i < MAXN/2; ++i) {
        if (i % 2 == 0) {
            Hint[i] -= Fint[i/2];
        }
    }

    for (ll i = MAXN/2; i < MAXN; ++i) {
        ll conv = -MAXN+i;

        if ((-conv) % 2 == 0) {
            ll other = MAXN+conv/2;
            Hint[i] -= Fint[other];
        }
    }

    ll ways = 0;
    Hint[0] -= Fint[0] * Fint[0];

    if (Fint[0] >= 3)
        ways += Fint[0] * (Fint[0]-1) * (Fint[0]-2);

    ways += Hint[0] * Fint[0];
    for (ll i = 1; i < MAXN; ++i) {
        ways += Hint[i] * Fint[i];
    }

    cout << ways << endl;

    return 0;
}
