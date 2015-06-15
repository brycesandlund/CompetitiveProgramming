#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<vvd> vvvd;

vvvd state;
ll r_max, s_max, p_max;

double probDie(ll indifferent, ll good, ll bad) {
    ll totalP = indifferent * good + indifferent * bad + good * bad;
    
    if (totalP == 0)
        return 0;

    return (double)(good*bad) / totalP;
}

double prob(ll r, ll s, ll p) {
    if (state[r][s][p] != -1) {
        return state[r][s][p];
    }

    if (r > r_max || s > s_max || p > p_max)
        return 0;

    state[r][s][p] = 0;
    double pStateRdies = prob(r+1, s, p);
    state[r][s][p] += pStateRdies * probDie(s, r+1, p);

    double pStateSdies = prob(r, s+1, p);
    state[r][s][p] += pStateSdies * probDie(p, s+1, r);

    double pStatePdies = prob(r, s, p+1);
    state[r][s][p] += pStatePdies * probDie(r, p+1, s);

    return state[r][s][p];
}

int main() {
    cin >> r_max >> s_max >> p_max;
    state = vvvd(110, vvd(110, vd(110, -1)));
    state[r_max][s_max][p_max] = 1;

    double pr = 0;
    for (ll i = 1; i <= r_max; ++i) {
        pr += prob(i, 0, 0);
    }

    double ps = 0;
    for (ll i = 1; i <= s_max; ++i) {
        ps += prob(0, i, 0);
    }

    double pp = 0;
    for (ll i = 1; i <= p_max; ++i) {
        pp += prob(0, 0, i);
    }

    cout << fixed;
    cout << setprecision(12);

    cout << pr << " " << ps << " " << pp << endl;
    return 0;
}
