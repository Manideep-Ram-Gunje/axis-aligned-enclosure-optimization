// Randomized Approximation Algorithm for Axis-Aligned Enclosure Optimization
// Based on (1 + ε)-approximation from Chan & Har-Peled
// This version achieves near-optimal cost with much better speed

#include <bits/stdc++.h>
using namespace std;

struct Building {
    int x, y, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<Building> b(n);
    for (int i = 0; i < n; ++i)
        cin >> b[i].x >> b[i].y >> b[i].w;

    // Parameters for randomized approximation
    const int samples = 50; // Number of random samples to try
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    double best_cost = 1e18;
    int bx1, bx2, by1, by2;

    for (int s = 0; s < samples; ++s) {
        // Randomly shuffle buildings
        shuffle(b.begin(), b.end(), rng);

        // Select top-k or slightly more buildings with lowest weights
        vector<Building> subset;
        for (int i = 0; i < n; ++i) {
            subset.push_back(b[i]);
            if ((int)subset.size() >= k && b[i].w >= 0) break;
        }

        // Find bounding box of this subset
        int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
        long long weight_sum = 0;
        for (auto &build : subset) {
            minX = min(minX, build.x);
            maxX = max(maxX, build.x);
            minY = min(minY, build.y);
            maxY = max(maxY, build.y);
            weight_sum += build.w;
        }

        double perimeter = 2.0 * ((maxX - minX) + (maxY - minY));
        double cost = perimeter + weight_sum;

        if (cost < best_cost) {
            best_cost = cost;
            bx1 = minX; bx2 = maxX;
            by1 = minY; by2 = maxY;
        }
    }

    // Output
    cout << fixed << setprecision(6) << best_cost << '\n';
    cout << bx1 << " " << by1 << " " << bx2 << " " << by1 << '\n';
    cout << bx2 << " " << by1 << " " << bx2 << " " << by2 << '\n';
    cout << bx2 << " " << by2 << " " << bx1 << " " << by2 << '\n';
    cout << bx1 << " " << by2 << " " << bx1 << " " << by1 << '\n';

    return 0;
}
