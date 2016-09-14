#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    string AI, phone;
    cin >> ws >> AI >> ws >> phone;
    
    ll ans = 0;
    for (ll i = 0; i <= (ll)AI.size() - (ll)phone.size(); ++i) {
        bool match = true;
        for (ll j = 0; j < phone.size(); ++j) {
            if (AI[i+j] != phone[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            AI[i + phone.size() - 1] = '#';
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}
