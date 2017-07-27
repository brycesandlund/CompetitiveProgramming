#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

#define INF 1000000000000000000LL

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
            vi total(B);
            ll maxTotal = -1;
            ll maxIdx;
            for (ll i = 0; i < B; ++i) {
                ll times = mid / M[i];
                if (times * M[i] < mid) {
                    count += times;
                }
                else {
                    count += times-1;
                }
                
                total[i] = times*M[i];

                if (total[i] > maxTotal) {
                    maxTotal = total[i];
                    maxIdx = i;
                }
            }

            for (ll i = 0; i < B; ++i) {
                if (total[i] == mid && count < N) {
                    ++count;
                    maxIdx = i;
                }
            }

            if (count == N) {
                for (ll i = 0; i < B; ++i) {
                    ll times = mid / M[i];
                }


                cerr << mid << endl;
                ans = maxIdx+1;
                break;
            }
            else if (count < N) lo = mid;
            else hi = mid;
        }
        
        printf("Case #%lld: %lld\n", cs, ans);
    }

    return 0;
}
