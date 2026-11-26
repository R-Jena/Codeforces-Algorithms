/*
{
    "problem_name": "Problem from Ust-Katav",
    "category": "Stacks / Math / Monotonic Stack",
    "time_complexity": "O(N) -> Single-pass monotonic stack without L/R arrays.",
    "space_complexity": "O(N) -> Only two flat int arrays (~1.6 MB), ZERO heap allocation.",
    "formula_used": "a = i - L[i], b = R[i] - i; contribution = (a == 1 || b == 1) ? (a + b - 1) : 2"
}
*/
#include <iostream>

using namespace std;

const int MAXN = 200005;
int p[MAXN];
int st[MAXN];

void solve() {
    int n;
    cin >> n;

    long long ans = 0;
    int top = 0;
    st[0] = 0; // Sentinel index
    p[0] = 0;  // Sentinel value (smaller than any permutation element)

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        while (top > 0 && p[st[top]] > p[i]) {
            int x = st[top--];
            int a = x - st[top];
            int b = i - x;
            ans += (a == 1 || b == 1) ? (a + b - 1) : 2;
        }
        st[++top] = i;
    }

    // Flush remaining elements with R = n + 1
    while (top > 0) {
        int x = st[top--];
        int a = x - st[top];
        int b = (n + 1) - x;
        ans += (a == 1 || b == 1) ? (a + b - 1) : 2;
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
