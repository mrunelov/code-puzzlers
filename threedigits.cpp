/*
 * Three Digits
 * https://kth.kattis.scrool.se/problems/threedigits 
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() { 
    long N;
    long n = 1;
    long numFivesSkipped = 0;
    long numTwosSkipped = 0;
    scanf("%ld", &N);
    for (long i = 2; i <= N; ++i) {
        long m = i;
        while(m%2 == 0 || m%5 == 0) {
            if (m%2 == 0) {
                m = m/2;
                ++numTwosSkipped;
            }
            if (m%5 == 0) {
                m = m/5;
                ++numFivesSkipped;
            }
        }
        // cout << "m: " << m << endl;
        n = n*m % 1000;
    }
    // cout << "fives skipped: " << numFivesSkipped << ", twos skipped: " << numTwosSkipped << endl; 
    while(numFivesSkipped < numTwosSkipped) {
        n = n*2 % 1000;
        --numTwosSkipped;
    }
    if (N >= 7) {
        cout.fill('0');
        cout.width(3);
    }
    cout << n << endl;

    return 0;
}