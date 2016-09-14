#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

// BEGIN
// Two FFT implementations, one using only integers and the other doubles.
// Integers is preferred unless doubles are necessary.
// Based on implementations available at: http://e-maxx.ru/algo/fft_multiply,
// first seen from: http://serjudging.vanb.org/wp-content/uploads/kinversions_hcheng.cc
// Integer version solves UVa Online Judge in 1.45 seconds, double version in 2.35 seconds

// Usage:
// f[0...N-1] and g[0..N-1] are numbers
// Want to compute the convolution h, defined by
// h[n] = sum of f[k]g[n-k] (k = 0, ..., N-1).
// Here, the index is cyclic; f[-1] = f[N-1], f[-2] = f[N-2], etc.
// Let F[0...N-1] be FFT(f), and similarly, define G and H.
// The convolution theorem says H[n] = F[n]G[n] (element-wise product).
// To compute h[] in O(N log N) time, do the following:
//   1. Compute F and G (pass d = 1 as the argument).
//   2. Get H by element-wise multiplying F and G (modulo mod if using integer version)
//   3. Get h by taking the inverse FFT (pass d = -1)

#define MAX_N (1 << 19)     // must be power of 2

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

const ll mod = 5 * (1 << 25) + 1;   // large prime modulus
const ll root = 243;                // primitive root modulo mod
const ll root_1 = 114609789;        // inverse of root modulo mod
const ll root_pw = 1<<25;           // order of the group (Z/modZ)*

// WARNING: negative number -n is represented as mod-n.
void FFT(vi &a, bool invert) {
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


typedef complex<double> T;
typedef vector<T> VT;
const double PI = 4*atan(1);

void FFT_double(VT &a, bool invert) {
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
        double ang = 2*PI/len * (invert ? -1 : 1);
        T wlen (cos(ang), sin(ang));
        for (ll i=0; i<n; i+=len) {
            T w(1);
            for (ll j=0; j<len/2; ++j) {
                T u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert)
        for (ll i=0; i<n; ++i)
            a[i] /= n;
}
// END

#include <iostream>
#include <iomanip>
#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

int main(void)
{
  cout << "If rows come in identical pairs, then everything works." << endl;
  cout << setprecision(8) << fixed;
  
  {
      cout << "Test Integer FFT:" << endl;

      const size_t n = 8;
      ll _a[n] = {0, 1, 3, 3, 1, 0, 2, 0};
      ll _b[n] = {1, 2, 2, 3, 1, 3, 1, 2};
      vi a(_a, _a+n), b(_b,_b+n);
      vi A = a, B = b;
      FFT(A,false);
      FFT(B,false);
      
      vi AB(n);
      FOR(i,0,n) AB[i] = A[i] * B[i] % mod;
      vi ab(AB);
      FFT(ab,true);

      // Test convolution theorem/inverse FFT
      cout << ab[0]; FOR(i,1,n) cout << " " << ab[i]; cout << endl;
      FOR(i,0,n) {
        ll aconvbi = 0;
        FOR(j,0,n) aconvbi += a[j] * b[(n + i - j) % n];
        if( i > 0 ) cout << " ";
        cout << aconvbi;
      }
      cout << endl;
  }
  
  {
      cout << "Test Double FFT:" << endl;

      const size_t n = 8;
      T _a[n] = {0, 1, T(1,3), T(0,5), 1, 0, 2, 0};
      T _b[n] = {1, T(0,-2), T(0,1), 3, -1, -3, 1, -2};
      VT a(_a, _a+n), b(_b,_b+n);
      VT A = a, B = b;
      FFT_double(A,false);
      FFT_double(B,false);
      
      // Test convolution
      cout << A[0]; FOR(i,1,n) cout << " " << A[i]; cout << endl;
      FOR(i,0,n) {
        T Ai = 0;
        FOR(j,0,n) Ai += a[j] * polar(1.0, j*i*2*PI/n);
        if( i > 0 ) cout << " ";
        cout << Ai;
      }
      cout << endl;
      
      // Test convolution theorem/inverse FFT
      VT AB(n);
      FOR(i,0,n) AB[i] = A[i] * B[i];
      VT ab(AB);
      FFT_double(ab,true);
      cout << ab[0]; FOR(i,1,n) cout << " " << ab[i]; cout << endl;
      FOR(i,0,n) {
        T aconvbi = 0;
        FOR(j,0,n) aconvbi += a[j] * b[(n + i - j) % n];
        if( i > 0 ) cout << " ";
        cout << aconvbi;
      }
      cout << endl;
  }

  return 0;
}
