#include <iostream>
#include <vector>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<ll> vi;


ll cross(ii pt1, ii pt2) {
    return pt1.first*pt2.second - pt1.second*pt2.first;
}

ll isLeft(ii a, ii b, ii c) {
    ii bma = ii(b.first-a.first,b.second-a.second);
    ii cma = ii(c.first-a.first,c.second-a.second);
    double z = cross(bma, cma);
    if (abs(z) < EP) return 0;
    else if (z > 0) return 1;
    else return -1;
}

ll WindingNumber(vii &p, ii q) {
    ll wn = 0;
    vi state(p.size());
    for (ll i = 0; i < p.size(); ++i) {
        if (abs(p[i].second - q.second) < EP) state[i] = 0;
        else if (p[i].second < q.second) state[i] = -1;
        else state[i] = 1;
    }
    for (ll i = 1; i < p.size(); ++i) if(state[i] == 0) state[i] = state[i-1];
    if (state[0] == 0) state[0] = state.back();
    for (ll i = 1; i < p.size(); ++i) if (state[i] == 0) state[i] = state[i-1];
    for (ll i = 0; i < p.size(); ++i) {
        ll z = (i+1) % p.size();
        if (state[z] == state[i]) continue;
        else if (state[z] == 1 && isLeft(p[i],p[z],q) > 0) ++wn;
        else if (state[i] == 1 && isLeft(p[i],p[z],q) < 0) --wn;
    }
    cerr << wn << endl;
    return wn < 0 ? -wn : wn;
}

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {
        vii vertices(n);
        for (ll i = 0; i < n; ++i) {
            cin >> vertices[i].first >> vertices[i].second;
        }

        ii P;
        cin >> P.first >> P.second;

        ll wn = WindingNumber(vertices, P);
        if (wn == 0) cout << "F" << endl;
        else cout << "T" << endl;
    }
    return 0;
}
