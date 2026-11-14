/*
{
    "problem_name": "Lakeside Trail (Easy Version)",
    "category": "Binary Search / Math",
    "time_complexity": "O(N^2 log(10^9)) -> Global bounding over circular distances inside BS.",
    "space_complexity": "O(N) -> Array storage only, zero DP matrix overhead.",
    "formula_used": "req_h[i] = max_{j}(h[j] - dist(i, j) * S)"
}
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// O(N^2) brutally efficient check function
bool check(long long S, int n, long long k, const vector<long long>& h) {
    long long total_soil = 0;

    for (int i = 0; i < n; i++) {
        long long req_h = h[i];

        // Find the maximum bound imposed on section 'i' by all other sections 'j'
        for (int j = 0; j < n; j++) {
            // Shortest circular distance between i and j
            int dist = abs(i - j);
            dist = min(dist, n - dist);

            long long needed = h[j] - 1LL * dist * S;
            if (needed > req_h) {
                req_h = needed;
            }
        }

        total_soil += (req_h - h[i]);

        // Early termination to prevent long long overflow and save execution time
        if (total_soil > k) {
            return false;
        }
    }
    return total_soil <= k;
}

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // Binary search over possible steepness S
    long long low = 0;
    long long high = 1e9; // Max difference between any two heights is at most 1e9
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, n, k, h)) {
            ans = mid;
            high = mid - 1; // Try to find a smaller valid steepness
        } else {
            low = mid + 1;  // Allowed steepness is too strict, increase it
        }
    }

    cout << ans << "\n";
}

int main() {
    // Hardware-level I/O bypass
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
