/*
{
    "problem_name": "2290C",
    "category": "Constructive Algorithms / Greedy / Sorting",
    "time_complexity": "O(N log N) -> Single sort + linear 3-bucket partition.",
    "space_complexity": "O(N) -> Flat static arrays, ZERO dynamic allocation.",
    "formula_used": "max_visible = sum(min(freq[x], 2)); arrange as [1st_copies_asc, 3rd+_copies, 2nd_copies_desc]"
}
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

// Flat static arrays for L1 cache locality and zero heap overhead
int h[MAXN];
int left_w[MAXN];
int mid_e[MAXN];
int right_w[MAXN];

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    sort(h, h + n);

    int l_sz = 0, m_sz = 0, r_sz = 0;
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0 || h[i] != h[i - 1]) {
            cnt = 1;
            left_w[l_sz++] = h[i];
        } else {
            cnt++;
            if (cnt == 2) {
                right_w[r_sz++] = h[i];
            } else {
                mid_e[m_sz++] = h[i];
            }
        }
    }

    // Maximum visible books = every 1st copy (from left) + every 2nd copy (from right)
    cout << (l_sz + r_sz) << '\n';

    bool first = true;
    auto print_val = [&](int x) {
        if (!first) cout << ' ';
        cout << x;
        first = false;
    };

    // 1. Ascending left wing
    for (int i = 0; i < l_sz; i++) print_val(left_w[i]);
    // 2. Hidden extra duplicates in the middle
    for (int i = 0; i < m_sz; i++) print_val(mid_e[i]);
    // 3. Descending right wing
    for (int i = r_sz - 1; i >= 0; i--) print_val(right_w[i]);

    cout << '\n';
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
