#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <map>
#include <queue>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

map<string, ll> str_to_id;
vvi adj_list;
string pe = "PAUL_ERDOS";

ll get_id(string name) {
    if (!str_to_id.count(name)) {
        ll size = str_to_id.size();
        str_to_id[name] = size;
        adj_list.push_back(vi());
    }

    return str_to_id[name];
}

int main() {
    string line;
    vector<string> person;
    while (getline(cin, line)) {
        stringstream ss(line);

        string author;
        ss >> author;
        person.push_back(author);

        ll author_id = get_id(author);

        string coauthor;
        while (ss >> coauthor) {
            ll coauthor_id = get_id(coauthor);

            adj_list[author_id].push_back(coauthor_id);
            adj_list[coauthor_id].push_back(author_id);
        }
    }

    ll n = adj_list.size();
    vi dist(n, INF);

    queue<ll> q;
    q.push(get_id(pe));
    dist[get_id(pe)] = 0;

    while (!q.empty()) {
        ll cur = q.front(); q.pop();
        
        for (ll i = 0; i < adj_list[cur].size(); ++i) {
            if (dist[cur]+1 < dist[adj_list[cur][i]]) {
                dist[adj_list[cur][i]] = dist[cur]+1;
                q.push(adj_list[cur][i]);
            }
        }
    }

    for (ll i = 0; i < person.size(); ++i) {
        if (dist[get_id(person[i])] < INF)
            cout << person[i] << " " << dist[get_id(person[i])] << endl;
        else
            cout << person[i] << " no-connection" << endl;
    }
}
