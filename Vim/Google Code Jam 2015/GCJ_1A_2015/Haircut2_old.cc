#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll B, N;
        cin >> B >> N;

        vi M(B);
        ll prod = 1;
        for (ll i = 0; i < B; ++i) {
            cin >> M[i];
            prod *= M[i];
        }

        cerr << "here2" << endl;

        cerr << prod << endl;
        N %= prod;

        cerr << "here" << endl;

        priority_queue<ii, vii, greater<ii> > q;
        for (ll i = 0; i < B; ++i) {
            q.push(ii(0, i));
        }

        for (ll i = 0; i < N-1; ++i) {
            ii cur = q.top();
            q.pop();

            q.push(ii(cur.first + M[cur.second], cur.second));
        }

        ll ans = q.top().second + 1;
        printf("Case #%lld: %lld\n", cs, ans);
    }

    return 0;
}
