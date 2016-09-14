#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

// code for fast linear recurrence evaluation. Based on blog post at:
// http://fusharblog.com/solving-linear-recurrence-for-programming-contest/
// used for AC answer at: http://codeforces.com/contest/678/problem/D

// compute AB with entries mod M
vvi matrix_mult(vvi A, vvi B, ll M) {
    vvi result(A.size(), vi(B[0].size(), 0));
    for (ll i = 0; i < result.size(); ++i) {
        for (ll j = 0; j < result[i].size(); ++j) {
            for (ll k = 0; k < A[0].size(); ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % M;
            }
        }
    }
    return result;
}

// compute A^n with entries mod M
// if A is m x m, takes O(m^3 log n) time
vvi matrix_pow(vvi A, ll n, ll M) {
    if (n == 1) {
        return A;
    }
    else if (n % 2 == 0) {
        vvi smaller = matrix_pow(A, n/2, M);
        return matrix_mult(smaller, smaller, M);
    }
    else {
        return matrix_mult(matrix_pow(A, n-1, M), A, M);
    }
}

// computes nth term of f(n) = rec[0]*f(n-1) + rec[1]*f(n-2) + ... + rec[k-1]*f(n-k) + c
// given that f(1) = init[0], f(2) = init[1], ..., f(k) = init[k-1]
// in O(k^3 log n) time
ll eval_rec(vi rec, vi init, ll n, ll M, ll c = 0) {
    ll k = rec.size();
    vvi mat(k+1, vi(k+1, 0));
    
    for (ll i = 0; i < k; ++i) {
        mat[i][i+1] = 1;
    }
    for (ll i = 0; i < k; ++i) {
        mat[k-1][i] = rec[k-1-i];
    }
    mat[k][k] = 1;

    if (n == 1)
        return init[0];

    vvi mat_new = matrix_pow(mat, n-1, M);
    vvi vect(k+1, vi(1));
    for (ll i = 0; i < k; ++i)
        vect[i][0] = init[i];
    vect[k][0] = c;

    vvi vect_new = matrix_mult(mat_new, vect, M);
    return vect_new[0][0];
}

int main() {
    ll M = 1000000007;
    ll A, B, n, x;
    cin >> A >> B >> n >> x;
    vvi mat(3, vi(3, 0));
    mat[0][1] = 1;
    mat[1][1] = A;
    mat[1][2] = 1;
    mat[2][2] = 1;

    vvi mat_new = matrix_pow(mat, n, M);
    vvi vect(3, vi(1));
    vect[0][0] = x;
    vect[1][0] = (A*x + B) % M;
    vect[2][0] = B;

    vvi vect_new = matrix_mult(mat_new, vect, M);
    ll ans1 = vect_new[0][0];

    vi recurrence(1, A);
    vi initial(1, x);
    ll ans2 = eval_rec(recurrence, initial, n+1, M, B);

    cout << ans2 << endl;

    return 0;
}
