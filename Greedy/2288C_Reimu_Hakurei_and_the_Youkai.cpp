/*
{
    "problem_name": "Reimu Hakurei and the Youkai",
    "category": "Greedy / Sorting / Math",
    "time_complexity": "O(N log N) -> Single sort + linear bound evaluation.",
    "space_complexity": "O(N) -> Flat static array, ZERO dynamic allocation.",
    "formula_used": "h_i = (a_i - 1) / x + 1; ans = max(0, max_{1 <= i <= n-1}(h_i - i))"
}
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
int h[MAXN];

void solve() {
    int n, x;
    cin >> n >> x;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        // Overflow-safe ceil(a / x)
        h[i] = (a - 1) / x + 1;
    }

    sort(h, h + n);

    // Leave h[n - 1] as the survivor; defeat h[0 .. n - 2]
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        // 1-based index is (i + 1)
        int need = h[i] - (i + 1);
        if (need > ans) {
            ans = need;
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
