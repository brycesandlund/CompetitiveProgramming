#include <vector>
#include <iostream>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

bool orient2D(ii a, ii b, ii q)
{
    return (b.first-a.first)*(q.second-a.second) - (q.first-a.first)*(b.second-a.second) > 0;
}

int main()
{
    while (true)
    {
        int N;
        cin >> N;
        if (N == 0)
            break;

        vii polygon(N);

        for (int i = 0; i < N; ++i)
        {
            cin >> polygon[i].first >> polygon[i].second;
        }

        int left = 0, right = 0;
        for (int i = 0; i < N; ++i)
        {
            if (orient2D(polygon[(i+N-1)%N], polygon[i], polygon[(i+1)%N]))
                ++left;
            else
                ++right;
        }

        cout << (left > 0 && right > 0 ? "Yes" : "No") << endl; 
    }
}
