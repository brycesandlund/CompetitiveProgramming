#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vvi nums;

vi multiply(vi &one, vi &two) {
    vi result(1020, 0);
    for (ll i = 0; i < 1020; ++i) {
        result[i] = one[i] + two[i];
    }
    return result;
}

vi divide(vi &one, vi &two) {
    vi result(1020, 0);
    for (ll i = 0; i < 1020; ++i) {
        result[i] = one[i] - two[i];
    }
    return result;
}

vi binom(ll n, ll r) {
    vi result(1020, 0);
    ll num = n;
    for (ll i = 0; i < r; ++i) {
        result = multiply(result, nums[num]);
        --num;
    }

    for (ll i = 1; i <= r; ++i) {
        result = divide(result, nums[i]);
    }
    return result;
}

int main() {
    nums = vvi(1010, vi(1020, 0));
    for (ll i = 0; i < 1010; ++i) {
        ll cur = i;
        for (ll j = 2; j <= cur; ++j) {
            if (cur % j == 0) {
                cur /= j;
                ++nums[i][j];
                --j;
            }
        }
    }

    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;
        if (N == 0)
            cout << 1 << endl;
        else if (N == 1)
            cout << "A+B" << endl;
        else {
            cout << "A^" << N;
            for (ll i = 1; i < N; ++i) {
                cout << "+";
                vi coeff = binom(N, i);
                
                for (ll i = 0; i < 1020; ++i) {
                    if (coeff[i] == 1) {
                        cout << i;
                    }
                    else if (coeff[i] > 1) {
                        cout << i << "^" << coeff[i];
                    }

                    if (coeff[i] > 0)
                        cout << "x";
                }

                if (i == 1 && (N-i) == 1)
                    cout << "AB";
                else if (i == 1)
                    cout << "A^" << (N-i) << "B";
                else if ((N-i) == 1)
                    cout << "A" << "B^" << i;
                else
                    cout << "A^" << (N-i) << "B^" << i;
            }
            cout << "+B^" << N << endl;
        }
    }
}
