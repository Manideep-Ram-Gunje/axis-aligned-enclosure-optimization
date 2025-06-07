// Hybrid Algorithm: Rectangle + Polygon Strategy for Axis-Aligned Enclosure Optimization
// Combines tight rectangle approximation with polygonal perimeter minimization

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

    // Parameters for sampling
    const int samples = 50;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    double best_cost = 1e18;
    vector<tuple<double, double, double, double>> best_edges;

    for (int s = 0; s < samples; ++s) {
        shuffle(b.begin(), b.end(), rng);

        vector<Building> selected;
        long long weight_sum = 0;
        for (int i = 0; i < n; ++i) {
            selected.push_back(b[i]);
            weight_sum += b[i].w;
            if ((int)selected.size() >= k && b[i].w >= 0) break;
        }

        // Rectangle candidate
        int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
        for (auto &build : selected) {
            minX = min(minX, build.x);
            maxX = max(maxX, build.x);
            minY = min(minY, build.y);
            maxY = max(maxY, build.y);
        }
        double rect_perimeter = 2.0 * ((maxX - minX) + (maxY - minY));
        double rect_cost = rect_perimeter + weight_sum;

        if (rect_cost < best_cost) {
            best_cost = rect_cost;
            best_edges = {
                {minX, minY, maxX, minY},
                {maxX, minY, maxX, maxY},
                {maxX, maxY, minX, maxY},
                {minX, maxY, minX, minY}
            };
        }

        // Polygon candidate using convex hull
        vector<pair<int, int>> points;
        for (auto &build : selected)
            points.emplace_back(build.x, build.y);

        sort(points.begin(), points.end());
        vector<pair<int, int>> hull;

        // Lower hull
        for (auto &pt : points) {
            while (hull.size() >= 2 && (hull.back().first - hull[hull.size()-2].first) * (pt.second - hull.back().second)
                 - (hull.back().second - hull[hull.size()-2].second) * (pt.first - hull.back().first) <= 0)
                hull.pop_back();
            hull.push_back(pt);
        }

        // Upper hull
        size_t lower_size = hull.size();
        for (int i = (int)points.size() - 2; i >= 0; --i) {
            auto pt = points[i];
            while (hull.size() > lower_size && (hull.back().first - hull[hull.size()-2].first) * (pt.second - hull.back().second)
                 - (hull.back().second - hull[hull.size()-2].second) * (pt.first - hull.back().first) <= 0)
                hull.pop_back();
            hull.push_back(pt);
        }

        hull.pop_back(); // last point == first point

        // Convert to axis-aligned polygon
        vector<tuple<double, double, double, double>> poly_edges;
        double poly_perimeter = 0;
        for (int i = 0; i < (int)hull.size(); ++i) {
            auto [x1, y1] = hull[i];
            auto [x2, y2] = hull[(i+1)%hull.size()];
            // Force axis-aligned (snap one coordinate)
            if (x1 == x2 || y1 == y2) {
                poly_perimeter += abs(x1 - x2) + abs(y1 - y2);
                poly_edges.emplace_back(x1, y1, x2, y2);
            }
        }

        double poly_cost = poly_perimeter + weight_sum;
        if (poly_edges.size() >= 4 && poly_cost < best_cost) {
            best_cost = poly_cost;
            best_edges = poly_edges;
        }
    }

    // Output
    cout << fixed << setprecision(6) << best_cost << '\n';
    for (auto &[x1, y1, x2, y2] : best_edges)
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << '\n';

    return 0;
}
