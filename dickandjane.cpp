/*
 * Dick and Jane
 * https://kth.kattis.scrool.se/problems/dickandjane
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

using namespace std;

int deltas[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{0,1,1},{1,0,1}};

bool is_ok(long a, long b, long c, long d, long j, long s, long p, long y) {
    if (a+b+c != d+j)
        return false;
    if (a-b < s || a-b > s+1)
        return false;
    if (b-c < p || b-c > p+1)
        return false;
    if (a-c < y || a-c > y+1)
        return false;
    return true;
}


int main() {
    long d = 12;
    long s,p,y,j,a,b,c;
    while(scanf("%ld %ld %ld %ld", &s, &p, &y, &j) == 4) {
        c = (d+j-p-y)/3; // integer division, floor
        a = y + c;
        b = p + c;
        bool first = true;
        int delta = 0;
        while(!is_ok(a,b,c,d,j,s,p,y)) {
            if (!first) {
                a -= deltas[delta-1][0];
                b -= deltas[delta-1][1];
                c -= deltas[delta-1][2];
            }
            if (first)
                first = false;
            a += deltas[delta][0];
            b += deltas[delta][1];
            c += deltas[delta][2];
            ++delta;
        }
        // if (!is_ok(a,b,c,d,j,s,p,y)) {
        //     ++a;
        //     if (!is_ok(a,b,c,d,j,s,p,y)) {
        //         --a;
        //         ++b;
        //         if (!is_ok(a,b,c,d,j,s,p,y)) {
        //             --b;
        //             ++c;
        //             if (!is_ok(a,b,c,d,j,s,p,y)) {
        //                 printf("IMPOSSIBLE\n");
        //             }
        //         }
        //     }
        // }
        printf("%ld %ld %ld\n", a,b,c);
    }
    return 0;
}