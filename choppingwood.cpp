/*
 * Chopping Wood
 * https://kth.kattis.scrool.se/problems/chopwood
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;
using std::max;
using std::priority_queue;

int v[200000];

int main() {
    int vsize;
    scanf("%d", &vsize);
    for (int i = 0; i < vsize; ++i) scanf("%d", &v[i]);

    // Algorithm:
    if (v[vsize-1] != vsize+1) { // the last remaining element has to be the biggest node
        cout << "Error" << endl;
        return 0;
    }
    
    priority_queue<int, vector<int>, std::greater<int>> leaves; // greater as comparison function to prioritize smaller leaves
    vector<int> degree(vsize+1);
    for (int i = 0; i < vsize; ++i) ++degree[v[i]];
    for (int i = 1; i < (vsize+1); ++i) {
        if (degree[i] == 0) // initial leaf
            leaves.push(i);
    }
    if (leaves.empty()) { // no starting leaves. needed?
        cout << "Error" << endl;
        return 0;
    }

    for (int i = 0; i < vsize; ++i) {
        cout << leaves.top() << "\n";
        leaves.pop();
        --degree[v[i]];
        if (degree[v[i]] == 0)
            leaves.push(v[i]);
    }
    cout << std::flush;
    return 0;
}
