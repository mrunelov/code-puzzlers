/*
 * Life Forms
 * https://kth.kattis.scrool.se/problems/lifeforms
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

 using namespace std;

#define rep(i,n) for(int i=0; i < (n); ++i)
#define For(i,n) for(int i=1; i <= (n); ++i)
#define MAX 100107

// "Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its Applications"
// LCP[i] = length of the longest common prefix of suffix SA[i] and suffix SA[i-1]

int chars[MAX]; // input strings
int r[MAX], SA[MAX]; //output (r = rank)
int pos[MAX];
int tmp[MAX];
int LCP[MAX]; // longest common prefix
int w[MAX]; // word mapping
int N, S, gap;
bool hasLCP = false;


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
                hasLCP = true;
            }
        }
    }
}
 
bool findLCS(int x, int SAsize, bool print) {
    // cout << "findLCS called with " << x << endl;
    bool counted[N];
    int count;
    for (int i = 1; i < SAsize; ++i) {
        if (LCP[i] >= x) {
            rep(i, N) counted[i] = false;
            count = 1;
            counted[w[SA[i-1]]] = true;
            int j = i;
            while (j < SAsize && LCP[j] >= x) { // check prefix
                if (w[SA[j]] != w[SA[j]+x-1]) { // switched suffix
                    break;
                }
                if (!counted[w[SA[j]]]) {
                    counted[w[SA[j]]] = true;
                    ++count;
                }
                ++j;
            }
            if (count > N/2) {
                if (print) {
                    printf("%c", 'a' + chars[SA[i]]); // always print at least 1 char
                    for (int k = 1; k < x; ++k) {
                        printf("%c", 'a' + chars[SA[i]+k]);
                    }
                    printf("\n");
                }
                else { // continue when printing, but one hit is enough for decisions
                    return true;
                }
            }
            i = j-1; // skip forward
        }
    }
    return false;
}


int main() {
    int T, SAsize, longestWord = -1;
    string line;
    while (scanf("%d", &N) == 1 && N != 0) {
        SAsize = 0;
        getline(cin, line); // remove end of line
        rep(i,N) {
            getline(cin, line);
            if (line.length() - longestWord > 0)
                longestWord = line.length();
            for (int j = 0; j < line.length(); ++j) {
                // cout << "setting w[" << SAsize << "] = " << i << " for word " << line << endl;
                w[SAsize] = i;
                chars[SAsize++] = line[j] - 'a';
            }
            chars[SAsize++] = 27+i; // unique end-of-string-character
            chars[SAsize] = 0;
        }
        chars[SAsize-1] = 0;

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
        // printf("\n");
        // cout << "built SA and LCP" << endl;
        // binary search for answers
        int low = 1, best = -1;
        int high = longestWord;
        if (hasLCP) {
            while (high >= low) {
                int mid = low + (high-low)/2;
                if (findLCS(mid, SAsize, false)) {
                    low = mid + 1;
                    best = max(mid,best);
                }
                else
                    high = mid - 1;
            }
        }
        if (best != -1) {
            findLCS(best, SAsize, true);
        }
        else
            printf ("?\n");
        printf ("\n");
     }
    return 0;
}


