#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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

    // Sort areas by position (they are already sorted according to the problem, but we ensure it)
    sort(areas.begin(), areas.end(), [](const Area &a, const Area &b) {
        return a.position < b.position;
    });

    // Compute cumulative population
    vector<long long> cumulative_pop(n);
    cumulative_pop[0] = areas[0].population;
    for (int i = 1; i < n; ++i) {
        cumulative_pop[i] = cumulative_pop[i - 1] + areas[i].population;
    }

    long long total_population = cumulative_pop[n - 1];

    // Determine target cumulative populations for partitioning
    vector<long long> targets(k);
    for (int i = 0; i < k; ++i) {
        targets[i] = (total_population * (i + 1)) / k;
    }

    // Partition areas into segments based on cumulative population
    vector<int> segment_indices;
    int idx = 0;
    for (int i = 0; i < k - 1; ++i) {
        // Find the index where cumulative population crosses the target
        while (idx < n && cumulative_pop[idx] < targets[i]) {
            idx++;
        }
        segment_indices.push_back(idx);
    }
    segment_indices.push_back(n);  // Ensure the last segment includes all remaining areas

    // Compute the weighted median for each segment and place a station there
    vector<int> station_positions;
    int start_idx = 0;
    for (int si = 0; si < k; ++si) {
        int end_idx = segment_indices[si];
        long long segment_pop = cumulative_pop[end_idx - 1] - (start_idx > 0 ? cumulative_pop[start_idx - 1] : 0);
        long long half_pop = segment_pop / 2;

        // Find the weighted median position
        int median_idx = start_idx;
        long long cum_pop = areas[median_idx].population;
        while (median_idx + 1 < end_idx && cum_pop < half_pop) {
            median_idx++;
            cum_pop += areas[median_idx].population;
        }
        station_positions.push_back(areas[median_idx].position);

        start_idx = end_idx;
    }

    // Compute the total utility
    double total_utility = 0.0;
    idx = 0;
    int station_idx = 0;
    for (int i = 0; i < n; ++i) {
        // Move to the nearest station
        while (station_idx + 1 < station_positions.size() &&
               abs(areas[i].position - station_positions[station_idx]) >=
               abs(areas[i].position - station_positions[station_idx + 1])) {
            station_idx++;
        }

        int distance = abs(areas[i].position - station_positions[station_idx]);
        // Since 2^{-distance} can underflow, we use logarithms
        // utility = p_i * 2^{-distance} = p_i * e^{ -ln(2) * distance }
        double utility = areas[i].population * exp(-0.6931471805599453 * distance);  // ln(2) ≈ 0.6931
        total_utility += utility;
    }

    // Output the total utility with precision up to 1e-3
    cout.precision(6);
    cout << fixed << total_utility << "\n";

    return 0;
}
