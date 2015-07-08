#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll total;
    cin >> total;
    
    ll min1, max1, min2, max2, min3, max3;
    cin >> min1 >> max1 >> min2 >> max2 >> min3 >> max3;

    ll n1 = min1, n2 = min2, n3 = min3;
    total -= n1 + n2 + n3;
    ll n1add = min(max1 - min1, total);
    n1 += n1add;
    total -= n1add;

    ll n2add = min(max2 - min2, total);
    n2 += n2add;
    total -= n2add;

    ll n3add = min(max3 - min3, total);
    n3 += n3add;
    total -= n3add;

    cout << n1 << " " << n2 << " " << n3 << endl;
    return 0;
}
