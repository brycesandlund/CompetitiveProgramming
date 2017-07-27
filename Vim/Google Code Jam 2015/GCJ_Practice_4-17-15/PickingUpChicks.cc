#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

int main() {
    ll C;
    cin >> C;
    for (ll cs = 1; cs <= C; ++cs) {
        ll N, K, B, T;
        cin >> N >> K >> B >> T;

        vi X(N);
        for (ll i = 0; i < N; ++i) {
            cin >> X[i];
        }

        vi V(N);
        for (ll i = 0; i < N; ++i) {
            cin >> V[i];
        }

        vb inTime(N, false);
        for (ll i = 0; i < N; ++i) {
            if ((B-X[i]+V[i]-1)/V[i] <= T) {
                inTime[i] = true;
            }
        }

        vi swaps;
        for (ll i = 0; i < N; ++i) {
            ll cur = 0;
            if (inTime[i]) {
                for (ll j = i+1; j < N; ++j) {
                    if (!inTime[j]) {
                        ++cur;
                    }
                }

                swaps.push_back(cur);
            }
        }

        if (swaps.size() < K) {
            printf("Case #%lld: IMPOSSIBLE\n", cs);
        }
        else {
            sort(swaps.begin(), swaps.end());

            ll total = 0;
            for (ll i = 0; i < K; ++i) {
                total += swaps[i];
            }

            printf("Case #%lld: %lld\n", cs, total);
        }
    }
}
