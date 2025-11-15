#include <stdio.h>

#define MAXN 1000000
#define MOD 1000000007

int spf[MAXN+1], mob[MAXN+1];
long long fact[MAXN+5], invfact[MAXN+5];

long long modpow(long long a, long long e){
    long long r = 1;
    while (e){
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

long long nCk(int n, int k){
    if (k < 0 || k > n) return 0;
    return fact[n] * (invfact[k] * invfact[n-k] % MOD) % MOD;
}

void sieve(){
    mob[1] = 1;
    for (int i=2;i<=MAXN;i++){
        if (!spf[i]) {
            spf[i] = i;
            mob[i] = -1;
            for (long long j = 1LL*i*i; j <= MAXN; j += i){
                if (!spf[j]) spf[j] = i;
            }
        } else {
            int p = spf[i], x = i/p;
            mob[i] = (x % p == 0 ? 0 : -mob[x]);
        }
    }
}

int pf[20], pe[20], pf_cnt;
void factorize(int x){
    pf_cnt = 0;
    while (x > 1){
        int p = spf[x], e = 0;
        while (x % p == 0) x /= p, e++;
        pf[pf_cnt] = p;
        pe[pf_cnt] = e;
        pf_cnt++;
    }
}

int divs[4096], dcnt;
void gen_divs_rec(int idx, int cur){
    if (idx == pf_cnt){
        divs[dcnt++] = cur;
        return;
    }
    int p = pf[idx], v = 1;
    for (int i=0;i<=pe[idx];i++){
        gen_divs_rec(idx+1, cur*v);
        v *= p;
    }
}

int main(){
    sieve();

    fact[0] = 1;
    for (int i=1;i<=MAXN;i++) fact[i] = fact[i-1] * i % MOD;
    invfact[MAXN] = modpow(fact[MAXN], MOD-2);
    for (int i=MAXN; i>0; i--) invfact[i-1] = invfact[i] * i % MOD;

    int T;
    scanf("%d", &T);

    while (T--){
        int n, k;
        scanf("%d %d", &n, &k);
        int m = k + 1;

        int pd[10], pc = 0;
        int x = n, last = -1;

        while (x > 1){
            int p = spf[x];
            if (p != last) pd[pc++] = p;
            last = p;
            x /= p;
        }

        long long ans = 0;

        for (int i=0;i<pc;i++){
            int p = pd[i];
            int t = n / p;
            if (t < m) continue;

            factorize(t);
            dcnt = 0;
            gen_divs_rec(0, 1);

            long long sum = 0;
            for (int j=0;j<dcnt;j++){
                int d = divs[j];
                int mu = mob[d];
                if (mu == 0) continue;

                int q = t / d;
                if (q < m) continue;

                long long ways = nCk(q-1, m-1);
                sum = (sum + mu * ways) % MOD;
            }

            ans = (ans + sum) % MOD;
        }

        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }

    return 0;
}

