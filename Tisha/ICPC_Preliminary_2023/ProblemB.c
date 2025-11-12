/*
Problem:
We are given two numbers A and N.
For every i from 1 to N, find K(i) = |(i % A) - (i % (A - 1))| 
and add them all together.

Goal:
Find the total sum of K(i) for i = 1 to N.


The pattern of K(i) repeats every A * (A - 1),
so we can use that to calculate the answer faster.
*/


#include <stdio.h>
#include <stdlib.h>

// Function to calculate sum of |i % A - i % (A-1)| for one period of length A*(A-1)
long long sum_one_period(int A) {
    long long sum = 0;
    int period = A * (A - 1);
    for (int i = 1; i <= period; i++) {
        sum += abs(i % A - i % (A - 1));
    }
    return sum;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int cas = 1; cas <= T; cas++) {
        int A;
        long long N;
        scanf("%d %lld", &A, &N);

        long long period = (long long)A * (A - 1);
        long long sum_period = 0;

        // Compute sum for one full period
        for (int i = 1; i <= period; i++) {
            sum_period += abs(i % A - i % (A - 1));
        }

        // Number of full periods in N
        long long full_periods = N / period;
        long long remainder = N % period;

        long long total_sum = full_periods * sum_period;

        // Add remaining part
        for (long long i = 1; i <= remainder; i++) {
            total_sum += abs(i % A - i % (A - 1));
        }

        printf("Case %d: %lld\n", cas, total_sum);
    }

    return 0;
}
