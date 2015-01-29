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

int main()
{
    #ifdef __FIO
    freopen("in.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif
    int T, i0;
    scanf("%d", &T);
    for(i0 = 1; i0 <= T; i0++){
        ll n, k, p;
        ll pre, i;
        ll ans;
        cin >> n >> k >> p;
        i = n%k;
        if(i == 0)
            i = k;
        if(p == 100){
            pre = i;
        }
        else{
            while(i <= n){
                pre = i;
                i += (i*p-1) / (100-p) + 1;
                if((i-pre)%k != 0)
                    i += k-(i-pre)%k;
            }
        }
        ans = 1+(n-pre)/k;
        printf("Case #%d: %lld\n", i0, ans);
    }
    return 0;
}
