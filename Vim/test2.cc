#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long long T;
typedef pair<T, T> Pt;
#define x first
#define y second

Pt operator - (Pt one, Pt two) { return Pt(one.x - two.x, one.y - two.y); }

T dot(Pt a, Pt b) { return a.x*b.x + a.y*b.y; }

double dist(Pt a, Pt b) {
    return sqrt(dot(a-b,a-b));
}

int main() {

    vector<double> nums;

    Pt one(3, 4);
    Pt two(5, 6);
    Pt three = one - two;

    //nums.push_back(one);
    //nums.push_back(two);
    //nums.push_back(three);
    nums.push_back(3);

    sort(nums.begin(), nums.end());


    return 0;
}
