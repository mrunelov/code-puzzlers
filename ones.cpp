/*
 * Ones
 * https://kth.kattis.scrool.se/problems/ones
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    // what about numbers that are already ones? not tested? guess not.
    int N, ones, count;
    while(scanf("%d", &N) == 1) {
        ones = 1;
        count = 1;
        while (ones % N != 0) {
            ones*= 10; // new no
            ones += 1;
            count++; // one more one added above
            // cout << ones << endl;
            // prevent overflow, doesn't ruin int calculation 
            // since we're just removing multiples of N and end when %N == 0
            // In other words: we're looking for the other prime(s) of 11111...
            ones = ones % N; 
        }
        cout << count << endl;
    }
    return 0;
}