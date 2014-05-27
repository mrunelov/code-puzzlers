/*
 * CD
 * https://kth.kattis.scrool.se/problems/cd
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
#include <algorithm>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::min;
using std::max;

bool binary_search(uint32_t x, int imin, int imax);

uint32_t A[1000000];
int prevIndex;


// TODO: try set, 
int main() {
    int N, M, i, duplicates;
    uint32_t c, highest;
    while(scanf("%u%u", &N, &M)) {
        duplicates = 0;
        prevIndex = 0;
        if (N == 0 && M == 0) // no more testcases if 0 0
            break;
        memset(A, 0, sizeof(A));
        for (int i = 0; i < N; ++i) scanf("%u", &A[i]);
        highest = A[N-1];
        for (i = 0; i < M; ++i) {
            scanf("%u", &c);
            if (c > highest)
                continue;
            if(binary_search(c,prevIndex,N))
                ++duplicates;
        }
        printf("%d\n", duplicates);
    }
    return 0;
}

bool binary_search(uint32_t x, int imin, int imax) {
    while(imax >= imin) {
        int imid = imin + ((imax-imin)/2);
        if (A[imid] == x) {
            prevIndex = imid;
            return true;
        }
        else if (A[imid] < x)
            imin = imid+1;
        else 
            imax = imid-1;
    }
    return false;
}



// set solution. slow.

// set<uint32_t> A;
// if (N == 0 && M == 0)
//     break;
// duplicates = 0;

// for (i = 0; i < N; ++i) {
//     scanf("%u", &c);
//     A.insert(c);
// }
// for (int i = 0; i < M; ++i) {
//     scanf("%u", &c);
//     if (A.find(c) != A.end())
//         ++duplicates;
// }

