#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);

    for (int cas = 1; cas <= T; cas++) {
        int N;
        scanf("%d", &N);
        long long A[N];
        for (int i = 0; i < N; i++) scanf("%lld", &A[i]);

        long long maxFront[N]; 
        long long minBack[N]; 

        maxFront[0] = 0; 
        for (int i = 1; i < N; i++) {
            maxFront[i] = (A[i-1] > maxFront[i-1]) ? A[i-1] : maxFront[i-1];
        }

        minBack[N-1] = 1e18; 
        for (int i = N-2; i >= 0; i--) {
            minBack[i] = (A[i+1] < minBack[i+1]) ? A[i+1] : minBack[i+1];
        }

        int found = 0;
        for (int i = 0; i < N; i++) {
            if (A[i] > maxFront[i] && A[i] < minBack[i]) {
                printf("Case %d: %d\n", cas, i+1); 
                found = 1;
                break;
            }
        }
        if (!found) printf("Case %d: Humanity is doomed!\n", cas);
    }

    return 0;
}
