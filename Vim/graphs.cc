#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

char c[500][500];

int main() {
    ll N;
    cin >> N;

    for (ll cs = 1; cs <= N; ++cs) {
        ll H, W;
        cin >> H >> W;

        for (ll i = 0; i < H; ++i) {
            for (ll j = 0; j < W; ++j) {
                cin >> c[i][j];
            }
        }
    }
}
