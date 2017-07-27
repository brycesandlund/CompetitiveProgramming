#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N, K;
        cin >> N >> K;
        vi sum(N-K+1);
        for (ll i = 0; i < sum.size(); ++i) {
            cin >> sum[i];
        }

        ll biggestDiff = -1;
        vi minDiff(K, 0);
        vi maxDiff(K, 0);
        ll target = sum[0];
        for (ll i = 0; i < K; ++i) {
            ll curDiff = 0;
            for (ll j = i; j+1 < sum.size(); j += K) {
                curDiff += sum[j+1]-sum[j];
                minDiff[i] = min(minDiff[i], curDiff);
                maxDiff[i] = max(maxDiff[i], curDiff);
            }

            target += minDiff[i];
            //cerr << minDiff << " " << maxDiff << endl;
            biggestDiff = max(biggestDiff, maxDiff[i] - minDiff[i]);
        }

        ll nFree = 0;
        for (ll i = 0; i < K; ++i) {
            nFree += biggestDiff - (maxDiff[i] - minDiff[i]);
        }

        if (target < 0) {
            target = target + K * ((-target + K-1) / K);
        }

        ll ans;
        if (target % K > nFree)
            ans = biggestDiff+1;
        else
            ans = biggestDiff;

        //cerr << target << " " << nFree << endl;

        printf("Case #%lld: %lld\n", cs, ans);
    }
    return 0;
}
