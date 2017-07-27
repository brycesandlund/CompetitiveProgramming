#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<double> vd;
        
ll H, S;

double process_spell() {
    ll X, Y, Z = 0;
    char c;
    scanf("%lldd%lld%c", &X, &Y, &c);
    if (c == '+' || c == '-') {
        cin >> Z;
        if (c == '-')
            Z *= -1;
    }

    vd odds(410, 0);
    odds[0] = 1;

    for (ll i = 0; i < X; ++i) {
        vd new_odds(410, 0);
        for (ll j = 1; j <= Y; ++j) {
            for (ll k = 0; k < 410-j; ++k) {
                new_odds[k+j] += odds[k] * (1.0/Y);
            }
        }
        odds = new_odds;
    }

    double winning = 0;
    for (ll i = 0; i < 410; ++i) {
        if (i + Z >= H) {
            winning += odds[i];
        }
    }

    return winning;
}

int main() {
    ll T;
    cin >> T;
    
    for (ll cs = 1; cs <= T; ++cs) {
        cin >> H >> S;
        
        double p_max = 0;
        for (ll i = 0; i < S; ++i) {
            p_max = max(p_max, process_spell());
        }
        printf("Case #%lld: %.10lf\n", cs, p_max);
    }
}
