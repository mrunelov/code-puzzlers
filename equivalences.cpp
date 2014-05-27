/*
 * Proving Equivalences
 * https://kth.kattis.scrool.se/problems/equivalences
 *
 * @author Martin Runelöv
 *
 * General idea:
 * Being in the same strongly connected component means that there is an equivalence relation within the SCC.
 * Binding all SCC's together is the goal. Connecting two SCC's requires an edge in both directions somewhere.
 * So, we check outgoing edges and incoming edges for each SCC and check how many are missing in total.
 * It is sufficient to count them since if there are two matching they are in the same SCC already and won't be counted.
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>

using namespace std;

typedef vector< vector<int> > graph;
graph G;
int N, idx, C;
vector<int> indices;
vector<int> lowlink;
vector<int> component;
vector<pair<int,int> > comp_to_node;
stack<int> S;
vector<bool> inS;
void scc(graph& G);
void strongconnect(graph& G, int node);
void reset();
void init();

using namespace std;


int main() {
    int t, M, u, v;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &N, &M);
        init();
        for (int i = 0; i < M; ++i) {
            scanf("%d %d", &u, &v);
            --u; --v; // 0-indexing
            G[u].push_back(v);
        }
        scc(G);
        if (C == 1) { // only one SCC. problem solved.
            cout << "0" << endl;
        }
        else {
            // calculate inDeg and outDeg between components by subtracting degrees within SCC's
            vector<int> compout(C,0);
            vector<int> compin(C,0);
            for (int u = 0; u < N; ++u) {
                for (int i = 0; i < G[u].size(); ++i) {
                    int v = G[u][i];
                    if (component[u] != component[v]) {
                        compout[component[u]]++;
                        compin[component[v]]++;
                    }
                }
            }
            // out from one is in for another.
            // out + in for two connects them.
            // (1,2,3): (1)->(2) and (1)->(3) can be connected
            // through one out from (3) and one out from (2)

            // Reworked. should work but double check compin/compout otherwise
            int in = 0; // how many incoming connections are missing
            int out = 0; // how many outcoming are missing
            for (int i = 0; i < C; ++i) {
                if (compin[i] == 0)
                    ++in;
                if (compout[i] == 0)
                    ++out;
            }
            cout << max(in,out) << endl;

            // for (int i = 0; i < N; ++i) {
            //     cout << "Node " << i << ", component " << component[i] << endl; 
            // }
        }
        if (t > 0)
            reset();
    }
    return 0;
}

void scc(graph& G) {
    for (int i = 0; i < N; ++i) {
        if (indices[i] == -1)
            strongconnect(G,i);
    }
}

void strongconnect(graph& G, int node) {
    // cout << "strongconnect called with " << node << endl;
    indices[node] = idx;
    lowlink[node] = idx;
    ++idx;
    S.push(node);
    inS[node] = true;
    for (int i = 0; i < G[node].size(); ++i) {
        int v = G[node][i];
        if (indices[v] == -1) {
            strongconnect(G,v);
            lowlink[node] = min(lowlink[node], lowlink[v]);
        }
        else if (inS[v]) {
            lowlink[node] = min(lowlink[node], indices[v]);
        }
    }
    if (lowlink[node] == indices[node]) {
        int n = -1;
        while(n != node) {
            n = S.top();
            S.pop();
            inS[n] = false;
            component[n] = C;
            comp_to_node.emplace_back(C,n);
        }
        ++C; // new component index for next component
    }
}


void init() {
    idx = 0;
    C = 0;
    G.resize(N);
    indices.resize(N,-1);
    lowlink.resize(N,-1);
    inS.resize(N,false); 
    component.resize(N,-1);
    comp_to_node.emplace_back(-1,-1); // dummy to end loop
}


void reset() {
    G.clear();
    indices.clear();
    lowlink.clear();
    component.clear();
    comp_to_node.clear();
    inS.clear();
    while(!S.empty()) // clear S
        S.pop();
}


