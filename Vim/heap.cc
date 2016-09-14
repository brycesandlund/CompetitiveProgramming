#include <iostream>
#include <set>
#include <sstream>

using namespace std;

typedef long long ll;

int main() {
    ll m;
    cin >> m;

    multiset<ll> heap;

    stringstream output;

    ll count = 0;

    for (ll i = 0; i < m; ++i) {
        string op;
        cin >> op;
        if (op == "removeMin") {
            if (heap.empty()) {
                output << "insert 1" << endl;
                ++count;
            }
            else {
                heap.erase(heap.begin());
            }
            output << "removeMin" << endl;
            ++count;
        }
        else if (op == "insert") {
            ll n;
            cin >> n;
            heap.insert(n);
            output << "insert " << n << endl;
            ++count;
        }
        else {
            ll n;
            cin >> n;

            while (!heap.empty() && *heap.begin() < n) {
                output << "removeMin" << endl;
                ++count;
                heap.erase(heap.begin());
            }

            if (heap.empty() || *heap.begin() != n) {
                heap.insert(n);
                output << "insert " << n << endl;
                ++count;
            }
            output << "getMin " << n << endl;
            ++count;
        }
    }

    cout << count << endl;
    cout << output.str();
}
