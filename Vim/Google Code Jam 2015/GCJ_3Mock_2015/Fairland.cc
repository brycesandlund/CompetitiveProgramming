#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;

ll N, D;

void activate(ll curMin, ll idx, vvi &children, vb &active, vi &M, vi &S, ll &activeCount) {
    stack<ll> future;
    future.push(idx);
    while (!future.empty()) {
        ll cur = future.top();
        future.pop();

        if (active[cur])
            continue;
        if (M[cur] != -1 && !active[M[cur]])
            continue;
        if (S[cur] >= curMin && S[cur] <= curMin+D) {
            active[cur] = true;
            ++activeCount;
            for (ll i = 0; i < children[cur].size(); ++i) {
                future.push(children[cur][i]);
            }
        }
    }
}

void deactivate(ll curMin, ll idx, vvi &children, vb &active, vi &M, vi &S, ll &activeCount) {
    stack<ll> future;
    future.push(idx);
    while (!future.empty()) {
        ll cur = future.top();
        future.pop();

        if (!active[cur])
            continue;
        active[cur] = false;
        --activeCount;
        for (ll i = 0; i < children[cur].size(); ++i) {
            future.push(children[cur][i]);
        }
    }
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        cin >> N >> D;

        vi S(N), M(N);

        ll As, Cs, Rs;
        cin >> S[0] >> As >> Cs >> Rs;

        ll Am, Cm, Rm;
        cin >> M[0] >> Am >> Cm >> Rm;

        for (ll i = 1; i < N; ++i) {
            S[i] = (S[i-1] * As + Cs) % Rs;
            M[i] = (M[i-1] * Am + Cm) % Rm;
        }

        vvi children(N);
        for (ll i = 1; i < N; ++i) {
            M[i] = M[i] % i;
            children[M[i]].push_back(i);
        }

        M[0] = -1;

        vvi salaries(Rs+D);
        for (ll i = 0; i < N; ++i) {
            salaries[S[i]].push_back(i);
        }

        vb active(N, false);
        ll activeCount = 0;
        ll best = -1;
        for (ll curMin = -D; curMin <= Rs-D-1; ++curMin) {
            for (ll i = 0; i < salaries[curMin+D].size(); ++i) {
                activate(curMin, salaries[curMin+D][i], children, active, M, S, activeCount);
            }
            if (curMin-1 >= 0) {
                for (ll i = 0; i < salaries[curMin-1].size(); ++i) {
                    deactivate(curMin, salaries[curMin-1][i], children, active, M, S, activeCount);
                }
            }
            if (active[0]) {
                best = max(best, activeCount);
            }
        }

        printf("Case #%lld: %lld\n", cs, best);
    }
    return 0;
}
