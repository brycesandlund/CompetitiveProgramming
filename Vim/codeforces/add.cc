#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll solve(vi &a, ll place, ll sum, ll n) {
    if (place == n)
        return sum;
   
    sum += a[place]; 
    stringstream ss;
    ss << sum;
    string str;
    ss >> str;

    ll maxSolution = 0;
    int perms[5] = {0,1,2,3,4};
    do {
        stringstream ss2;
        for (ll i = 0; i < (ll)str.size(); ++i) {
            ss2 << str[perms[i]];
        }

        ll num;
        ss2 >> num;

        maxSolution = max(maxSolution, solve(a, place+1, num, n));
    } while(next_permutation(perms, perms+str.size()));

    return maxSolution;
}

int main() {
    ll n;
    cin >> n;

    vi a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    cout << solve(a, 0, 0, n) << endl;
}
