#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    vi male(1, 0);
    vi female(1, 1);

    for (ll i = 0; male[i] < (1LL << 32) && female[i] < (1LL << 32); ++i) {
        male.push_back(male[i] + female[i]);
        female.push_back(male[i] + 1);
    }

    ll N;

    for (ll cs = 1; cin >> N && N != -1; ++cs) {
        cout << male[N] << " " << male[N]+female[N] << endl;
    }
    return 0;
}
