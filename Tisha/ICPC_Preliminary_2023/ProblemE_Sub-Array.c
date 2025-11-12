/*
Problem:
Count how many subarrays are NOT Beautiful.
A Beautiful subarray has all identical elements.

Goal:
For each test case, find:
   Total subarrays - Beautiful subarrays


A sequence of same numbers of length L forms (L*(L+1))/2 Beautiful subarrays.
*/ 

#include <stdio.h>
int main() {
    int T;
    scanf("%d", &T); 

    for (int cas = 1; cas <= T; cas++) {
        int N;
        scanf("%d", &N);

        long long A[N];
        for (int i = 0; i < N; i++) scanf("%lld", &A[i]);

        long long total = (long long)N * (N + 1) / 2; 
        long long beautiful = 0; 
        long long count = 1; 

        for (int i = 1; i < N; i++) {
            if (A[i] == A[i - 1]) {
                count++;
            } else {
                // Add all beautiful subarrays from the previous segment
                beautiful += (count * (count + 1)) / 2;
                count = 1; // reset for new number
            }
        }

        // Add the last segment
        beautiful += (count * (count + 1)) / 2;

        long long notBeautiful = total - beautiful;

        printf("Case %d: %lld\n", cas, notBeautiful);
    }

    return 0;
}
