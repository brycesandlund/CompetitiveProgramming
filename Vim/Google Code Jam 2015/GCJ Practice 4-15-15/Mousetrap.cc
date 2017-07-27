#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

//binary indexed tree - taken from Stanford ACM
#define LOGSZ 20

int ft[(1<<LOGSZ)+1];
int N = (1<<LOGSZ);

// add v to value at x
void adjust(int x, int v) {
    while(x <= N) {
        ft[x] += v;
        x += (x & -x);
    }
}

// get cumulative sum up to and including x
int rsq(int x) {
    int res = 0;
    while(x) {
        res += ft[x];
        x -= (x & -x);
    }
    return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
int getind(int x) {
    int idx = 0, mask = N;
    while(mask && idx < N) {
        int t = idx + mask;
        if(x >= ft[t]) {
            idx = t;
            x -= ft[t];
        }
        mask >>= 1;
    }
    return idx;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll K, n;
        cin >> K >> n;
        vi qIndices(n);
        
        for (ll i = 0; i < n; ++i) {
            cin >> qIndices[i];
            --qIndices[i];
        }

        memset(ft, 0, sizeof(ft));
        for (ll i = 1; i <= K; ++i) {
            adjust(i, 1);
        }

        vi numAt(K);
        ll size = K;

        ll curPlace = 0;
        for (ll i = 0; i < K; ++i) {
            ll searchSpot = (curPlace+i) % size;
            ll idx = getind(searchSpot)+1;
            numAt[idx-1] = i+1;
            adjust(idx, -1);
            --size;
            curPlace = searchSpot;
        }

        printf("Case #%lld:", cs);
        for (ll i = 0; i < n; ++i) {
            printf(" %lld", numAt[qIndices[i]]);
        }
        printf("\n");
    }

    return 0;
}
