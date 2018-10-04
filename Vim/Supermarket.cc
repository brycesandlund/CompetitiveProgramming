#include <iostream>
#include <vector>
#include <cfloat>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    double best = DBL_MAX;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        double cur = a / (double)b;

        best = min(best, cur);
    }

    printf("%.10lf\n", best*m);
}
