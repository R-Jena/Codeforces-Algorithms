/*
{
    "problem_name": "Problem from Malinovka",
    "category": "Math / Number Theory / Graphs",
    "time_complexity": "O(N sqrt(N) * density) -> Bit-packed L3-cache-friendly triangle listing.",
    "space_complexity": "O(N log N) -> Compressed uint16_t/uint32_t flat arrays (~19 MB).",
    "formula_used": "x=pq*u^2, y=qr*v^2, z=rp*w^2; p=1 folded on-the-fly, p>=2 via single-fetch tag_w[]"
}
*/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <numeric>
#include <cstdint>
#include <cstring>

using namespace std;

const int MAXN = 1000005;
const int MAXM = 1005;
const int MAXE = 2000005;

uint8_t sqfree[MAXN];
uint16_t isqrt_arr[MAXN];

// Compressed flat CSR adjacency list (q >= 2 only)
int adj_r[MAXE];
uint16_t adj_f[MAXE];
int start_idx[MAXM];
int end_idx[MAXM];

// Bit-packed: upper 16 bits = tag, lower 16 bits = w_p[r] (1 cache fetch instead of 2)
uint32_t tag_w[MAXN];
uint32_t timer = 0;

void precompute() {
    memset(sqfree, 1, sizeof(sqfree));
    sqfree[0] = 0;
    for (int i = 2; i * i < MAXN; i++) {
        if (sqfree[i]) {
            int sq = i * i;
            for (int j = sq; j < MAXN; j += sq) {
                sqfree[j] = 0;
            }
        }
    }
    uint16_t root = 0;
    for (int i = 1; i < MAXN; i++) {
        while ((int)(root + 1) * (root + 1) <= i) root++;
        isqrt_arr[i] = root;
    }
}

void solve() {
    int n;
    cin >> n;

    int m = isqrt_arr[n];
    long long f1 = m;

    // Case 1: p = q = r = 1
    long long ans = f1 * f1 * f1;

    // Case 2: Two are 1, one is r > 1 (3 permutations)
    long long case2 = 0;
    for (int r = 2; r <= n; r++) {
        if (sqfree[r]) {
            long long fr = isqrt_arr[n / r];
            case2 += fr * fr;
        }
    }
    ans += 3LL * f1 * case2;

    // Build flat adjacency list for 2 <= q <= m, folding p = 1 on-the-fly
    int edge_cnt = 0;
    long long case3 = 0;

    for (int q = 2; q <= m; q++) {
        start_idx[q] = edge_cnt;
        if (!sqfree[q]) {
            end_idx[q] = edge_cnt;
            continue;
        }
        int lim = n / q;
        long long fq = isqrt_arr[lim];
        long long p1_inner = 0;

        for (int r = q + 1; r <= lim; r++) {
            if (sqfree[r] && gcd(q, r) == 1) {
                uint16_t fqr = isqrt_arr[n / (q * r)];
                adj_r[edge_cnt] = r;
                adj_f[edge_cnt] = fqr;
                edge_cnt++;
                p1_inner += 1LL * fqr * isqrt_arr[n / r];
            }
        }
        case3 += fq * p1_inner;
        end_idx[q] = edge_cnt;
    }

    // Case 3 (remaining): 2 <= p < q < r
    for (int p = 2; p <= m; p++) {
        if (!sqfree[p]) continue;

        if (++timer == 65535u) {
            memset(tag_w, 0, sizeof(tag_w));
            timer = 1;
        }
        uint32_t tag = timer << 16;

        int p_start = start_idx[p];
        int p_end = end_idx[p];

        for (int i = p_start; i < p_end; i++) {
            tag_w[adj_r[i]] = tag | adj_f[i];
        }

        for (int i = p_start; i < p_end; i++) {
            int q = adj_r[i];
            if (q > m) break;

            long long inner = 0;
            int q_start = start_idx[q];
            int q_end = end_idx[q];

            for (int j = q_start; j < q_end; j++) {
                uint32_t tw = tag_w[adj_r[j]];
                if ((tw & 0xFFFF0000u) == tag) {
                    inner += 1LL * adj_f[j] * (tw & 0xFFFFu);
                }
            }
            case3 += 1LL * adj_f[i] * inner;
        }
    }

    ans += 6LL * case3;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
