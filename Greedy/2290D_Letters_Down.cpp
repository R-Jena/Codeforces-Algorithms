/*
{
    "problem_name": "Letters Down",
    "category": "Greedy / Strings",
    "time_complexity": "O(N) -> Single pass with interval marking.",
    "space_complexity": "O(1) -> 26-element boolean array for the alphabet.",
    "formula_used": "Total unique alphabet adjacent edges required to bridge all differing pairs."
}
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    // Boolean array to track which x -> x-1 operations are absolutely necessary
    bool needed[26] = {false};

    // Traverse inwards to check palindrome pairs
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) {
            // Find the smaller and larger character of the mismatched pair
            int u = min(s[i], s[n - 1 - i]) - 'a';
            int v = max(s[i], s[n - 1 - i]) - 'a';

            // To make them equal, EVERY alphabet gap between them MUST be unlocked
            for (int j = u; j < v; j++) {
                needed[j] = true;
            }
        }
    }

    // The total minimum operations is just the number of unique gaps we had to unlock
    int min_ops = 0;
    for (int i = 0; i < 26; i++) {
        if (needed[i]) {
            min_ops++;
        }
    }

    cout << min_ops << "\n";
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
