#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double du;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FOR(i, s, t) for(i = (s); i < (t); i++)
#define RFOR(i, s, t) for(i = (s)-1; i >= (t); i--)

int a[104];

int main()
{
    #ifdef __FIO
    freopen("in.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif
    int T, i0;
    scanf("%d", &T);
    for(i0 = 1; i0 <= T; i0++){
        int n;
        ll ans = 1;
        int i, j;
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for(i = 0; i < n; i++)
            ans += a[i]*(a[i]-1)/2+1;
        for(i = 0; i < n; i++)
            for(j = i+1; j < n; j++)
                ans += (a[i]+1)*(a[j]+1);
        printf("Case #%d: %lld\n", i0, ans);
    }
    return 0;
}
