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

    // Sort by x
    sort(b.begin(), b.end(), [](const Building& a, const Building& b) {
        return a.x < b.x;
    });

    double best_cost = 1e18;
    int best_lx, best_rx, best_ly, best_ry;

    multiset<int> yvals;
    vector<int> wvals;

    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> yws;

        for (int j = i; j < n; ++j) {
            yws.emplace_back(b[j].y, b[j].w);
            vector<pair<int, int>> temp = yws;
            sort(temp.begin(), temp.end()); // sort by y

            vector<long long> prefix_w(temp.size() + 1, 0);
            for (int l = 0; l < temp.size(); ++l)
                prefix_w[l + 1] = prefix_w[l] + temp[l].second;

            for (int l = 0; l + k - 1 < temp.size(); ++l) {
                int r = l + k - 1;
                int y1 = temp[l].first;
                int y2 = temp[r].first;
                long long wsum = prefix_w[r + 1] - prefix_w[l];

                double perim = 2.0 * ((b[j].x - b[i].x) + (y2 - y1));
                double cost = perim + wsum;

                if (cost < best_cost) {
                    best_cost = cost;
                    best_lx = b[i].x;
                    best_rx = b[j].x;
                    best_ly = y1;
                    best_ry = y2;
                }
            }
        }
    }

    // Output best result
    cout << fixed << setprecision(6) << best_cost << "\n";
    cout << best_lx << " " << best_ly << " " << best_rx << " " << best_ly << "\n";
    cout << best_rx << " " << best_ly << " " << best_rx << " " << best_ry << "\n";
    cout << best_rx << " " << best_ry << " " << best_lx << " " << best_ry << "\n";
    cout << best_lx << " " << best_ry << " " << best_lx << " " << best_ly << "\n";

    return 0;
}
