#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

ll find(vs &strings, string str) {
    for (ll i = 0; i < strings.size(); ++i) {
        if (strings[i] == str)
            return i;
    }
    return -1;
}

bool can(string &one, string &two) {
    if (one.size() != two.size())
        return false;
    
    bool diffused = false;
    for (ll i = 0; i < one.size(); ++i) {
        if (one[i] != two[i]) {
            if (diffused)
                return false;
            diffused = true;
        }
    }
    return true;
}

int main() {
    ll L;
    for (ll cs = 1; cin >> L; ++cs) {
        ll Q;
        cin >> Q;

        vs d(L);
        for (ll i = 0; i < L; ++i) {
            cin >> d[i];
        }

        for (ll i = 0; i < Q; ++i) {
            string one, two;
            cin >> one >> two;
            
            ll start = find(d, one);
            ll end = find(d, two);

            if (start == -1 || end == -1) {
                cout << -1 << endl;
                continue;
            }

            queue<ll> q;
            q.push(start);
            vi dist(L, INF);
            dist[start] = 0;

            while (!q.empty()) {
                ll idx = q.front(); q.pop();

                if (idx == end) {
                    break;
                }

                for (ll i = 0; i < L; ++i) {
                    if (can(d[idx], d[i])) {
                        if (dist[idx]+1 < dist[i]) {
                            dist[i] = dist[idx]+1;
                            q.push(i);
                        }
                    }
                }
            }

            if (dist[end] == INF)
                cout << -1 << endl;
            else
                cout << dist[end] << endl;
        }
    }
    return 0;
}
