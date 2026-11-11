/*
{
    "problem_name": "101",
    "category": "Greedy / Constructive Algorithms",
    "time_complexity": "O(N) -> Single pass from left and right.",
    "space_complexity": "O(1) -> In-place modification of array.",
    "formula_used": "Find leftmost possible 1 and rightmost possible 1, make everything between them 0."
}
*/
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int first_one = -1;
    int last_one = -1;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Find leftmost candidate for 1
    for (int i = 0; i < n; i++) {
        if (a[i] == 1 || a[i] == -1) {
            first_one = i;
            break;
        }
    }

    // Find rightmost candidate for 1
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 1 || a[i] == -1) {
            last_one = i;
            break;
        }
    }

    // If we found valid boundaries, set them to 1.
    // If first_one == last_one, we just set that single element to 1.
    if (first_one != -1) {
        a[first_one] = 1;
        if (last_one != first_one && last_one != -1) {
             a[last_one] = 1;
        }
    }

    // Convert all remaining -1s to 0s
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) {
            a[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    // Fast I/O
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
