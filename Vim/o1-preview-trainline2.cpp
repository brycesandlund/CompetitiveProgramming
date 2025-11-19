#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

struct Area {
    int population;
    int position;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Area> areas(n);

    for (int i = 0; i < n; ++i) {
        cin >> areas[i].population >> areas[i].position;
    }

    // Sort areas by population in descending order
    sort(areas.begin(), areas.end(), [](const Area &a, const Area &b) {
        return a.population > b.population;
    });

    // Place stations at positions of top k areas
    set<int> station_positions_set;
    for (int i = 0; i < min(k, n); ++i) {
        station_positions_set.insert(areas[i].position);
    }

    vector<int> station_positions(station_positions_set.begin(), station_positions_set.end());

    // Sort areas by position
    sort(areas.begin(), areas.end(), [](const Area &a, const Area &b) {
        return a.position < b.position;
    });

    // Sort station positions
    sort(station_positions.begin(), station_positions.end());

    // Assign areas to nearest station
    double total_utility = 0.0;
    int s = 0;
    for (const auto &area : areas) {
        // Find nearest station
        while (s + 1 < station_positions.size() &&
               abs(area.position - station_positions[s]) >= abs(area.position - station_positions[s + 1])) {
            s++;
        }
        int min_distance = abs(area.position - station_positions[s]);
        double utility = area.population * pow(2.0, -min_distance);
        total_utility += utility;
    }

    cout.precision(6);
    cout << fixed << total_utility << "\n";

    return 0;
}
