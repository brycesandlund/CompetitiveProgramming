#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<double> vd;

ll next_match(string target) {
    for (ll i = 1; i < target.size(); ++i) {
        bool success = true;
        for (ll j = 0; j+i < target.size(); ++j) {
            if (target[i+j] != target[j]) {
                success = false;
                break;
            }
        }
        if (success)
            return target.size()-i;
    }
    return 0;
}

ll max_matches(string target, ll S, ll i, ll nm) {
    ll charMatch = (target.size()-i);
    if (charMatch > S)
        return 0;
    else
        return 1 + max_matches(target, S - charMatch, nm, nm);
}

double E(ll i, ll n, string &keyboard, string &target, ll nm) {
    for (ll j = 0; j < keyboard.size(); ++j) {
        if (target[i] == keyboard[j]) {
            return 1.0/keyboard.size() * E(i+1, n-1, keyboard, target, nm);
        }
        else {
            
        }
    }
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll K, L, S;
        cin >> K >> L >> S;

        string keyboard;
        cin >> keyboard;
        string target;
        cin >> target;
        ll nm = next_match(target);

        
    }
    return 0;
}
