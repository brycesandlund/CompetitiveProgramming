#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef pair<ii, ll> iii;
typedef vector<iii> viii;
typedef vector<ll> vi;
    
set<ii> x_coord, y_coord; // (coordinate, index)
vii points;
viii queries;
ll n, q;

bool myfunction(iii one, iii two) {
    ll x_bucket_one = one.f.f % (ll)sqrt(n);
    ll x_bucket_two = two.f.f % (ll)sqrt(n);

    if (x_bucket_one == x_bucket_two) {
        return one.f.s < two.f.s;
    }
    else {
        return x_bucket_one < x_bucket_two;
    }
}

void add_pt(ll idx) {
    x_coord.insert(ii(points[idx].f, idx));
    y_coord.insert(ii(points[idx].s, idx));
}

void remove_pt(ll idx) {
    x_coord.erase(ii(points[idx].f, idx));
    y_coord.erase(ii(points[idx].s, idx));
}

ll remove_and_test(ll idx) {
    x_coord.erase(ii(points[idx].f, idx));
    y_coord.erase(ii(points[idx].s, idx));
    
    ll x_spread = x_coord.rbegin()->f - x_coord.begin()->f;
    ll y_spread = y_coord.rbegin()->f - y_coord.begin()->f;

    x_coord.insert(ii(points[idx].f, idx));
    y_coord.insert(ii(points[idx].s, idx));

    ll ans = max(x_spread, y_spread);
    return ans;
}

int main() {
    cin >> n >> q;

    points = vii(n);
    for (ll i = 0; i < n; ++i) {
        cin >> points[i].f >> points[i].s;
    }

    queries = viii(q);  //((x, y), idx)
    for (ll i = 0; i < q; ++i) {
        cin >> queries[i].f.f >> queries[i].f.s;
        --queries[i].f.f;
        --queries[i].f.s;
        queries[i].s = i;
    }

    sort(queries.begin(), queries.end(), myfunction);
    vi answers(q);

    cerr << "here" << endl;

    ll l = 0, r = 0;
    add_pt(0);
    for (ll i = 0; i < q; ++i) {
        while (r < queries[i].f.s) {
            add_pt(++r);
        }
        while (l > queries[i].f.f) {
            add_pt(--l);
        }
        while (l < queries[i].f.f) {
            remove_pt(l++);
        }
        while (r > queries[i].f.s) {
            remove_pt(r--);
        }

        ll remove_bot = remove_and_test(y_coord.begin()->s);
        ll remove_top = remove_and_test(y_coord.rbegin()->s);
        ll remove_left = remove_and_test(x_coord.begin()->s);
        ll remove_right = remove_and_test(x_coord.rbegin()->s);
        answers[queries[i].s] = min(min(remove_bot, remove_top), min(remove_left, remove_right));
    }

    for (ll i = 0; i < q; ++i) {
        cout << answers[i] << endl;
    }
}
