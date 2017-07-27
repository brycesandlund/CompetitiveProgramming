#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<string> vs;

struct Path {
    vector<Path> children;
    string id;

    ll add(vs &path, ll curIdx) {
        if (curIdx == path.size()) {
            return 0;
        }

        for (ll i = 0; i < children.size(); ++i) {
            if (children[i].id == path[curIdx]) {
                return children[i].add(path, curIdx+1);
            }
        }

        children.push_back(Path(path[curIdx]));
        return children.back().add(path, curIdx+1) + 1;
    }

    Path(string id) : id(id) {}
};

vs tokenize(string input) {
    stringstream ss;
    ss << input;

    vs tokens;
    string token;
    while (getline(ss, token, '/')) {
        tokens.push_back(token);
    }

    return tokens;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll N, M;
        cin >> N >> M;

        Path root("");
        vs empty(1, "");
        root.add(empty, 0);
        for (ll i = 0; i < N; ++i) {
            string s;
            cin >> s;
            vs sVect = tokenize(s);
            root.add(sVect, 0);
        }

        ll total = 0;
        for (ll i = 0; i < M; ++i) {
            string s;
            cin >> s;
            vs sVect = tokenize(s);
            total += root.add(sVect, 0);
        }

        printf("Case #%lld: %lld\n", cs, total);
    }

    return 0;
}
