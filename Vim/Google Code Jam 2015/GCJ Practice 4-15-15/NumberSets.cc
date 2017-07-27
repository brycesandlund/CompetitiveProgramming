#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

ll find(vi &UF, ll i) { return UF[i] == i ? i : UF[i] = find(UF, UF[i]); }

void merge(vi &UF, ll i, ll j) { UF[find(UF, i)] = find(UF, j); }

int main() {
    ll C;
    cin >> C;
    
    for (ll cs = 1; cs <= C; ++cs) {
        ll A, B, P;

        cin >> A >> B >> P;

        vb sieve(B-A+1, true);
        for (ll i = 2; i < sieve.size(); ++i) {
            if (sieve[i]) {
                for (ll j = i*2; j < sieve.size(); j += i) {
                    sieve[j] = false;
                }
            }
        }

        vi UF(B-A+1);
        for (ll i = 0; i < UF.size(); ++i) {
            UF[i] = i;
        }

        for (ll i = P; i < sieve.size(); ++i) {
            if (sieve[i]) {
                for (ll j = ((A+i-1)/i)*i; j <= B; j += i) {
                    merge(UF, ((A+i-1)/i)*i - A, j - A);
                }
            }
        }

        set<ll> unique;
        for (ll i = 0; i < UF.size(); ++i) {
            unique.insert(find(UF, i));
        }

        printf("Case #%lld: %lld\n", cs, (ll)unique.size());
    }
    return 0;
}
