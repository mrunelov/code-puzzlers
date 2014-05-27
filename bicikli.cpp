/*
 * Bicikli
 * https://kth.kattis.scrool.se/problems/bicikli
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

struct edge {
    int v;
    bool visited;
    edge() {}
    edge(int v) : v(v) { visited = false; }
};

typedef vector< vector<edge> > graph;

void bfs(graph& G, int start);
void topSort(graph& G, vector<int> inDeg);
// same as visited but requires two visits, one from start, one from end with reverse edges
vector<int> status; // city status. 0 = disconnected, 1 = reachable from start, 2 = reachable from start AND can reach end.

graph G(10000,vector<edge>());
graph revG(10000,vector<edge>()); // used to find what can reach city 2 (end)
vector<int> ts;
vector<int> inDeg;

int N;

int main() {
    int M, u, v;
    scanf("%d %d", &N, &M);
    // G.resize(N,vector<edge>());
    // revG.resize(N,vector<edge>());
    status.resize(N,0);
    inDeg.resize(N,0);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &u, &v);
        --u; --v; // 0-indexing
        G[u].emplace_back(v);
        revG[v].emplace_back(u);
        ++inDeg[v];
    }
    bfs(G,0); // reachable from start
    bfs(revG, 1); // can reach end
    if (status[0] != 2) {
        cout << "0" << endl;
        return 0;
    }

    // update inDegrees after BFS
    for (int i = 0; i < N; ++i) {
        if (status[i] != 2) {
            for (int j = 0; j < G[i].size(); ++j) {
                --inDeg[G[i][j].v];
            }
        }
    }

    topSort(G, inDeg);
    // cout << "statuses:" << endl;
    // for (int i = 0; i < N; ++i) {
    //     if (status[i] == 2 || status[i] == -1)
    //         cout << "city " << i+1 << " is connected." << endl;
    //     for (int j = 0; j < G[i].size(); ++j) {
    //         if (G[i][j].visited)
    //             cout << "    --> " << G[i][j].v+1 <<  " visited!" << endl;
    //     }
    // }


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < G[i].size(); ++j) {
            if (!G[i][j].visited && status[i] == 2 && status[G[i][j].v] == 2) {
                // cout << "topsort didn't visit (" << i << "," << G[i][j].v << ")" << endl;
                cout << "inf" << endl;
                return 0;
            }
        }
    }
    vector<int> nPaths(N,0);
    nPaths[0] = 1;
    bool overflow = false;
    for (int i = 1; i < ts.size(); ++i) { 
        int city = ts[i];
        // cout << ts[i]+1 << " ";
        for (int j = 0; j < revG[city].size(); ++j) { // check edges into city
            // cout << "checking edge from " << revG[ts[i]][j].v+1 << endl;
            nPaths[city] += nPaths[revG[city][j].v];
            if (nPaths[city] >= 1e9) {
                overflow = true;
                nPaths[city] -= 1e9;
            }
            // cout << "nPaths[" << i << "] = " << nPaths[ts[i]] << endl;
        }
        if (city == 1)
            break;
    }
    // cout << endl;
    if (overflow) printf("%09d\n", nPaths[1]); // 0-padding printing when overflow occured
    else printf("%d\n", nPaths[1]);

    return 0;
}

void topSort(graph& G, vector<int> inDeg) {
    // http://en.wikipedia.org/wiki/Topological_sorting
    vector<int> S;
    for (int i = N-1; i >= 1; --i) { // find nodes without incoming edges
        if (inDeg[i] == 0) {
            S.push_back(i);
        }
    }
    S.push_back(0);
    while(!S.empty()) {
        int u = S.back();
        S.pop_back();
        ts.push_back(u);
        for (int i = 0; i < G[u].size(); ++i) {
            edge& e = G[u][i];
            int v = e.v;
            if (!e.visited && status[v] == 2) {
                e.visited = true;
                --inDeg[v];
                if (inDeg[v] == 0)
                    S.push_back(v);
            }
        }
    }
}

void bfs(vector< vector<edge> >& g, int start) {
    queue<int> q;
    q.push(start);
    status[start] = start+1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            edge& e = g[u][i];
            int v = e.v;
            if (status[v] == start) { // makes use of the fact that end == 1. CAREFUL
                ++status[v];
                q.push(v);
            }
        }
    }
}