#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;

iii dc(vi &seq, ll start, ll end, ll k) {
    if (start == end)
        return iii(seq[start], ii(start, end));

    ll mid = (start+end)/2;
    iii left = dc(seq, start, mid, k);
    iii right = dc(seq, mid+1, end, k);

    ll left = mid, right = mid+1;
    ll sum = 
}

int main() {
    
    return 0;
}
