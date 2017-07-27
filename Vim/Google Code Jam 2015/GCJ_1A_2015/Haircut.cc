#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

#define INF 10000000000000000LL

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll B, N;
        cin >> B >> N;

        vi M(B);
        for (ll i = 0; i < B; ++i) {
            cin >> M[i];
        }

        ll lo = 0, hi = INF;
        ll ans;
        while (true) {
            ll mid = (hi+lo)/2;

            ll count = 0;
            for (ll i = 0; i < B; ++i) {
                ll times = (mid + M[i]-1) / M[i];
                count += times;
            }

            if (count < N) {
                for (ll i = 0; i < B; ++i) {
                    ll times = mid / M[i];
                    if (times * M[i] == mid) {
                        ++count;
                        ans = i;
                        if (count == N) {
                            goto END;
                        }
                    }
                }
            }

            if (count < N) lo = mid;
            else hi = mid;
        }
END:
        
        printf("Case #%lld: %lld\n", cs, ans+1);
    }

    return 0;
}
