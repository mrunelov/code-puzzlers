#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

/*
 * So you want to be a 2^n-aire?
 * https://kth.kattis.scrool.se/problems/2naire
 *
 * @author Martin Runelöv
 */

using namespace std;


//
// The expected value is the probabilty of a value times the value.
// This can be defined recursively, and calculated iteratively backwards.
// Keep in mind: the breakpoint where the probability is high enough for us to
// choose to answer the question. If this is lower than t, we don't add any stop-value.
// (stop == do not answer, next = answer next question).
// Maybe flip the loop to more easily debug.
int main() {
    int n;
    double t;
    while(scanf("%d %lf", &n, &t) == 2) {
        if (n == 0 && t == 0)
            break;
        double next = (double) (1 << n); // 2^n. maximal winnings.
        for (int i = 1; i <= n; ++i) { // backwards from last question.
            double stop = (double) (1 << (n-i)); // 2^(n-i). winnings for stopping.
            double breakpoint = (double)stop/next; 
            if (breakpoint < t) { // we always choose to answer. no stopping.
                breakpoint = t; // adjust breakpoint to be within limits.
                stop = 0;
            }
            else {
                stop = (breakpoint-t)*stop; // size of stop interval = (breakpt - t). constant.
            }
            double lh = 0.5; // left hand side of integral solution
            double rh = (breakpoint*breakpoint)/2; // right hand side
            next = (lh-rh)*next; // integral value for p
            // cout << "stop: " << stop << endl;
            // cout << "next: " << next << endl;
            next = (stop+next)*(1.0/(1-t)); // total expected value
        }
        printf("%0.3lf\n", next);
    }
}