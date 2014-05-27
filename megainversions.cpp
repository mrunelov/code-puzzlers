/*
 * Mega Inversions
 * https://kth.kattis.scrool.se/problems/megainversions
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

void print_vector(vector<int> &v, int range);

int N;
int A[100001];
int P[100001];

struct fenwick_tree {
    int tree[100001];

    fenwick_tree() {
        memset(tree, sizeof(tree), 0);
    }

    void clear() {
        memset(tree, sizeof(tree), 0);
    }

    int cumulative_freq(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            // printf("tree[%d] = %d \n", idx, tree[idx]);
            idx -= idx&(-idx);
        }
        return sum;
    }

    int freq(int idx) { // one can also do sum = cumulative_freq[idx] - cumulative_freq[idx-1]
        int sum = tree[idx]; // sum to decrease
        if (idx > 0) { // special case, x == 0
            int z = idx - (idx&(-idx)); // make z first
            int y = idx - 1;
            while (y != z) {
                sum -= tree[y]; 
                idx -= idx&(-idx);
            }
        }
        return sum;
    }

    int interval_cumulative_freq(int a, int b) {
        // cout << "returning cumulative frequency for " << a << " and " << b  << ":  " << (cumulative_freq(b) - cumulative_freq(a-1)) << endl;
        return (cumulative_freq(b) - cumulative_freq(a-1));
    }    

    void update(int idx, int val) { //update cumulative frequencies
        // printf("update called with %d and %d\n", idx, val);
        while (idx <= N) {
            tree[idx] += val;
            // printf("tree[%d] += %d\n", idx, val);
            // printf("tree[%d] = %d\n", idx, tree[idx]);
            idx += idx&-idx;
        }
        // printf("\n");
    }

    void print_tree() {
        cout << "\ntree: ";
        for (int i = 0; i <= N; ++i) {
            cout << tree[i] << " ";
        }
        cout << "\n";
        // cout << "cumulative frequencies: ";
        // for (int i = 0; i <= N; ++i) {
        //     cout << cumulative_freq(i) << " ";
        // }
        // cout << "\n";
    }
};

int main() {
    int inversions = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
        P[i] = A[i];
    }

    // 2 binary indexed trees
    fenwick_tree ft_one;
    fenwick_tree ft_two;
    ft_one.clear();
    ft_two.clear();

    for (int i = 1; i <= N; ++i) {
        printf("using A[%d] = %d \n", i, A[i]);
        printf("updating q with idx = %d and val = %d\n", i, ft_one.interval_cumulative_freq(A[i]+1,N));
        ft_two.update(i, ft_one.interval_cumulative_freq(A[i]+1,N));
        ft_one.update(A[i], 1);
    }
    ft_one.print_tree();
    ft_two.print_tree();

    ft_one.clear();
    for (int i = 1; i <= N; ++i) {
        inversions += ft_one.interval_cumulative_freq(A[i],N);
        ft_one.update(A[i], ft_two.interval_cumulative_freq(i,i+1));
    }
    ft_one.print_tree();
    ft_two.print_tree();
    printf("%d\n", inversions);
    return 0;
}


void print_vector(vector<int> &v, int range) {
    copy(v.begin(), v.begin()+range, ostream_iterator<int>(cout, " "));
    cout << endl;
}