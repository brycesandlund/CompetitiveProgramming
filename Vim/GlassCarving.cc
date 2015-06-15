#include <iostream>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

void apply(set<ll> &cuts, multiset<ll> &gaps, ll cut) {
    cuts.insert(cut);
    set<ll>::iterator it = cuts.find(cut);
    --it;
    ll lower = *it;
    ++it;
    ++it;
    ll higher = *it;
    ll prevGap = higher-lower;

    gaps.erase(gaps.find(prevGap));
    gaps.insert(cut-lower);
    gaps.insert(higher-cut);
}

int main() {
    ll w, h, n;
    cin >> w >> h >> n;

    set<ll> x_cuts;
    set<ll> y_cuts;
    multiset<ll> x_gaps;
    multiset<ll> y_gaps;

    x_cuts.insert(0);
    x_cuts.insert(w);
    y_cuts.insert(0);
    y_cuts.insert(h);

    x_gaps.insert(w);
    y_gaps.insert(h);

    for (ll i = 0; i < n; ++i) {
        char c;
        ll cut;
        cin >> ws >> c >> cut;

        if (c == 'H') {
            apply(y_cuts, y_gaps, cut);
        }
        else {
            apply(x_cuts, x_gaps, cut);
        }

        cout << *x_gaps.rbegin() * *y_gaps.rbegin() << endl;
    }

    return 0;
}
