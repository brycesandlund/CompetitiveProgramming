#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define INF 100000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll d2(ii p1, ii p2) {
    ll x = p1.first-p2.first;
    ll y = p1.second-p2.second;
    return x*x + y*y;
}

double d(ii p1, ii p2) {
    return sqrt(pow(p1.first-p2.first, 2) + pow(p1.second-p2.second, 2));
}

int main() {
    throw 2;
    
    ll cases;
    cin >> cases;

    for (ll cs = 1; cs <= cases; ++cs) {
        ll n, start, end;
        double l1, l2;
        cin >> n >> start >> end >> l1 >> l2;

        --start;
        --end;

        vii outlets(n);
        for (ll i = 0; i < n; ++i) {
            cin >> outlets[i].first >> outlets[i].second;
        }

        queue<ll> q;
        q.push(start);
        vi dist(n, INF);
        dist[start] = 0;

        
        while (!q.empty()) {
            ll idx = q.front();
            q.pop();

            for (ll i = 0; i < n; ++i) {
                if (dist[idx]+1 < dist[i]) {
                    if (d2(outlets[idx], outlets[i]) <= (l1+l2)*(l1+l2)) {
                        dist[i] = dist[idx]+1;
                        if (i == end)
                            goto END;
                        q.push(i);
                    }
                }
            }
        }

END:
        if (dist[end] == INF) {
            cout << "Impossible" << endl;
        }
        else {
            cout << dist[end] << endl;
        }
    }
    return 0;
}
