/*
{
    "problem_name": "Stubborn Pen",
    "category": "Strings / Greedy",
    "time_complexity": "O(N) -> Single linear pass over stack buffer.",
    "space_complexity": "O(1) -> Fixed 105-byte stack char array, ZERO heap allocation.",
    "formula_used": "switches = (s[0] == 'B') + count(s[i] == s[i - 1])"
}
*/
#include <iostream>

using namespace std;

void solve() {
    int n;
    char s[105];
    cin >> n >> s;

    int switches = (s[0] == 'B');
    for (int i = 1; i < n; i++) {
        switches += (s[i] == s[i - 1]);
    }

    cout << switches << '\n';
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
