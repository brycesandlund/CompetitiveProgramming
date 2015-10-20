#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long T;

T gcd(T a, T b) {
    T c;
    while (b) { c = a % b; a = b; b = c; }
    return a;
}

T lcm(T a, T b) {
    return (a / gcd(a, b)) * b;
}

struct rat {
    T n, d;

    rat(T n, T d) {
        T k = gcd(n, d);
        this->n = n/k;
        this->d = d/k;
    }

    rat(T n) : n(n), d(1) {}
};

rat operator + (const rat &a, const rat &b) {
    T new_d = lcm(a.d, b.d);
    T a_scale = new_d / a.d;
    T b_scale = new_d / b.d;
    
    if (new_d == 0) {
        cerr << "yikes" << endl;
        new_d = 1;  //overflow already occurred, just do something that won't break
    }
    
    return rat(a.n*a_scale + b.n*b_scale, new_d);
}

rat operator * (const T s, const rat &a) {
    return rat(a.n * s, a.d);
}

rat operator * (const rat &a, const T s) {
    return s*a;
}

rat operator - (const rat &a, const rat &b) {
    return a + (-1 * b);
}

rat operator * (const rat &a, const rat &b) {
    return rat(a.n*b.n, a.d*b.d); 
}

rat operator / (const rat &a, const rat &b) {
    return a * rat(b.d, b.n);
}

typedef vector<rat> vr;
typedef vector<vr> vvr;

int main() {
    vvr dp(25, vr(200, rat(0)));
    dp[0][0] = 1;
    for (ll i = 1; i < 25; ++i) {
        for (ll j = 1; j < 160; ++j) {
            for (ll k = 1; k <= 6; ++k) {
                if (j - k >= 0) {
                    rat addition = rat(1, 6) * dp[i-1][j-k];
                    dp[i][j] = dp[i][j] + addition;
                }
            }
        }
    }

    cerr << "here" << endl;

    T n, x;
    for (T cs = 1; cin >> n >> x && n; ++cs) {
        rat ans(0);
        for (T i = x; i <= 150; ++i) {
            ans = ans + dp[n][i];
        }
        if (ans.d == 1) {
            cout << ans.n << endl;
        }
        else {
            cout << ans.n << "/" << ans.d << endl;
        }
    }
    return 0;
}
