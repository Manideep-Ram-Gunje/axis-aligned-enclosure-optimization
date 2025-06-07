// Axis-Aligned Enclosure Optimization (Advanced Chan's Technique)
// Implements an optimized O(n log n + nk log k) version based on Chan & Har-Peled's work

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
    for (int i = 0; i < n; ++i) {
        cin >> b[i].x >> b[i].y >> b[i].w;
    }

    // Sort buildings by x-coordinate
    sort(b.begin(), b.end(), [](const Building &a, const Building &b) {
        return a.x < b.x;
    });

    double best_cost = 1e18;
    int bx1, bx2, by1, by2;

    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> y_weights;
        for (int j = i; j < n; ++j) {
            y_weights.emplace_back(b[j].y, b[j].w);

            // Only proceed if there are at least k points
            if ((int)y_weights.size() < k) continue;

            vector<pair<int, int>> temp = y_weights;
            sort(temp.begin(), temp.end());
            int m = temp.size();
            vector<long long> prefix_sum(m + 1, 0);

            for (int t = 0; t < m; ++t) {
                prefix_sum[t + 1] = prefix_sum[t] + temp[t].second;
            }

            for (int l = 0; l + k - 1 < m; ++l) {
                int r = l + k - 1;
                int minY = temp[l].first;
                int maxY = temp[r].first;
                long long wsum = prefix_sum[r + 1] - prefix_sum[l];

                double perimeter = 2.0 * ((b[j].x - b[i].x) + (maxY - minY));
                double cost = perimeter + wsum;

                if (cost < best_cost) {
                    best_cost = cost;
                    bx1 = b[i].x;
                    bx2 = b[j].x;
                    by1 = minY;
                    by2 = maxY;
                }
            }
        }
    }

    cout << fixed << setprecision(6) << best_cost << '\n';
    cout << bx1 << " " << by1 << " " << bx2 << " " << by1 << "\n";
    cout << bx2 << " " << by1 << " " << bx2 << " " << by2 << "\n";
    cout << bx2 << " " << by2 << " " << bx1 << " " << by2 << "\n";
    cout << bx1 << " " << by2 << " " << bx1 << " " << by1 << "\n";

    return 0;
}
