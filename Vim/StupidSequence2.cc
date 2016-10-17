#include <iostream>
#include <vector>
#include <cmath>

#define NUM 1500 // change when submit!
#define EP 1e-10

using namespace std;

const double EPS = 1e-10;

typedef unsigned long long ll;
typedef vector<ll> vi;
typedef vector<int> VI;
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

T GaussJordan(VVT &a, VVT &b) {
  const int n = a.size();
  const int m = b[0].size();
  VI irow(n), icol(n), ipiv(n);
  T det = 1;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) if (!ipiv[j])
      for (int k = 0; k < n; k++) if (!ipiv[k])
	if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
    if (fabs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;
    irow[i] = pj;
    icol[i] = pk;

    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    for (int p = 0; p < m; p++) b[pk][p] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;      
    }
  }

  for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
    for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);
  }

  return det;
}

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        vi f(NUM, 0);
        for (ll i = 0; i < NUM; ++i) {
            cin >> f[i];
        }

        VVT A(7, VT(7));
        for (ll i = 0; i < 7; ++i) {
            ll entry = 1;
            for (ll j = 0; j < 7; ++j) {
                A[i][j] = entry;
                entry *= (i+1);
            }
        }

        VVT b(7, VT(1));
        for (ll i = 0; i < 7; ++i) {
            b[i][0] = f[i];
        }

        GaussJordan(A, b);

        bool success = true;
        vi a(7);
        
        for (ll i = 0; i < 7; ++i)
            if (b[i][0] < -EP || b[i][0] > 1000+EP)
                success = false;

        for (ll i = 0; i < 7; ++i)
            a[i] = (ll)(b[i][0] + .5 + EP);
        
        for (ll i = 1; i <= NUM; ++i) {
            if (f[i-1] < a[0] || (f[i-1] - a[0]) % i != 0)
                success = false;

            if ((f[i-1]-a[0])/i != a[1] + a[2]*i + a[3]*i*i + a[4]*i*i*i + a[5]*i*i*i*i + a[6]*i*i*i*i*i)
                success = false;

            /*ll test = 1;
            ll sum = 0;
            for (ll j = 0; j < 7; ++j) {
                sum += test * a[j];
                test *= (i+1);
            }
            if (sum != f[i]) {
                success = false;
                break;
            }*/
        }

        if (success) {
            cout << a[0];
            for (ll i = 1; i < 7; ++i) {
                cout << " " << a[i];
            }
            cout << endl;
        }
        else {
            cout << "This is a smart sequence!" << endl;
        }
    }
    return 0;
}
