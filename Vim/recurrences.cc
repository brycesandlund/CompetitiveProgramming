#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vvi matrix_mult(vvi A, vvi B, ll m) {
    vvi result(A.size(), vi(B[0].size(), 0));
    for (ll i = 0; i < result.size(); ++i) {
        for (ll j = 0; j < result[i].size(); ++j) {
            for (ll k = 0; k < A[0].size(); ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % m;
            }
        }
    }
    return result;
}

vvi matrix_pow(vvi A, ll n, ll m) {
    if (n == 1) {
        return A;
    }
    else if (n % 2 == 0) {
        vvi smaller = matrix_pow(A, n/2, m);
        return matrix_mult(smaller, smaller, m);
    }
    else {
        return matrix_mult(matrix_pow(A, n-1, m), A, m);
    }
}

int main() {
    ll d, n, m;
    for (ll cs = 1; cin >> d >> n >> m && d; ++cs) {
        vvi T(d, vi(d, 0));
        for (ll i = 0; i < d-1; ++i) {
            T[i][i+1] = 1;
        }

        for (ll i = d-1; i >= 0; --i) {
            cin >> T[d-1][i];
        }

        vvi init(d, vi(1));
        for (ll i = 0; i < d; ++i) {
            cin >> init[i][0];
        }

        if (n == 1) {
            cout << init[0][0] << endl;
        }
        else {
            T = matrix_pow(T, n-1, m);
            vvi result = matrix_mult(T, init, m);

            cout << result[0][0] << endl;
        }
    }
    return 0;
}
