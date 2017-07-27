#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll n, a, b, T;

vi solve(string orient, bool first) {
    vi time(n+1);
    time[0] = 0;
    for (ll i = 0; i < orient.size(); ++i) {
        time[i+1] = time[i] + 1 + ((i == 0 && first) ? 0 : a) + (orient[i] == 'w' ? b : 0);
    }
    return time;
}

ll objective(vi &forward, vi &backward, ll f_pt, ll b_pt) {
    return forward[f_pt] + backward[b_pt] + (b_pt * a);
}

void combine(vi &forward, vi &backward, ll &best) {
    ll f_pt = (upper_bound(forward.begin(), forward.end(), T) - forward.begin());
    --f_pt;

    ll b_pt = 0;
    for (; f_pt >= 0; --f_pt) {
        while (objective(forward, backward, f_pt, b_pt) <= T) {
            ++b_pt;
        }
        --b_pt;

        if (f_pt > 0)
            best = max(best, f_pt + b_pt);
    }
}

int main() {
    cin >> n >> a >> b >> T;
    
    string orient;
    cin >> orient;

    vi forward = solve(orient, true);



    if (forward[n] <= T) {
        cout << n << endl;
    }
    else {
        string r_orient_not_1(orient.rbegin(), orient.rend());
        string orient_not_1 = orient.substr(1) + orient.substr(0, 1);
        string r_orient(orient_not_1.rbegin(), orient_not_1.rend());
        
        vi backward_not_1 = solve(r_orient_not_1, false);
        vi forward_not_1 = solve(orient_not_1, false);
        vi backward = solve(r_orient, true);

        ll best = 0;
        combine(forward, backward_not_1, best);
        combine(backward, forward_not_1, best);
    
        cout << best << endl;
    }

    return 0;
}
