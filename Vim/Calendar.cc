#include <iostream>

using namespace std;

typedef long long ll;

bool leap(ll y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int main() {
    ll y;
    cin >> y;

    ll day = 0;
    bool need_leap = leap(y);
    while (true) {
        ++y;
        if (leap(y)) {
            day = (day + 366) % 7;
            if (day == 0 && need_leap) {
                break;
            }
        }
        else {
            day = (day + 365) % 7;
            if (day == 0 && !need_leap) {
                break;
            }
        }
    }
    cout << y << endl;
}
