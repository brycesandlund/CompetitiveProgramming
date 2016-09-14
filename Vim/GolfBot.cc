#include <iostream>
#include <complex>
#include <vector>

#define MAX_N (1 << 19)

using namespace std;

typedef long long ll;
typedef complex<double> T;
typedef vector<T> vt;
typedef vector<ll> vi;

const double PI = 4*atan(1);

void FFT_r(T *A, T *B, ll p, ll n, ll d) {
    if (n == 1) { B[0] = A[0]; return; }
    FFT_r(A, B, 2*p, n/2, d);
    FFT_r(A+p, B+n/2, 2*p, n/2, d);
    for (ll k = 0; k < n/2; ++k) {
        T w = polar(1.0, 2*PI*k/n*d);
        T even = B[k], odd = B[k+n/2];
        B[k] = even + w * odd;
        B[k+n/2] = even - w * odd;
    }
}

void FFT(vt &_A, ll d) {
    const ll n = _A.size();
    T *A = new T[n], *B = new T[n];
    for (ll i = 0; i < n; ++i) A[i] = _A[i];
    FFT_r(A, B, 1, n, d);
    for (ll i = 0; i < n; ++i) _A[i] = B[i];
    delete[] A;
    delete[] B;
    if (d < 0) for (ll i = 0; i < n; ++i) _A[i] /= n;
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

        vt f(MAX_N, 0);
        for (ll i = 0; i < N; ++i) {
            f[knob[i]] = 1;
        }

        f[0] = 1;

        vt g = f;
        FFT(f, 1);
        FFT(g, 1);
        vt h(MAX_N);
        for (ll i = 0; i < MAX_N; ++i)
            h[i] = f[i] * g[i];

        FFT(h, -1);

        ll reachable = 0;
        for (ll i = 0; i < M; ++i) {
            if (h[hole[i]].real() > .5) {
                ++reachable;
            }
        }

        cout << reachable << endl;
    }
}
