#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;

ll dx[4] = {1, 0, -1, 0};
ll dy[4] = {0, -1, 0, 1};

ii endlocation(vs &direction) {
    ll x = 0, y = 0;
    ll orientation = 3;
    for (ll i = 0; i < direction.size(); ++i) {
        if (direction[i] == "Forward") {
            x += dx[orientation];
            y += dy[orientation];
        }
        else if (direction[i] == "Right") {
            ++orientation;
        }
        else {
            --orientation;
        }
        orientation = (orientation + 4) % 4;
    }
    return ii(x, y);
}

int main() {
    ll x, y;
    cin >> x >> y;
    ll n;
    cin >> n;

    vs direction(n);
    for (ll i = 0; i < n; ++i) {
        cin >> direction[i];
    }

    string move[3] = {"Forward", "Right", "Left"};
    for (ll i = 0; i < n; ++i) {
        string prev = direction[i];
        for (ll j = 0; j < 3; ++j) {
            direction[i] = move[j];
            ii result = endlocation(direction);
            
            if (result == ii(x, y)) {
                cout << i+1 << " " << move[j] << endl;
                return 0;
            }
        }
        direction[i] = prev;
    }
}
