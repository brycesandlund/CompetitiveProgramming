#include <iostream>
#include <vector>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll cuberoot(ll n) {
    double root = pow(n, 1.0/3);
    return (ll)(root + EP);
}

ii best(ll n) {
    ll root = cuberoot(n);
    ii ans1 = best(n-root);
    ans1.first++;
    ii ans2 = best(root*root*root-1);
    
    if (ans2.first > ans1.first) {
        return ans2;
    }
    else {
        return ii(ans1.first+1, ans1.second + root*root*root);
    }
}

int main() {
}
