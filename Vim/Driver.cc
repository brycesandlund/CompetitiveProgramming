#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll N;
    cin >> N;
    vi C(N);
    for (ll i = 0; i < N-1; ++i) {
        cin >> C[i];
    }
    
    C[N-1] = 0;

    vi T(N);
    for (ll i = 0; i < N; ++i)
        cin >> T[i];

    ll cost = 0;
    for (ll i = 0; i < N-1; ++i)
        cost += C[i];   // we must pass through each edge once

    ll lastStop = 0;
    ll lastTime = 0;
    for (ll i = 0; i < N; ++i) {
        if (C[i] < C[lastStop]) {
            ll dist = i-lastStop;
            ll nCircles = 0;
            if (T[i] - dist > lastTime) {
                nCircles = (T[i]-dist-lastTime+1LL)/2LL;    // round up
            }
            cost += nCircles * C[lastStop] * 2LL;
            lastStop = i;
            lastTime += dist + nCircles*2LL;
        }
    }

    cout << cost << endl;

    return 0;
}
