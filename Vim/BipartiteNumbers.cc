#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <set>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a < 0) {
        ll r = egcd(-a, b, x, y);
        x *= -1;
        return r;
    }
    if (b < 0) {
        ll r = egcd(a, -b, x, y);
        y *= -1;
        return r;
    }
    ll u = y = 0, v = x = 1;
    while (b) {
        ll q = a/b, r = a % b;
        a = b, b = r;
        ll m = u, n = v;
        u = x - q*u, v = y - q*v;
        x = m, y = n;
    }
    return a;
}

ll modinv(ll a, ll n) {
    ll x, y, g = egcd(a, n, x, y);
    if (g != 1) return -1;
    x %= n;
    if (x < 0) x +=n;
    return x;
}

ll modsolve(ll a, ll b, ll n, vi &S) {
    ll blah1, blah2;
    ll g = egcd(a, n, blah1, blah2);
    if (b % g == 0) {
        ll x = modinv(a/g, n/g);
        x = (x * b/g) % (n/g);
        for (ll k = 0; k < g; ++k)
            S.push_back((x + k*(n/g)) % n);
        return g;
    }
    return 0;
}

bool better(ll m, ll s, ll n, ll t, ll mn, ll sn, ll nn, ll tn) {
    if (m+n == mn+nn) {
        if (s == sn) {
            if (m == mn) {
                return tn < t;
            }
            else if (m < mn)
                return sn < t;
            else
                return tn < s;
        }
        else if (s > sn)
            return true;
        else
            return false;
    }
    else if (m+n > mn+nn)
        return true;
    else
        return false;
}

ll powMod(ll x, ll e, ll m) {
    if (e == 0) {
        return 1;
    }
    else if (e % 2 == 0) {
        ll smaller = powMod(x, e/2, m);
        return (smaller * smaller) % m;
    }
    else
        return (x * powMod(x, e-1, m)) % m;
}

ll getNum(ll d, ll n) {
    return d * ((powMod(10, n, INF) - 1)/9);
}

bool same(ll num, ll m, ll s, ll n, ll t) {
    if (m+n >= 6) return false;

    ll newNum = getNum(s, m) * powMod(10, n, INF) + getNum(t, n);
    return newNum == num;
}

int main() {
    for (ll cs = 1; true; ++cs) {
        ll num;
        cin >> num;

        if (num == 0) break;

        vector<set<ii> > best(num);

        vi cycleStart(10);

        vvi step(10);
        priority_queue<ii, vii, greater<ii> > pq;

        for (ll d = 0; d < 10; ++d) {
            ll val = d % num;
            ll curLen = 1;
            map<ll, ll> seen;
            while(true) {
                if (seen.count(val)) {
                    cycleStart[d] = seen[val];
                    break;
                }
                
                seen[val] = curLen-1;
                pq.push(ii(curLen, d));
                step[d].push_back(val);

                best[val].insert(ii(curLen, d));

                val = (val*10 + d) % num;
                ++curLen;
            }

        }

        vi digit(num, -1);
        vi length(num, -1);
        
        vi digit2(num, -1);
        vi length2(num, -1);

        for (ll i = 0; i < num; ++i) {
            for (set<ii>::iterator it = best[i].begin(); it != best[i].end(); ++it) {
                if (it->second != 0) {
                    if (digit[i] == -1) {
                        length[i] = it->first;
                        digit[i] = it->second;
                    }
                    else if (it->second != digit[i]) {
                        length2[i] = it->first;
                        digit2[i] = it->second;
                    }
                }
            }
        }

        ll m = INF, s = INF, n = INF, t = INF;

        while (true) {
            ii cur = pq.top(); pq.pop();
            
            ll nn = cur.first;
            ll tn = cur.second;

            if (nn > m+n) break;

            vi S;
            ll a = powMod(10, nn, num);
            ll cycleL = step[tn].size() - cycleStart[tn];
            
            ll idx = (nn-1) >= step[tn].size() ? (step[tn].size()-cycleL + (nn-1)%cycleL) : (nn-1);
            
            ll C = step[tn][idx];
            ll b = (num - C)%num;

            modsolve(a, b, num, S);

            for (ll i = 0; i < S.size(); ++i) {
                ll mn = length[S[i]];
                ll sn = digit[S[i]];

                if (sn != -1) {
                    if (sn == tn || same(num, mn, sn, nn, tn)) {
                        mn = length2[S[i]];
                        sn = digit2[S[i]];

                        if (mn == -1 || same(num, mn, sn, nn, tn))
                            continue;
                    }

                    if (better(m, s, n, t, mn, sn, nn, tn)) {
                        m = mn; s = sn; n = nn; t = tn;
                    }
                }
            }

            if (S.size() > 0 && idx >= cycleStart[tn])
                pq.push(ii(nn + cycleL, tn));
        }

        printf("%lld: %lld %lld %lld %lld\n", num, m, s, n, t);
    }
}
