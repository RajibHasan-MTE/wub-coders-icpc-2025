/*
Problem:

Given an array of positive integers and a number K, find the longest contiguous subarray that meets these rules:

Rules:
1. Exactly K "almost prime factors": primes that appear in some but not all numbers of the subarray.
2. No "perfect prime factors": primes that appear in every number of the subarray.

Goal:
- Find the longest subarray where the number of almost primes is exactly K
  and there are no perfect primes.
- Output the length of this longest subarray for each test case.

Example:
Array: [6, 10, 15], K = 2
- Subarray [6,10] has almost primes {3,5} but perfect prime 2 → invalid
- Subarray [10,15] has almost primes {2,3} but perfect prime 5 → invalid
- We need to check all subarrays and find the longest one that meets the rules.
*/



#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Count unique prime factors of x
int unique_primes(int x, int primes[]) {
    int count = 0;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            int found = 0;
            for (int j = 0; j < count; j++)
                if (primes[j] == i) found = 1;
            if (!found) primes[count++] = i;
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) {
        int found = 0;
        for (int j = 0; j < count; j++)
            if (primes[j] == x) found = 1;
        if (!found) primes[count++] = x;
    }
    return count;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; cas++) {
        int n, k;
        scanf("%d %d", &n, &k);
        int arr[n];
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int primes[100];
            int sub_gcd = arr[i];
            for (int j = i; j < n; j++) {
                if (j > i) sub_gcd = gcd(sub_gcd, arr[j]);
                int count = unique_primes(arr[j], primes);
                if (count > k) break;
                if (count == k && sub_gcd == 1) {
                    if (j - i + 1 > ans) ans = j - i + 1;
                }
            }
        }
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
