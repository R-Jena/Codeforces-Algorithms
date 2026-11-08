/*
{
    "problem_name": "MEX Game",
    "category": "Game Theory / Math",
    "time_complexity": "O(N) -> Single frequency pass.",
    "space_complexity": "O(N) -> Frequency array storage.",
    "formula_used": "Find smallest M where count[M] < 2k. Alice wins iff count[M] == 2k - 1."
}
*/
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    // Frequency array to store counts of each element
    // Elements are bounded by n, so size n+1 is perfect
    vector<int> freq(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a <= n) {
            freq[a]++;
        }
    }

    // Find the bottleneck MEX candidate (first element with count < 2k)
    for (int i = 0; i <= n; i++) {
        if (freq[i] < 2 * k) {
            // Alice can only secure 'k' copies if exactly 2k - 1 copies exist
            if (freq[i] == 2 * k - 1) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            return;
        }
    }
}

int main() {
    // Fast I/O for zero-overhead execution
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
