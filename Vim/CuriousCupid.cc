#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

typedef int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef pair<ii, ll> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

ll N, M, K;

vi a, b, answer;
viii interval;

struct language_count {
    ll l, r;
    vi language;
    ll matches = 0;

    void add(ll spot) {
        if (language[a[spot]] > 0) {
            ++matches;
        }
        --language[a[spot]];

        if (language[b[spot]] < 0) {
            ++matches;
        }
        ++language[b[spot]];
    }

    void subtract(ll spot) {
        if (language[a[spot]] >= 0) {
            --matches;
        }
        ++language[a[spot]];

        if (language[b[spot]] <= 0) {
            --matches;
        }
        --language[b[spot]];
    }

    language_count(ll start, ll K) {
        l = start;
        r = start;
        language = vi(K);
        add(start);
    }

    ll move_left(ll new_l) {
        while (l > new_l) {
            --l;
            add(l);
        }
        return matches;
    }

    ll move_right(ll new_r) {
        while (r < new_r) {
            ++r;
            add(r);
        }
        return matches;
    }

    ll move_left_right(ll new_l) {
        while (l < new_l) {
            subtract(l);
            ++l;
        }
        return matches;
    }
};

ll find_start() {
    for (ll i = 0; i < M; ++i) {
        if (answer[i] == -1)
            return i;
    }
    return -1;
}

int main() {
    cin >> N >> M >> K;
    a = vi(N), b = vi(N);

    for (ll i = 0; i < N; ++i)
        cin >> a[i];
    for (ll i = 0; i < N; ++i)
        cin >> b[i];

    interval = viii(M);
    for (ll i = 0; i < M; ++i) {
        cin >> interval[i].first.first >> interval[i].first.second;
        interval[i].second = i;
    }

    answer = vi(M, -1);

    sort(interval.begin(), interval.end());
    ll depth = (ll)sqrt(M / log2(M));

    while (true) {
        // longest decreasing subsequence
        vi best_idx(2, -1);
        vi best(2, N+1);
        vi prev_idx(M, -1);

        ll start = find_start();
        if (start == -1)
            break;

        best_idx[1] = start;
        best[1] = interval[start].first.second;

        for (ll i = start+1; i < M; ++i) {
            if (answer[i] != -1)
                continue;
            auto it = upper_bound(best.begin(), best.end(), interval[i].first.second, greater<ll>());
            ll idx = it - best.begin();
            if (idx == best.size()) {
                best.push_back(interval[i].first.second);
                best_idx.push_back(i);
                prev_idx[i] = best_idx[idx-1];
            }
            else {
                best[idx] = interval[i].first.second;
                best_idx[idx] = i;
                prev_idx[i] = best_idx[idx-1];
            }
        }

        if (best.size() <= depth) {
            break;
        }
        else {
            vi nest;
            ll cur = best_idx.back();
            while (true) {
                nest.push_back(cur);
                if (prev_idx[cur] == -1)
                    break;
                cur = prev_idx[cur];
            }
            
            language_count lc(interval[nest[0]].first.first, K);
            for (ll i = 0; i < nest.size(); ++i) {
                lc.move_left(interval[nest[i]].first.first);
                answer[nest[i]] = lc.move_right(interval[nest[i]].first.second);
            }
        }
    }
    
    while (true) {
        ll start = find_start();
        if (start == -1)
            break;
        
        language_count lc(interval[start].first.first, K);
        for (ll i = start; i < M; ++i) {
            if (answer[i] != -1 || interval[i].first.second < lc.r)
                continue;

            lc.move_right(interval[i].first.second);
            answer[i] = lc.move_left_right(interval[i].first.first);
        }
    }
    
    vi final_answer(M);
    for (ll i = 0; i < M; ++i) {
        final_answer[interval[i].second] = answer[i];
    }

    for (ll i = 0; i < M; ++i) {
        cout << final_answer[i] << endl;
    }
}
