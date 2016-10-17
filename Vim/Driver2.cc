#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll N;
    cin >> N;
    vi C(N-1);
    for (ll i = 0; i < N-1; ++i) {
        cin >> C[i];
    }
    
    vi T(N);
    for (ll i = 0; i < N; ++i) {
        cin >> T[i];
        if (i % 2 != T[i] % 2)
            ++T[i];
    }

    ll cost = 0;
    for (ll i = 0; i < N-1; ++i)
        cost += C[i];   // we must pass through each edge once

    ll minIdx = 0;
    ll place = 0;
    ll time = 0;
    for (; place < N; ++time) {
        if (time >= T[place]) {
            if (C[place] < C[minIdx]) {
                minIdx = place;
            }
            ++place;
        }
        else
            cost += C[minIdx];
    }

    cout << cost << endl;

    return 0;
}
