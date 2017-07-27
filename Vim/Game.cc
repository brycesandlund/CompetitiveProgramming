#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

void clear(ii pair, unorderd_map<ll, list<ii> > mp) {
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        it->second.remove(pair);
    }
}
    
unordered_map<ll, list<ii> > product, sum;

int main() {
    ll N, M;
    cin >> N >> M;

    for (ll i = 1; i <= N; ++i) {
        for (ll j = i+1; j <= N; ++j) {
            if (!product.count(i*j)) {
                product[i*j] = list();
            }
            product[i*j].push_back(ii(i, j));

            if (!sum.count(i+j)) {
                sum[i+j] = list();
            }
            sum[i+j].push_back(ii(i, j));
        }
    }

    for (ll i = 0; i < M; ++i) {
        if (i % 2 == 0) {
            for (auto it = sum.begin(); it != sum.end(); ++it) {
                if (it->size() == 1) {
                    ii nums = it->front();
                }
            }
        }
    }
    return 0;
}
