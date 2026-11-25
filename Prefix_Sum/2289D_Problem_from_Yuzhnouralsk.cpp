/*
{
    "problem_name": "Problem from Yuzhnouralsk",
    "category": "Prefix Sum / Divide and Conquer / Math",
    "time_complexity": "O(N log N) -> Flat-array Merge Sort inversion count.",
    "space_complexity": "O(N) -> Two static long long arrays (~3.2 MB), ZERO heap allocation.",
    "formula_used": "Op at i swaps P[i-1] and P[i]. Valid iff all P[k] >= 0; min ops = inversions(P[1..n])."
}
*/
#include <iostream>

using namespace std;

const int MAXN = 200005;
long long P[MAXN];
long long tmp[MAXN];

long long merge_count(int l, int r) {
    if (r - l <= 1) return 0;
    int mid = (l + r) >> 1;
    long long inv = merge_count(l, mid) + merge_count(mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (P[i] <= P[j]) {
            tmp[k++] = P[i++];
        } else {
            tmp[k++] = P[j++];
            inv += (mid - i);
        }
    }
    while (i < mid) tmp[k++] = P[i++];
    while (j < r) tmp[k++] = P[j++];

    for (int idx = l; idx < r; idx++) {
        P[idx] = tmp[idx];
    }
    return inv;
}

void solve() {
    int n;
    cin >> n;

    long long pref = 0;
    bool possible = true;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        pref += a;
        P[i] = pref;
        if (pref < 0) {
            possible = false;
        }
    }

    if (!possible) {
        cout << "-1\n";
        return;
    }

    cout << merge_count(0, n) << '\n';
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
