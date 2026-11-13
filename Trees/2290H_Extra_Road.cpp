/*
{
    "problem_name": "Extra Road",
    "category": "Trees / Greedy",
    "time_complexity": "O(N) -> Pure array-based DFS traversing.",
    "space_complexity": "O(N) -> Flat static arrays (Forward Star), ZERO dynamic allocation.",
    "formula_used": "K = max(third_max_at_root, max_{x!=1}(second_max_at_x)); ans = n - K"
}
*/
#include <iostream>

using namespace std;

const int MAXN = 200005;

// Forward Star Graph Representation (Zero vector overhead)
int head[MAXN];
int to[MAXN << 1];
int nxt[MAXN << 1];
int sz[MAXN];

int K, edge_cnt;

// O(1) in-place edge addition
inline void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dfs(int u, int p) {
    sz[u] = 1;

    int max1 = 0, max2 = 0, max3 = 0;

    // Cache-friendly flat array traversal
    for (int e = head[u]; e; e = nxt[e]) {
        int v = to[e];
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];

            int s = sz[v];
            if (s > max1) {
                max3 = max2;
                max2 = max1;
                max1 = s;
            } else if (s > max2) {
                max3 = max2;
                max2 = s;
            } else if (s > max3) {
                max3 = s;
            }
        }
    }

    if (u == 1) {
        if (max3 > K) K = max3;
    } else {
        if (max2 > K) K = max2;
    }
}

void solve() {
    int n;
    cin >> n;

    // O(N) lightning-fast reset for flat arrays
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    K = 0;
    dfs(1, 0);

    cout << n - K << "\n";
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
