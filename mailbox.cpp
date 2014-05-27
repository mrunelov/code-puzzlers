/*
 * The mailbox manufacturers problem
 * https://kth.kattis.com/problems/mailbox
 *
 * @author Martin Runelöv
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::memset;

int test_mailbox(int k, int a, int b);

const int MAX_VALUE = 1e9;
int memo[11][101][101];

int main() {
    int num_cases, k, m;
    memset(memo, -1 , sizeof(memo));
    cin >> num_cases;
    for (int i = 0; i < num_cases; ++i) {
        cin >> k >> m;
        printf("%d\n", test_mailbox(k,0,m));
    }
    return 0;
}

int test_mailbox(int k, int a, int b) {
    if (k == 0)
        return MAX_VALUE;
    if (k == 1)
        return (b*(b+1))/2 - (a*(a+1))/2;
    if (a == b)
        return 0;

    if (memo[k][a][b] == -1) {
        int res = MAX_VALUE;
        for (int i = a+1; i <= b; ++i) {
            res = min(res, i+max(test_mailbox(k-1,a,i-1), test_mailbox(k,i,b)));
        }
        memo[k][a][b] = res;
    }
    return memo[k][a][b];
}



