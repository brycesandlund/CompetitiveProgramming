#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll H, M;
    cin >> H >> M;

    cerr << "blah" << endl;

    ll time = H*60 + M;
    ll minID = 60*24;
    time = (time + minID - 45) % minID;

    cout << time / 60 << " " << time % 60 << endl;
}
