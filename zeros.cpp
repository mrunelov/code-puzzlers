#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

/*
 * How many 0's?
 * https://kth.kattis.scrool.se/problems/howmanyzeros
 *
 * @author Martin Runelöv
 */

using namespace std;

/* returns the ith digit of N */
long long digitAt(long long N, long long i) {
    return (N/(long long)pow(10,i))%10;
}

/* Calculates the number of digits in N */
long long numDigits(long long N) {
    long long digits = 0;
    while (N != 0) {
        N /= 10;
        ++digits;
    }
    return digits;
}

/* 
 * Returns the number of zeroes in all natural numbers in the interval 0-N
 */
long long numZeroesFromZero(long long N) {
    // a = number of zeroes
    // b = number so far
    // c = zeroes so far
    long long a = 0, b = 0, c = 0;
    long long digits = numDigits(N);
    for (long long i = digits-1; i >= 0; --i) { // loop over all digits, left to right.
        long long digit = digitAt(N,i);
        a = (10*a + b - c*(9-digit)); // main formula. the count of each digit is periodic
        if (digit == 0) {
            ++c;
        }
        b = (10*b + digit);
        // cout << "digit[" << i << "]: " << digit << endl;
        // cout << "a: " << a << endl;
        // cout << "b: " << b << endl;
        // cout << "c: " << c << endl;
        // cout << endl;
    }
    return a + 1;
}

int main() {
    long long M, N;
    while(scanf("%lld %lld", &M, &N) == 2 && M >= 0) {
        // for (long long i = 0; i < numDigits(N); ++i) {
        //     cout << digitAt(N, i) << endl;
        // }
        // printf("N: %d\n", numZeroesFromZero(N));
        // printf("M-1: %d\n", numZeroesFromZero(M-1));
        long long a = numZeroesFromZero(N);
        long long b = M == 0 ? 0 : numZeroesFromZero(M-1);
        printf("%lld\n", a-b);
    } 
}