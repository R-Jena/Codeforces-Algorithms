/*
{
    "problem_name": "Turn Into a Palindrome",
    "category": "Two Pointers / Strings",
    "time_complexity": "O(N) -> Single inward pass.",
    "space_complexity": "O(1) -> In-place character checking.",
    "formula_used": "cost = 1 if one char is c, cost = 2 if neither is c for non-matching pairs"
}
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    char c;
    cin >> n >> c;

    string s;
    cin >> s;

    int coins = 0;
    int left = 0;
    int right = n - 1;

    // Traverse inwards from the edges
    while (left < right) {
        if (s[left] != s[right]) {
            // Mismatch found. Can we fix it with 1 coin or 2?
            if (s[left] == c || s[right] == c) {
                // One side is already the target character, only 1 operation needed
                coins += 1;
            } else {
                // Neither side is the target character, 2 operations needed
                coins += 2;
            }
        }
        left++;
        right--;
    }

    cout << coins << "\n";
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
