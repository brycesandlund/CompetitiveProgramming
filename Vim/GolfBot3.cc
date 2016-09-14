#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

#define MAX_N (1 << 19)

using namespace std;

typedef long long ll;
typedef complex<double> T;
typedef vector<T> vt;
typedef vector<ll> vi;

const double PI = 4*atan(1);

typedef complex<double> base;

void fft(vector<base> &a, bool invert) {
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
        base wlen (cos(ang), sin(ang));
        for (ll i=0; i<n; i+=len) {
            base w(1);
            for (ll j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
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

        vector<base> A(MAX_N, 0);
        for (ll i = 0; i < N; ++i) {
            A[knob[i]] = 1;
        }

        A[0] = 1;
        vector<base> B = A;

        fft(A, false);
        fft(B, false);

        vector<base> C(MAX_N);
        for (ll i = 0; i < MAX_N; ++i)
            C[i] = A[i] * B[i];

        fft(C, true);

        ll reachable = 0;
        for (ll i = 0; i < M; ++i) {
            if (C[hole[i]].real() > .5)
                ++reachable;
        }

        cout << reachable << endl;
    }
}
