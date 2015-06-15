#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <sstream>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef unordered_set<string> ss;

void insertWords(ss &dict, vs &words) {
    for (ll i = 0; i < words.size(); ++i) {
        dict.insert(words[i]);
    }
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll N;
        cin >> N;

        vvs sentences(N);
        string blah;
        getline(cin, blah);
        for (ll i = 0; i < N; ++i) {
            string line;
            getline(cin, line);

            stringstream ss;
            ss << line;

            string word;
            while (ss >> word) {
                sentences[i].push_back(word);
            }
        }

        ss english, french;
        for (ll i = 0; i < sentences[0].size(); ++i) {
            english.insert(sentences[0][i]);
        }
        for (ll i = 0; i < sentences[1].size(); ++i) {
            french.insert(sentences[1][i]);
        }

        ll ans = INF;
        for (ll mask = 0; mask < (1 << (N-2)); ++mask) {
            cerr << mask << endl;
            ss englishCp = english;
            ss frenchCp = french;
           
            for (ll copy = mask, i = 0; i < N-2; copy /= 2, ++i) {
                if (copy % 2 == 1) {
                    insertWords(englishCp, sentences[i+2]);
                }
                else {
                    insertWords(frenchCp, sentences[i+2]);
                }
            }

            ll curAns = 0;
            for (ss::iterator it = englishCp.begin(); it != englishCp.end(); ++it) {
                if (frenchCp.count(*it)) {
                    ++curAns;
                }
            }

            ans = min(ans, curAns);
        }

        printf("Case #%lld: %lld\n", cs, ans);
    }
    return 0;
}
