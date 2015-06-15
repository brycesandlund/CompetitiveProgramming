#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n;
    cin >> n;
    string rooms;
    cin >> rooms;

    ll needToBuy = 0;
    vi keys(26, 0);

    for (ll i = 0; i < rooms.size(); ++i) {
        if (i % 2 == 0) {
            ++keys[rooms[i] - 'a'];
        }
        else {
            if (keys[rooms[i] - 'A'] > 0)
                --keys[rooms[i] - 'A'];
            else
                ++needToBuy;
        }
    }

    cout << needToBuy << endl;

    return 0;
}
