/*
{
    "problem_name": "Lakeside Trail (Hard Version)",
    "category": "Binary Search / Dynamic Programming",
    "time_complexity": "O(N log(MAX_H)) -> Binary Search with O(N) circular DP propagation.",
    "space_complexity": "O(N) -> Flat static arrays, ZERO dynamic allocation.",
    "formula_used": "req[curr] = max(req[curr], req[neighbor] - S) via 2-pass zero-modulo propagation"
}
*/
#include <iostream>

using namespace std;

const int MAXN = 1000005;
long long h[MAXN];
long long req[MAXN];

int n;
long long k;

// Inlined check function to bypass function call overhead
inline bool check(long long S) {
    for (int i = 0; i < n; i++) {
        req[i] = h[i];
    }

    // 1. Forward Circular Propagation (Zero Modulo Overhead)
    int prev = n - 1;
    int curr = 0;
    for (int step = 0; step < 2 * n; step++) {
        long long val = req[prev] - S;
        if (val > req[curr]) {
            req[curr] = val;
        }
        prev = curr;
        curr++;
        // Branch predictor will completely optimize this single condition
        if (curr == n) curr = 0;
    }

    // 2. Backward Circular Propagation (Zero Modulo Overhead)
    curr = n - 1;
    int next = 0;
    for (int step = 0; step < 2 * n; step++) {
        long long val = req[next] - S;
        if (val > req[curr]) {
            req[curr] = val;
        }
        next = curr;
        curr--;
        // Predictable backward wrap-around
        if (curr < 0) curr = n - 1;
    }

    long long total_soil = 0;
    for (int i = 0; i < n; i++) {
        total_soil += (req[i] - h[i]);
        if (total_soil > k) {
            return false;
        }
    }

    return true;
}

void solve() {
    cin >> n >> k;

    // Track global max for a tighter binary search upper bound
    long long max_h = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        if (h[i] > max_h) max_h = h[i];
    }

    long long low = 0;
    // The maximum possible difference is tightly bounded by max_h
    long long high = max_h;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";
}

int main() {
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
