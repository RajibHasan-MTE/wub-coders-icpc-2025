#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 998244353LL

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        unsigned long long n;
        int k;
        scanf("%llu %d", &n, &k);

        int maxbit = 63 - __builtin_clzll(n);

        long long *dp = calloc(k + 3, sizeof(long long));
        long long *dpn = calloc(k + 3, sizeof(long long));
        long long *diff = calloc(k + 5, sizeof(long long));

        dp[0] = 1;

        for (int i = 0; i <= maxbit; i++) {
            int b = (n >> i) & 1ULL;

            for (int j = 0; j <= k + 2; j++) diff[j] = 0;

            for (int c = 0; c <= k; c++) {
                long long ways = dp[c];
                if (!ways) continue;

                int need = b ^ (c & 1);
                if (need > k) continue;

                int a_min = need;
                int a_max = a_min + 2 * ((k - a_min) / 2);

                long long cmin = (c + a_min - b) / 2;
                long long cmax = (c + a_max - b) / 2;

                if (cmax < 0) continue;
                if (cmin < 0) cmin = 0;
                if (cmin > k) continue;
                if (cmax > k) cmax = k;

                diff[cmin] = (diff[cmin] + ways) % MOD;
                diff[cmax + 1] = (diff[cmax + 1] - ways + MOD) % MOD;
            }

            long long cur = 0;
            for (int j = 0; j <= k; j++) {
                cur = (cur + diff[j]) % MOD;
                dpn[j] = cur;
            }

            for (int j = 0; j <= k; j++) {
                dp[j] = dpn[j];
                dpn[j] = 0;
            }
        }

        printf("%lld\n", dp[0] % MOD);

        free(dp);
        free(dpn);
        free(diff);
    }

    return 0;
}