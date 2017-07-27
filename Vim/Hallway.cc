#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

string gen_string(ll n) {
    if (n == 1)
        return "L";

    string smaller = gen_string(n-1);
    string result(smaller.size()*2 + 1, 'x');
    
    result[0] = 'L';
    for (ll i = 0; i < smaller.size(); ++i) {
        result[i*2+1] = smaller[i];
        
        if (i % 2 == 0) {
            result[i*2+2] = 'R';
        }
        else {
            result[i*2+2] = 'L';
        }
    }

    return result;
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll n;
        string S;
        cin >> n >> S;
        n = min(n, 10LL);

        string code = gen_string(n);

        if (code.find(S) != string::npos) {
            printf("Case %lld: Yes\n", cs);
        }
        else {
            printf("Case %lld: No\n", cs);
        }
    }
}
