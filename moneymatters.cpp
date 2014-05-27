/*
 * Money Matters
 * https://kth.kattis.scrool.se/problems/moneymatters
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


vector< vector<int> > f(10000,vector<int>(10000));
long long debt[10000];
bool visited[10000];
long long sum;

void dfs(int node) {
    if (visited[node])
        return;
    visited[node] = true;
    sum += debt[node];
    for (int i = 0; i < f[node].size(); ++i) {
        if (!visited[f[node][i]])
            dfs(f[node][i]);
    }
}

int main() {
    int N, M, a, b;
    bool works = true;
    scanf("%d%d",&N,&M);
    for (int i = 0; i < N; ++i) { // debts/owed
        scanf("%lld", &debt[i]);
        visited[i] = false;
    }
    for (int i = 0; i < M; ++i) { // friendships
        scanf("%d%d",&a,&b);
        f[a].push_back(b);
        f[b].push_back(a);
    }

    for (int i = 0; i < N; ++i) {
        sum = 0;
        dfs(i);
        if(sum != 0){
            // cout << "Impossible at i = " << i << ", sum = " << sum << endl;
            works = false;
            break;
        }
    }

    if(works)
        cout << "POSSIBLE";
    else 
        cout << "IMPOSSIBLE";
    cout << endl;
}
