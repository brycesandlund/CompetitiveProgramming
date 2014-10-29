#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;

int cross(ii a, ii b)
{
    return a.first*b.second - b.first*a.second;
}

int shoelace(vii &pts)
{
    int area = 0;
    for (int i = 0; i < (int)pts.size(); ++i)
    {
        area += cross(pts[i], pts[(i+1)%pts.size()]);
    }

    return abs(area);
}

bool orient2D(ii a, ii b, ii q)
{
    return (b.first-a.first)*(q.second-a.second) - (q.first-a.first)*(b.second-a.second) > 0;
}

vii convex_hull(vii pts)
{
    sort(pts.begin(), pts.end());
    vii up, dn;

    for (int i = 0; i < pts.size(); ++i)
    {

        while (up.size() > 1 && orient2D(up[up.size()-2],up.back(),pts[i]))
            up.pop_back();
        while (dn.size() > 1 && !orient2D(dn[dn.size()-2],dn.back(),pts[i]))
            dn.pop_back();

        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }

    for (int i = up.size()-2; i >= 1; i--) dn.push_back(up[i]);

    return dn;
}

bool inPoly(vii &poly, ii qpt)
{
    for (int i = 0; i < poly.size(); ++i)
    {
        if (!orient2D(poly[i], poly[(i+1)%poly.size()], qpt))
            return false;
    }

    return true;
}

int main()
{
    vvii kingdoms;
    while (true)
    {
        int N;
        cin >> N;

        if (N == -1)
            break;

        vii kingdom(N);
        for (int i = 0; i < N; ++i)
            cin >> kingdom[i].first >> kingdom[i].second;

        kingdoms.push_back(convex_hull(kingdom));
    }

    ii qpt;
    vb hasPower(kingdoms.size(), true);
    while (cin >> qpt.first >> qpt.second)
    {
        for (int i = 0; i < kingdoms.size(); ++i)
        {
            if (inPoly(kingdoms[i], qpt))
                hasPower[i] = false;
        }
    }

    double total = 0;
    for (int i = 0; i < kingdoms.size(); ++i)
    {
        if (!hasPower[i])
            total += shoelace(kingdoms[i]);
    }

    printf("%.2f\n", total/2.0);
}
