#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Check if Alice can transform a -> b
int canAlice(int a, int b) {
    // Alice can reach b if all prime factors of b are in a
    return b % gcd(a, b) == 0;
}

// Check if Bob can transform array A -> B
int canBob(int *A, int *B, int N) {
    int i;
    int g = A[0];
    for (i = 1; i < N; i++)
        g = gcd(g, A[i]);
    
    for (i = 0; i < N; i++) {
        if (B[i] % A[i] != 0)
            return 0; 
        int ratio = B[i] / A[i];
        int tempG = g;
        while (tempG != 1) {
            int gg = gcd(tempG, ratio);
            if (gg == 1) break;
            ratio /= gg;
        }
        if (ratio != 1)
            return 0; 
    }
    return 1;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        int N;
        scanf("%d", &N);
        int A[N], B[N];
        for (int i = 0; i < N; i++) scanf("%d", &A[i]);
        for (int i = 0; i < N; i++) scanf("%d", &B[i]);

        int alice = 1, bob = 1;
        for (int i = 0; i < N; i++) {
            if (!canAlice(A[i], B[i]))
                alice = 0;
        }
        if (!canBob(A, B, N))
            bob = 0;

        printf("Case %d: %s %s\n", tc, alice ? "Yes" : "No", bob ? "Yes" : "No");
    }
    return 0;
}
