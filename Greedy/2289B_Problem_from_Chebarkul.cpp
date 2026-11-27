/*
{
    "problem_name": "Problem from Chebarkul",
    "category": "Greedy / Sliding Window / Implementation",
    "time_complexity": "O(N) -> Single streaming pass.",
    "space_complexity": "O(1) -> ZERO array storage, pure register variables.",
    "formula_used": "Window size W = n - k + 1; position i is invariant iff a[i .. i+W-1] are all equal."
}
*/
#include <iostream>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    int w = n - k + 1;
    int prev = -1, run = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == prev) {
            run++;
        } else {
            prev = x;
            run = 1;
        }
        if (run >= w) {
            ans++;
        }
    }

    cout << ans << '\n';
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
