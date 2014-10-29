#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <set>

#define EP 1e-10

using namespace std;

typedef pair<double, double> dd;
typedef vector<dd> vdd;

double cross(dd a, dd b)
{
    return a.first*b.second - b.first*a.second;
}

double shoelace(vdd &pts)
{
    double area = 0;
    for (int i = 0; i < (int)pts.size(); ++i)
    {
        area += cross(pts[i], pts[(i+1)%pts.size()]);
    }

    return abs(area / 2);
}

int main()
{
    while(1)
    {
        int N;
        cin >> N;
        string line;
        getline(cin, line);

        if (N == 0)
            break;

        double total = 0;

        for (int i = 0; i < N; ++i)
        {
            getline(cin, line);

            //cout << line << endl;

            stringstream ss;
            ss << line;

            double T;
            ss >> T;

            //cout << T << endl;

            vdd pts;

            double x, y;
            while (ss >> x >> y)
            {
                pts.push_back(dd(x, y));
            //    cout << x << ", " << y << endl;
            }

            pts.pop_back();

            total += shoelace(pts) * T;
        }

        double R, T;
        cin >> R >> T;

        //cout << R << "   " << T << endl;

        cout << (long long)(total / (M_PI * R * R * T) + EP) << endl;
    }
}
