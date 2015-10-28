#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll LSB(ll a) { return a ^ (a & (a-1)); }

struct BIT {
    ll N;
    vi A;
    BIT(ll n) : N(n), A(N+1, 0) {}

    void add(ll idx, ll v) {
        for (ll i = idx+1; i <= N; i += LSB(i)) A[i] += v;
    }

    ll sum(ll idx) {
        ll ret = 0;
        for (ll i = idx+1; i > 0; i -= LSB(i)) ret += A[i];
        return ret;
    }

    ll sum_range(ll l, ll r) { return sum(r) - sum(l-1); }

    void set(ll idx, ll v) {
        ll val = sum_range(idx, idx);
        add(idx, v-val);
    }
};

int main() {
    ll N;
    for (ll cs = 1; scanf("%lld", &N) && N; ++cs) {
        BIT ft(1 << 18);
        for (ll i = 0; i < N; ++i) {
            ll val;
            scanf("%lld", &val);
            ft.add(i+1, val);
        }

        if (cs != 1) {
            printf("\n");
        }
        printf("Case %lld:\n", cs);
        while (true) {
            char c;
            scanf("%c", &c);
            if (c == 'S') {
                ll x, r;
                scanf("%lld %lld", &x, &r);
                ft.set(x, r);
            }
            else if (c == 'M') {
                ll x, y;
                scanf("%lld %lld", &x, &y);
                printf("%lld\n", ft.sum_range(x, y));
            }
            else if (c == 'E') {
                scanf("%c", &c);
                scanf("%c", &c);
                break;
            }
        }
    }
}
