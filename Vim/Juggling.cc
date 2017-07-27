#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

int main() {
    string pattern;
    for (ll cs = 1; cin >> pattern; ++cs) {
        ll sum = 0;
        for (ll i = 0; i < pattern.size(); ++i) {
            sum += pattern[i] - '0';
        }

        if (sum % pattern.size() != 0) {
            printf("%s: invalid # of balls\n", pattern.c_str());
        }
        else {
            vb taken(pattern.size(), false);
            bool success = true;
            for (ll i = 0; i < pattern.size(); ++i) {
                ll spot = (i + pattern[i] - '0') % pattern.size();
                if (taken[spot]) {
                    success = false;
                    break;
                }
                taken[spot] = true;
            }

            if (success) {
                printf("%s: valid with %lld balls\n", pattern.c_str(), sum/pattern.size());
            }
            else {
                printf("%s: invalid pattern\n", pattern.c_str());
            }
        }
    }
    return 0;
}
