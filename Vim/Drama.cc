#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <functional>
#include <cmath>

#define M 1000000007LL
#define INF 1000000000000000000
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main() {
    ll H, N;
    cin >> H >> N;

    vb fullpyramid(N+1, false);
    for (ll i = 0; i <= H; ++i) {
        ll result = i*(i+1)/2;
        if (result > N)
            break;
        else
            fullpyramid[result] = true;
    }

    H = min(H, (ll)(2*sqrt(N)+1));

    vvi DP(H+1, vi(N+1, 1));
    vvi uni(H+1, vi(N+1, 1));
    for (ll i = H; i < H+1; ++i) {
        for (ll j = 2; j < N+1; ++j) {
            DP[i][j] = (DP[i][j-1] + uni[i][j-1]-1 + fullpyramid[j]) % M;
            uni[i][j] = uni[i][j-1] + fullpyramid[j];
        }
    }

    for (ll i = 1; i <= N; ++i)
        cout << DP[H][i] << " ";
    cout << endl;

    cout << DP[H][N] << endl;
}
