#include <iostream>
#include <vector>

using namespace std;

typedef int ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

class ApplesAndOrangesEasy {
    public:
    int maximumApples(int &N, int &K, vector<int> &info) {
        vb apple(N, false);
        for (ll i = 0; i < info.size(); ++i) {
            apple[info[i]-1] = true;
        }

        for (ll i = 0; i < N; ++i) {
            ll appleCount = 0;
            for (ll j = max(0, i-K+1); j < i; ++j) {
                if (apple[j]) {
                    ++appleCount;
                }
            }

            if (appleCount < K/2)
                apple[i] = true;
        }

        ll numApples = 0;
        for (ll i = 0; i < N; ++i)
            if (apple[i])
                ++numApples;

        return numApples;
    }
};

int main() {
}
