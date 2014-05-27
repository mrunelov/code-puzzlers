/*
 * Uxuhul Voting
 * https://kth.kattis.scrool.se/problems/uxuhul
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int prefs[101][8];
int state[101][8]; 
int m;

// votestate = 3 bit number. 

void printvote(int votestate) {
    for (int i = 2; i >= 0; --i) {
        if (votestate & (1<<i)) // check bits from left to right
            printf("Y");
        else 
            printf("N");
    }
} 

// can be made with much less memory iteratively (DP), highest to lowest (7 -> 0)
int solve(int priest, int votestate) {
    // cout << "solve called with priest " << priest << " and votestate ";
    // printvote(votestate);
    // cout << " (" << votestate << ")" << endl;
    if (priest == m) // base case. no more priests, the state is final.
        return votestate;
    if (state[priest][votestate] != -1)
        return state[priest][votestate];
    bool first = true;
    int best, res;
    for (int i = 0; i < 3; ++i) { // for each possible flip
        // heart of the recursion. check all possible votings
        int vote = (votestate ^ (1 << i)); // flip the i'th bit/rock
        res = solve(priest+1, vote);
        if (first) {
            best = res;
            first = false;
        }
        else if (prefs[priest][res] < prefs[priest][best]) { // check preferences. lower is better
            // cout << "changed best from ";
            // printvote(res);
            // cout << " to ";
            // printvote(best);
            // cout << " for priest " << priest << endl;
            best = res;
        }
        // cout << "compared " << prefs[priest][res] << " and " << prefs[priest][best] << endl;
        // cout << "(res = ";
        //     printvote(res);
        //     cout << "), (best =  ";
        //     printvote(best);
        //     cout << ") " << endl;
    }
    return state[priest][votestate] = best;
}


int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        memset(state,-1,sizeof(state));
        scanf("%d", &m);
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 8; ++k) {
                scanf("%d", &prefs[j][k]);
                // printf("scanned prefs[%d][%d] = %d\n", j, k, prefs[j][k]);
            }
        }
        int res = solve(0,0); // starting at priest 0 with votestate 0 = NNN = bits 000
        printvote(res);
        printf("\n");
    }
    return 0;
}




