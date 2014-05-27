/*
 * Ignore the garbage
 * https://kth.kattis.scrool.se/problems/ignore
 *
 * @author Martin Runelöv
 *
 * Idea:
 * There are 7 valid digits.
 * Labeling these 7 digits as 0-6 will give us a base 7 number.
 * converting K to base 7 and translating from these labels will give the Kth displayed no.
 * This is done iteratively.
 */

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main(){
    int K;
    string flip = "0125986"; // 6 and 9 swapped
    while(scanf("%d", &K) == 1) {
        while(K != 0) { 
            cout << "0125986"[K%7]; // print the corresponding flippable digit (translation!)
            K /= 7; // next digit
        }
        cout << endl;
    }
}