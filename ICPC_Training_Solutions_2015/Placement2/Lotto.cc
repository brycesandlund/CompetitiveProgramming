#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;

int main() {
    ll N;
    for (ll cs = 1; cin >> N && N; ++cs) {
        vb tickets(50, false);
        for (ll i = 0; i < N*6; ++i) {
            ll ticket_num;
            cin >> ticket_num;

            tickets[ticket_num] = true;
        }

        bool all_present = true;
        for (ll i = 1; i <= 49; ++i) {
            if (!tickets[i])
                all_present = false;
        }

        if (all_present)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
