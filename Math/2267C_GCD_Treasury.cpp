/*
{
    "problem_name": "GCD Treasury",
    "category": "Math / Greedy / Number Theory",
    "time_complexity": "O(sqrt(X) + N * k) -> Factorize X only, then sweep array for each prime factor.",
    "space_complexity": "O(N) -> Array storage only.",
    "formula_used": "max over all prime factors 'p' of x: sum of all a_i where a_i % p == 0"
}
*/
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // If x is 1, gcd with anything is 1, so we can't make a single move
    if (x == 1) {
        cout << 0 << "\n";
        return;
    }

    // Find ONLY the unique prime factors of x
    vector<int> primes;
    int temp = x;
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            primes.push_back(i);
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp > 1) {
        primes.push_back(temp);
    }

    long long max_stolen = 0;

    // For every prime factor of x, calculate the maximum coins we can drain
    for (int p : primes) {
        long long current_sum = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % p == 0) {
                current_sum += a[i];
            }
        }
        if (current_sum > max_stolen) {
            max_stolen = current_sum;
        }
    }

    cout << max_stolen << "\n";
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
