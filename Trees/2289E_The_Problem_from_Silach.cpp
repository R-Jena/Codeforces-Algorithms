/*
{
    "problem_name": "The Problem from Silach",
    "category": "Trees / Data Structures / Leftist Heap",
    "time_complexity": "O(N log N) -> Worst-case O(log N) Leftist Max-Heap merge & pop.",
    "space_complexity": "O(N) -> Flat static arrays, ZERO std::set / heap allocation.",
    "formula_used": "x in W(L) survives match u iff x < max(W(R)) + d; eliminated x gets ans[x] = dep[x] - dep[u]"
}
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MAXV = 400005;

int p1[MAXV], p2[MAXV];
int dep[MAXV];
int hroot[MAXV];

// Leftist Max-Heap on athlete IDs 1..n (node ID itself is the key)
int lc[MAXN], rc[MAXN], dist_h[MAXN];
int ans[MAXN];

inline int merge_heap(int a, int b) {
    if (!a || !b) return a | b;
    if (a < b) swap(a, b); // Max-heap: largest athlete number at root
    rc[a] = merge_heap(rc[a], b);
    if (dist_h[lc[a]] < dist_h[rc[a]]) swap(lc[a], rc[a]);
    dist_h[a] = dist_h[rc[a]] + 1;
    return a;
}

void solve() {
    int n, d;
    cin >> n >> d;

    int total = 2 * n - 1;
    for (int u = n + 1; u <= total; u++) {
        cin >> p1[u] >> p2[u];
    }

    // 1. Top-down depth calculation (zero DFS recursion)
    dep[total] = 0;
    for (int u = total; u >= n + 1; u--) {
        int nd = dep[u] + 1;
        dep[p1[u]] = nd;
        dep[p2[u]] = nd;
    }

    // 2. Initialize single-node Leftist Heaps for athletes 1..n
    for (int i = 1; i <= n; i++) {
        lc[i] = rc[i] = 0;
        dist_h[i] = 1;
        hroot[i] = i;
        ans[i] = dep[i]; // Default if athlete survives all the way to root
    }

    // 3. Bottom-up elimination and heap merging
    for (int u = n + 1; u <= total; u++) {
        int L = hroot[p1[u]];
        int R = hroot[p2[u]];

        int maxL = L; // Root of max-heap is the maximum element
        int maxR = R;

        int limL = maxR + d;
        while (L && L >= limL) {
            ans[L] = dep[L] - dep[u];
            L = merge_heap(lc[L], rc[L]);
        }

        int limR = maxL + d;
        while (R && R >= limR) {
            ans[R] = dep[R] - dep[u];
            R = merge_heap(lc[R], rc[R]);
        }

        hroot[u] = merge_heap(L, R);
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }
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
