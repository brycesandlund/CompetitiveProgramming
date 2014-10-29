#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define INF 1000000000
#define EP 1e-10

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool orient2D(ii a, ii b, ii q)
{
    return (b.first-a.first)*(q.second-a.second) - (q.first-a.first)*(b.second-a.second) > 0;
}

vii convexHull(vii pts)
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

double dist(ii pt1, ii pt2)
{
    return sqrt(pow(pt1.first - pt2.first, 2) + pow(pt1.second - pt2.second, 2));
}

double perimeter(vii p)
{
    double total = 0;
    for (int i = 0; i < p.size(); ++i)
        total += dist(p[i], p[(i+1)%p.size()]);

    return total;
}

int main()
{
    for (int caseNum = 1; true; ++caseNum)
    {
        int n;
        cin >> n;

        if (n == 0)
            break;

        if (caseNum != 1)
            cout << endl;

        vii trees(n);
        vi v(n), l(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> trees[i].first >> trees[i].second >> v[i] >> l[i];
        }

        int minVal = INF;
        vi minTrees;
        double minExtraW;
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            vii notcut;
            vi cut;
            int copy = mask;
            double lengthA = 0;
            int cutVal = 0;

            for (int i = 0; i < n; ++i, copy /= 2)
            {
                if (copy % 2 == 0)
                    notcut.push_back(trees[i]);
                else
                {
                    cut.push_back(i+1);
                    lengthA += l[i];
                    cutVal += v[i];
                }
            }

            double lengthNeeded = perimeter(convexHull(notcut));

            double extraW = lengthA - lengthNeeded;
            if (extraW > -EP)
            {
                if (cutVal < minVal || cutVal == minVal && cut.size() < minTrees.size())
                {
                    minTrees = cut;
                    minVal = cutVal;
                    minExtraW = extraW;
                }
            }
        }

        printf("Forest %d\n", caseNum);
        printf("Cut these trees:");

        for (int i = 0; i < minTrees.size(); ++i)
            cout << " " << minTrees[i]; 
        
        cout << endl;
        printf("Extra wood: %.2f\n", minExtraW);
    }
}
