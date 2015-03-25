#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

#define M 1000000007LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;

ll blog(ll num) {
    --num;
    ll count;
    for (count = 0; num > 0; num >>= 1, ++count);
    return count;
}

ll getSum(vi &sum, ll L, ll R) {
    return sum[R] - (L == 0 ? 0 : sum[L-1]);
}

ll getMaxIdx(vvi &maxIdx, vi &H, ll L, ll R) {
    ll lb2 = blog(R-L+1)-1;
    ll range = 1 << lb2;

    if (H[maxIdx[lb2][L]] > H[maxIdx[lb2][R-range+1]]) {
        return maxIdx[lb2][L];
    }
    else {
        return maxIdx[lb2][R-range+1];
    }
}

map<ii, ll> memo;

ll solve(vi &sum, vvi &maxIdx, vi &H, ll Ai, ll Bi, bool Lbound, bool Rbound) {
    if (memo.count(ii(Ai, Bi))) {
        return memo[ii(Ai, Bi)];
    }

    if (Ai == Bi)
        return 0;

    ll ans;
    ll rangeMaxIdx = getMaxIdx(maxIdx, H, Ai, Bi);
    if (!Lbound && !Rbound) {
        ans = (solve(sum, maxIdx, H, Ai, rangeMaxIdx-1, false, true)
                + solve(sum, maxIdx, H, rangeMaxIdx+1, Bi, true, false)) % M;
    }
    else if (Lbound) {
        ans = ((rangeMaxIdx - Ai) * H[rangeMaxIdx] - getSum(sum, Ai+1, rangeMaxIdx-1)) % M;
        ans = (ans + solve(sum, maxIdx, H, rangeMaxIdx+1, Bi, true, false)) % M;
    }
    else {
        ans = ((Bi - rangeMaxIdx) * H[rangeMaxIdx] - getSum(sum, rangeMaxIdx+1, Bi-1)) % M;
        ans = (ans + solve(sum, maxIdx, H, Ai, rangeMaxIdx-1, false, true)) % M;
    }

    return memo[ii(Ai, Bi)] = ans;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        memo.clear();
        
        ll N, Q;
        cin >> N >> Q;

        vi H(N);
        for (ll i = 0; i < N; ++i) {
            cin >> H[i];
        }

        vi sum(N);
        ll sumSoFar = 0;
        for (ll i = 0; i < N; ++i) {
            sumSoFar += H[i];
            sum[i] = sumSoFar;
        }

        vvi maxIdx(blog(N), vi(N, -1));
        for (ll j = 0; j < N; ++j) {
            maxIdx[0][j] = j;
        }

        for (ll i = 1; i < blog(N); ++i) {
            for (ll j = 0; j < N-1; ++j) {
                if (H[maxIdx[i-1][j]] > H[maxIdx[i-1][j+1]]) {
                    maxIdx[i][j] = maxIdx[i-1][j];
                }
                else {
                    maxIdx[i][j] = maxIdx[i-1][j+1];
                }
            }
        }

        cerr << getMaxIdx(maxIdx, H, 0, 10) << endl;

        /*for (ll i = 0; i < Q; ++i) {
            ll Ai, Bi;
            cin >> Ai >> Bi;
            --Ai; --Bi;

            printf("Case #%lld: %lld\n", cs, solve(sum, maxIdx, H, Ai, Bi, false, false));
        }*/
    }
}
