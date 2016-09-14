#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<ll> vi;

int main() {
    ll n, A, c_f, c_m, m;
    cin >> n >> A >> c_f >> c_m >> m;

    vi a(n);
    vii a_idx(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        a_idx[i] = ii(a[i], i);
    }
    
    vi a_cp(a);
    sort(a.begin(), a.end());
    sort(a_idx.begin(), a_idx.end());

    vi idx_to_pos(n);
    for (ll i = 0; i < n; ++i) {
        idx_to_pos[a_idx[i].second] = i;
    }

    vi cost_bot(n, 0);
    for (ll i = 1; i < n; ++i) {
        cost_bot[i] = cost_bot[i-1] + (i * (a[i] - a[i-1]));
    }

    vi cost_top(n+1, 0);
    for (ll i = n-1; i >= 0; --i) {
        cost_top[i] = cost_top[i+1] + (A - a[i]);
    }

    ll best = 0;
    ll bot_k = -1, top_k = n, bot_val = -1;
    for (ll i = n; i >= 0; --i) {
        ll left = m - cost_top[i];

        if (left < 0)
            break;

        ll bot_idx = (upper_bound(cost_bot.begin(), cost_bot.end(), left)-1) - cost_bot.begin();
        
        if (bot_idx >= i)
            bot_idx = i-1;
        
        left -= cost_bot[bot_idx];
        ll cur_bot_val = -1;
        if (bot_idx+1 == 0) {
            cur_bot_val = A;
        }
        else {
       ll  inc = left / (bot_idx+1);
        
            cur_bot_val = a[bot_idx] + inc;

        }
        

        cur_bot_val = min(cur_bot_val, A);

        //cerr << bot_idx << " " << left << " " << inc << " " << cur_bot_val <<  endl;

        ll cur_val = c_f * (n-i) + cur_bot_val * c_m;

        //cerr << cur_val << " " << i << endl;
        //cerr << endl;

        if (cur_val > best) {
            top_k = i;
            bot_k = bot_idx;
            bot_val = cur_bot_val;
            best = cur_val;
        }
    }

    cout << best << endl;
    //cerr << top_k << endl;
    //cerr << bot_k << endl;

    for (ll i = 0; i < n; ++i) {
        //cerr << "pos: " << idx_to_pos[i] << endl << endl;
        
        if (idx_to_pos[i] <= bot_k) {
            cout << bot_val;
        }
        else if (idx_to_pos[i] >= top_k) {
            cout << A;
        }
        else {
            cout << a_cp[i];
        }

        if (i != n-1)
            cout << " ";
    }
    cout << endl;

    return 0;
}
