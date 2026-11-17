/*
{
    "problem_name": "Alice, Bob and Stones",
    "category": "Game Theory / Math",
    "time_complexity": "O(N) -> Single pass parity calculation.",
    "space_complexity": "O(1) -> Zero memory allocation overhead.",
    "formula_used": "Game is fixed-length. Moves parity depends only on piles where i % (k + 1) == 1."
}
*/
#include <iostream>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    int total_parity = 0;

    // We only care about piles that contribute an ODD number of descendant moves.
    // Mathematically, these are exactly the piles at 1-based index i where i % (k + 1) == 1.
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a;

        if (i % (k + 1) == 1) {
            // Since we only care about even/odd moves, we XOR the parity of the stone count
            total_parity ^= (a & 1);
        }
    }

    // In a normal play fixed-length game, Odd total moves means First player (Alice) wins.
    if (total_parity) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
}

int main() {
    // Hardware-level I/O bypass for max execution speed
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
