/*
{
    "problem_name": "Three Piles",
    "category": "Math / Implementation",
    "time_complexity": "O(1) -> Direct arithmetic comparison.",
    "space_complexity": "O(1) -> Three stack integers, zero allocation.",
    "formula_used": "b - a == 1 && c - b == 1 (given a <= b <= c)"
}
*/
#include <iostream>

using namespace std;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    if (b - a == 1 && c - b == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
