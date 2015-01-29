#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define EP 10e-8

using namespace std;

typedef long long ll;
typedef vector<double> vd;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

double f(ll x, ll y)
{
    if (x < 0) return -f(-x, y);
    return acos(y / sqrt(x*x + y*y));
}

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll N, theta;

        cin >> N >> theta;

        if (N == 0 && theta == 0)
            break;

        vd angles(N);

        vii points(N+1);
        points[0] = ii(0, 0);

        for (ll i = 1; i < N+1; ++i)
        {
            cin >> points[i].first >> points[i].second;
        }

        double minCounter = 0;
        double minClock = 0;
        for (ll i = 1; i < N+1; ++i)
        {
            double cur = f(points[i].first - points[i-1].first, points[i].second - points[i-1].second);
            angles[i-1] = cur;
            if (cur < 0)
            {
                minCounter = max(minCounter, -cur);
                minClock = max(minClock, acos(-1) + cur);
            }
        }

        bool counter = true;
        bool clock = true;
        for (ll i = 0; i < N; ++i)
        {
            if (angles[i] + minCounter > acos(-1) + EP)
            {
                counter = false;
            }

            if (angles[i] >= EP && angles[i] - minClock < -EP)
            {
                clock = false;
            }
        }

        printf("Case %lld: ", caseNum);
        if ((counter && minCounter == 0) || (clock && minClock == 0) || theta == 0)
        {
            printf("Acceptable as proposed\n");
        }
        else if (!counter && !clock)
        {
            printf("Unacceptable\n");
        }
        else
        {
            if ((clock && minClock + EP < minCounter) || (clock && !counter))
            {
                printf("Acceptable after counterclockwise rotation of %.2lf degrees\n", (minClock*360)/(acos(-1)*2));
            }
            else
            {
                printf("Acceptable after clockwise rotation of %.2lf degrees\n", (minCounter*360)/(acos(-1)*2));
            }
        }

        printf("\n");
    }
}
