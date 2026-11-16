/*
{
    "problem_name": "Value Counters",
    "category": "Math / Constructive Algorithms",
    "time_complexity": "O(N) -> Single mathematical pass to determine unique positions.",
    "space_complexity": "O(N) -> Flat arrays for permutation construction.",
    "formula_used": "pos = b[v] + n + 1 - v; Derived from canceling out L_v in pair counts."
}
*/
#include <iostream>
#include <vector>

using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

void solve() {
    int n;
    cin >> n;

    vector<int> b(n + 1);
    for (int v = 1; v <= n; v++) {
        cin >> b[v];
    }

    vector<int> p(n + 1, 0); // To store the constructed permutation (1-based)
    bool possible = true;

    for (int v = 1; v <= n; v++) {
        // The master formula derived from invariant cancellation
        int pos = b[v] + n + 1 - v;

        // Check if the calculated position is valid
        if (pos < 1 || pos > n) {
            possible = false;
            break;
        }

        // Check if the position is already occupied (collision)
        if (p[pos] != 0) {
            possible = false;
            break;
        }

        // Place value 'v' at its uniquely determined position
        p[pos] = v;
    }

    if (!possible) {
        cout << "-1\n";
    } else {
        for (int i = 1; i <= n; i++) {
            cout << p[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    // Hardware-level I/O bypass for max speed
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
