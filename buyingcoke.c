/*
 * Buying coke
 * https://kth.kattis.scrool.se/problems/coke
 *
 * @author Martin Runelöv
 */

#include <stdio.h>
#include <string.h>

 #define COKE_PRICE 8
 #define MAX_FIVE 151
 #define MAX_TEN 51
 #define MAX_COKES 151

int min(int a, int b);
int dp_buy_coke(int num_cokes, int twos, int tens, int total);
// int recursive_dp_buy_coke(int N, int fives, int tens);
// int m_total;
// int m_N;
int C[MAX_COKES][MAX_FIVE][MAX_TEN] = {{{0}}};


int main(int argc, char *argv[]) {
    int num_cases, num_cokes, ones, fives, tens, total, i;

    scanf("%d", &num_cases);
    for (i = 0; i < num_cases; ++i) {
        scanf("%d %d %d %d", &num_cokes, &ones, &fives, &tens);
        total = ones + 5*fives + 10*tens;
        printf("%d\n", dp_buy_coke(num_cokes, fives, tens, total));
        // recursive version:
        // m_total = total;
        // m_N = num_cokes;
        // printf("%d\n", recursive_dp_buy_coke(0, fives, tens));
        // memset(C, 0, sizeof(C));
    }
    return 0;
}

/*
 * Recursion (see below for recursive function):
 * X cokes bought with a minimum number of coins with a certain number of
 *  fives and tens is dependent on the minimum number of coins used with the remaining coins.
 * The DP matrix built shows the minimum number of coins used for X cokes bought with Y fives and Z tens.
 * The number of ones are irrelevant since the min_countimum number of coins min_countimizes the number of ones
 * and since the instance has a solution the number of ones is not a factor
 */
int dp_buy_coke(int N, int fives, int tens, int total) {
    int max_five = fives + tens;
    int i, j, n, min_count, ones, coins;
    // int C[MAX_COKES][MAX_FIVE][MAX_TEN] = {{{0}}};
    for (n = 1; n <= N; ++n) {
        for (i = 0; i <= max_five; ++i) {
            for (j = 0; j <= tens; ++j) {
                min_count = 1e9; // min_count = infinity
                ones = total - 5*i - 10*j;
                // if(ones < 0)
                //     continue; // not needed? don't think so.
                if (ones >= COKE_PRICE) {
                    coins = C[n-1][i][j] + COKE_PRICE;
                    if (coins < min_count) { min_count = coins; };
                }
                if (i >= 1 && ones >= 3) {
                    coins = C[n-1][i-1][j] + 4;
                    if(coins < min_count) { min_count = coins; };
                }
                // Special case: If we have a scenario where 1 coke was bought with 8 ones
                // and we now want one more coke and have a ten we can do:
                // 3 ones + 1 ten --> A five and a coke. A five + 3 ones --> A coke. Total: 8 coins for 2 cokes.
                if (j >= 1 && n >= 2) {
                    if (C[n-1][i][j-1] - C[n-2][i][j-1] == COKE_PRICE) {
                        coins = C[n-1][i][j-1] + 0; // + 0 to be explicit. See above comment.
                        if(coins < min_count) { min_count = coins; };
                    }
                }
                if (i >= 2) {
                    coins = C[n-1][i-2][j] + 2;
                    if(coins < min_count) { min_count = coins; };
                }
                if (j >= 1) {
                    coins = C[n-1][i][j-1] + 1;
                    if(coins < min_count) { min_count = coins; };
                }
                // printf("Setting C[%d][%d][%d] to %d\n", n,i,j,min_count);
                if (n == N && i == fives && j == tens) // shortcut to ignore max_fives excessive loop count
                    return min_count;
                C[n][i][j] = min_count;
            }
        }
    }
    return C[N][fives][tens];
} 

// int recursive_dp_buy_coke(int N, int fives, int tens) {
//     if (C[N][fives][tens] != 0) {
//         return C[N][fives][tens];
//     }
//     if (N == m_N) {
//         return C[N][fives][tens] = 0;
//     }
//     int ones = m_total - 5*fives - 10*tens; // TODO: figure out 8*N
//     int min_count = 1e9; // min_count = inf
//     if (ones >= 8) {
//         min_count = min(min_count, recursive_dp_buy_coke(N+1, fives, tens) + 8);
//     }
//     if (fives >= 2) {
//         min_count = min(min_count, recursive_dp_buy_coke(N+1, fives-2, tens) + 2);
//     }
//     if (tens >= 1) {
//         min_count = min(min_count, recursive_dp_buy_coke(N+1, fives, tens-1) + 1);    
//     }
//     if (fives >= 1 && ones >= 3) {
//         min_count = min(min_count, recursive_dp_buy_coke(N+1, fives-1, tens) + 4);
//     }
//     if (tens >= 1 && ones >= 3) {
//         min_count = min(min_count, recursive_dp_buy_coke(N+1, fives+1, tens-1) + 4);
//     }
//     return C[N][fives][tens] = min_count;
// }

int min (int a, int b) {
    return a <= b ? a : b;
}
