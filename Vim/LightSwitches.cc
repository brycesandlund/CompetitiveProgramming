#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cmath>


using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef set<ll> si;

ll gcd(ll a, ll b) {
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

long long mult_mod(long long a, long long b, long long m) {
    long long q;
    long long r;
    asm(
        "mulq %3;"
        "divq %4;"
        : "=a"(q), "=d"(r)
        : "a"(a), "rm"(b), "rm"(m));
    return r;
}

/* Computes a^b mod m. Assumes 1 <= m <= 2^62-1 and 0^0=1.
 * The return value will always be in [0, m) regardless of the sign of a.
 */
long long pow_mod(long long a, long long b, long long m) {
    if (b == 0) return 1 % m;
    if (b == 1) return a < 0 ? a % m + m : a % m;
    long long t = pow_mod(a, b / 2, m);
    t = mult_mod(t, t, m);
    if (b % 2) t = mult_mod(t, a, m);
    return t >= 0 ? t : t + m;
}

/* A deterministic implementation of Miller-Rabin primality test.
 * This implementation is guaranteed to give the right result for n < 2^64
 * by using a 7-number magic base.
 * Alternatively, the base can be replaced with the first 12 prime numbers
 * (prime numbers <= 37) and still working correctly.
 */
bool is_prime(long long n) {
    long long small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; ++i)
        if (n > small_primes[i] && n % small_primes[i] == 0)
            return false;
    long long base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    long long d = n - 1;
    int s = 0;
    for (; d % 2 == 0; d /= 2, ++s);
    for (int i = 0; i < 7; ++i) {
        long long a = base[i] % n;
        if (a == 0) continue;
        long long t = pow_mod(a, d, n);
        if (t == 1 || t == n - 1) continue;
        bool found = false;
        for (int r = 1; r < s; ++r) {
            t = pow_mod(t, 2, n);
            if (t == n - 1) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

ll g(ll x, ll n, ll b)
{
    return mult_mod(x, x, n) + b;
}

ll pollard_rho(ll n, ll start, ll b)
{
    ll x = start, y = start, d = 1;
    while (d == 1)
    {
        x = g(x, n, b);
        y = g(g(y, n, b), n, b);
        d = gcd(abs(x-y), n);
    }
    
    return d;
}

vector<ll> prime_factor_smart(ll n)
{
    vector<ll> factors;
    
    long long small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n <= 37*37)
    {
        for (int i = 0; i < 12; ++i)
        {
            while (n % small_primes[i] == 0)
            {
                factors.push_back(small_primes[i]);
                n /= small_primes[i];
            }
        }
        
        return factors;
    }
    
    if (is_prime(n))
    {
        factors.push_back(n);
        return factors;
    }
    else
    {
        ll factor;
        while (true)
        {
            factor = pollard_rho(n, rand()%10, rand()%10);
            
            if (factor != n)
                break;
        }
        
        vector<ll> fact1 = prime_factor_smart(n / factor);
        vector<ll> fact2 = prime_factor_smart(factor);
        
        fact1.insert(fact1.end(), fact2.begin(), fact2.end());
        return fact1;
    }
}

int main() {
    ll N, t, b;
    for (ll cs = 1; cin >> N >> t >> b; ++cs) {
        t = t % (N+1);
        
        vi prime_facts = prime_factor_smart(b);
        si divisors;
        divisors.insert(1);
        for (ll i = 0; i < prime_facts.size(); ++i) {
            si new_divisors(divisors);

            for (si::iterator it = divisors.begin(); it != divisors.end(); ++it) {
                if (*it * prime_facts[i] <= t) {
                    new_divisors.insert(*it * prime_facts[i]);
                }
            }
            divisors = new_divisors;
        }
        if (divisors.size() % 2 == 1)
            printf("Case %lld: On\n", cs);
        else
            printf("Case %lld: Off\n", cs);
    }

    return 0;
}
