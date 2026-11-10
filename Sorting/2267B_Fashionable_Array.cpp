/*
{
    "problem_name": "Fashionable Array",
    "category": "Greedy / Sorting",
    "time_complexity": "O(N log N) -> Single pass grouping followed by custom sort.",
    "space_complexity": "O(N) -> Map and vector storage for elements.",
    "formula_used": "Sort by occurrence rank (ascending), then by value (descending)"
}
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void solve() {
    int n;
    cin >> n;

    // We will store pairs of {occurrence_rank, value}
    // occurrence_rank is 1 for the first time we see 'x', 2 for the second time, etc.
    vector<pair<int, int>> elements;
    map<int, int> freq;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        freq[val]++;
        elements.push_back({freq[val], val});
    }

    // Sort: primary key is rank (ascending), secondary key is value (descending)
    sort(elements.begin(), elements.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        if (x.first != y.first) {
            return x.first < y.first;
        }
        return x.second > y.second; // Tie-breaker: largest value wins
    });

    // Output the optimally rearranged array
    for (int i = 0; i < n; i++) {
        cout << elements[i].second << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
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
