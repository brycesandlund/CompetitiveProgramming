#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
typedef pair<ll, ll> ii;
typedef set<ii> sii;
typedef vector<sii> vsii;
typedef vector<vsii> vvsii;

void findLCS(vvsii &parent, string &a, ll i, ll j, vs &result, string &cur, ll curIdx) {
    if (parent[i][j].empty()) {
        //result.push_back(cur);
        cout << cur << endl;
    }
    else {
        for (sii::iterator it = parent[i][j].begin(); it != parent[i][j].end(); ++it) {
            cur[curIdx] = a[it->first];
            findLCS(parent, a, it->first, it->second, result, cur, curIdx-1);
        }
    }
}

int main() {
    string a, b;
    for (ll cs = 1; cin >> a >> b; ++cs) {
        ll n = a.size()+1;
        ll m = b.size()+1;
        
        vvsii parent(n, vsii(m));
        vvi bestLength(n, vi(m, 0));

        for (ll i = 1; i < n; ++i) {
            for (ll j = 1; j < m; ++j) {
                if (a[i-1] == b[j-1]) {
                    bestLength[i][j] = bestLength[i-1][j-1]+1;
                    parent[i][j].insert(ii(i-1, j-1));
                }

                if (bestLength[i-1][j] > bestLength[i][j]) {
                    parent[i][j] = parent[i-1][j];
                    bestLength[i][j] = bestLength[i-1][j];
                }
                else if (bestLength[i-1][j] == bestLength[i][j]) {
                    parent[i][j].insert(parent[i-1][j].begin(), parent[i-1][j].end());
                }

                if (bestLength[i][j-1] > bestLength[i][j]) {
                    parent[i][j] = parent[i][j-1];
                    bestLength[i][j] = bestLength[i][j-1];
                }
                else if (bestLength[i][j-1] == bestLength[i][j]) {
                    parent[i][j].insert(parent[i][j-1].begin(), parent[i][j-1].end());
                }
            }
        }

        if (cs != 1)
            cout << endl;

        cerr << "here" << endl;
        if (bestLength[n-1][m-1] == 0) {
            cout << "No common sequence." << endl;
        }
        else {
            vs result;
            string cur(bestLength[n-1][m-1], ' ');
            findLCS(parent, a, n-1, m-1, result, cur, cur.size()-1);
            //sort(result.begin(), result.end());
            //vs::iterator it = unique(result.begin(), result.end());
            //result.resize(it - result.begin());
            for (ll i = 0; i < result.size(); ++i) {
                cout << result[i] << endl;
            }
        }
    }
}
