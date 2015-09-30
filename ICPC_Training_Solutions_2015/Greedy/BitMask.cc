#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

vi to_binary(ll k) {
    vi binary(32);
    for (ll i = 31; i >= 0; --i) {
        binary[i] = k % 2;
        k >>= 1;
    }
    return binary;
}

int main() {
    ll N, L, U;
    for (ll cs = 1; cin >> N >> L >> U; ++cs) {
        vi N_bin = to_binary(N);
        vi M_bin(32, 0);
        ll M = 0;
        for (ll i = 0; i < 32; ++i) {
            if (N_bin[i] == 0) {
                ll M_1 = M + (1LL << (31-i));
                if (M_1 <= U) {
                    M_bin[i] = 1;
                    M = M_1;
                }
            }
            else if (N_bin[i] == 1) {
                ll M_0 = M + (1LL << (31-i))-1;
                if (M_0 < L) {
                    M_bin[i] = 1;
                    M = M_0+1;
                }
            }
        }

        cout << M << endl;
    }
    return 0;
}
