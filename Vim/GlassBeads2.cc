#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

#define MAX_N 100010

void countingSort(int k, vi &SA, vi &RA) {
    int n = SA.size();
    int i, sum, maxi = max(300, n);
    vi c(maxi, 0), tempSA(n);
    for (i = 0; i < n; i++)
        c[i+k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++)
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void constructSA(string T, vi &SA) {
    int n = T.size();
    int i, k, r;
    SA = vi(n);
    vi RA(n), tempRA(n);
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i;
    for (k = 1; k < n; k <<= 1) {
        countingSort(k, SA, RA);
        countingSort(0, SA, RA);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++)
            tempRA[SA[i]] = 
                (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;
    }
}


int main() {
    ll N;
    cin >> N;
    for (ll i = 0; i < N; ++i) {
        string line;
        cin >> line;

        vi SA;
        constructSA(line + line + "{", SA);
        cout << SA[0]+1 << endl;
    }
    return 0;
}
