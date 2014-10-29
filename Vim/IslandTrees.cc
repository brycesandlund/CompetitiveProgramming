#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> ii;
typedef vector<ii> vii;

LL gcd(LL a, LL b)
{
    if (b > a)
        return gcd(b, a);
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

LL cross(ii a, ii b)
{
    return a.first*b.second - b.first*a.second;
}

LL shoelace(vii &pts)
{
    LL area = 0;
    for (int i = 0; i < (int)pts.size(); ++i)
    {
        area += cross(pts[i], pts[(i+1)%pts.size()]);
    }

    return abs(area / 2);
}

int main()
{
    while (1)
    {
        int N;
        cin >> N;
        if (N == 0)
            break;

        vii poly(N);
        for (int i = 0; i < N; ++i)
            cin >> poly[i].first >> poly[i].second;

        LL boundPts = 0;
        for (int i = 0; i < N; ++i)
        {
            int x = abs(poly[i].first - poly[(i+1)%N].first);
            int y = abs(poly[i].second - poly[(i+1)%N].second);
            boundPts += gcd(x, y);
        }

        LL area = shoelace(poly);
        
        LL interPts = area - boundPts/2 + 1;

        cout << interPts << endl;
    }
}
