/*
 * Dvaput
 * https://kth.kattis.scrool.se/problems/dvaput
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i,n) for(int i=0; i < (n); ++i)
#define For(i,n) for(int i=1; i <= (n); ++i)
#define MAX 200001

// "Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its Applications"
// LCP[i] = length of the longest common prefix of suffix SA[i] and suffix SA[i-1]

int chars[MAX]; // input string
int r[MAX], SA[MAX]; //output (r = rank)
int pos[MAX], tmp[MAX];
int LCP[MAX]; // longest common prefix
int N, S, gap;
// int longestLCP = 0;

bool cmp(int i, int j) {
    if (pos[i] == pos[j]) {
        i += gap;
        j += gap;
        if (i < S && j < S)
            return pos[i] < pos[j];
        else
            return i > j;
    }
    return pos[i] < pos[j];
}


void buildSA() {
    for (int i = 0; i < S; ++i) {
        pos[i] = chars[i];
        SA[i] = i;      // assume order
        tmp[i] = 0;     // used to calculate pos[]
    }
    /*
    * 1: Sorting by 2^i-grams, using the lexicographic names from the previous iteration to enable comparisons in 2 steps (i.e. O(1) time) each
    * 2: Creating new lexicographic names
    */
    gap = 1;
    while (true) {
        //use previous pos (pos of 2^(i-1)-grams, stored in pos) to sort 2^i-grams
        sort(begin(SA), begin(SA) + S, cmp);

        // lexographic renaming => store the pos of each gram in the sorted bigrams (SA)
        rep(i, S-1) {
            int higher = cmp(SA[i], SA[i+1]);     //since SA is sorted, increment pairwise
            tmp[i+1] = tmp[i] + (higher ? 1 : 0);
        }
        rep(i, S) pos[SA[i]] = tmp[i]; // store 'previous' pos for each SA[i]
        if (tmp[S-1] >= S-1) // repeat until all 2i-grams are different
            break;
        gap = gap << 1; // next iteration we check 2^(i+1)-grams
    }
}


void buildLCP(int SAsize) {
    rep(i, SAsize) r[SA[i]] = i;
    LCP[0] = 0;
    int h = 0;
    for (int i = 0; i < SAsize; ++i) {
        if (r[i] == 0) {
            LCP[i] = 0;
            continue;
        }
        if (r[i] > 0) {
            int j = SA[r[i]-1];
            while (i+h < SAsize && j+h < SAsize && chars[i+h] == chars[j+h]) ++h;
            LCP[r[i]] = h;
            if (h > 0) {
                --h;
                // longestLCP = max(longestLCP, h);
            }
        }
    }
}

int getLRS() {
    int maxi = -1;
    for (int i = 0; i < S; ++i) {
        maxi = max(maxi,LCP[i]);
    }
    return maxi;
}



int main() {
    int SAsize;
    string line;
    scanf("%d", &N);
    SAsize = 0;
    getline(cin, line); // remove end of line
    getline(cin, line);
    for (int j = 0; j < N; ++j) {
        chars[SAsize++] = line[j] - 'a';
    }
    chars[SAsize] = 0;
    --SAsize;
    S = SAsize;
    buildSA();
    buildLCP(SAsize);
    // printf("Chars:\n");
    // for (int i = 0; i < SAsize; ++i) {
    //     printf("%c ", 'a' + chars[i]);
    // }
    // printf("\n");
    // printf("Suffix Array:\n");
    // for (int i = 0; i < SAsize; ++i) {
    //     printf("%d ", SA[i]);
    // }
    // printf("\n");
    // printf("LCP Array:\n");
    // for (int i = 0; i < SAsize; ++i) {
    //     printf("%d ", LCP[i]);
    // }
    printf ("%d\n", getLRS());
    return 0;
}
