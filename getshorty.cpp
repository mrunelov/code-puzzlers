/*
 * Get Shorty
 * https://kth.kattis.scrool.se/problems/getshorty
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

struct Edge {
    int v; // end of edge
    double w;
    Edge() {}
    Edge(int v, double w) : v(v), w(w) {}
};

struct Comp {
    bool operator()(pair<int,double> const& a, pair<int,double> const& b) const {
        return a.second < b.second;
    }
};

struct Node {
    vector<Edge> adj;
};

double dijkstra();

vector<Node> G;
int N;

int main() {
    int M, u, v;
    double w;
    while(scanf("%d%d",&N,&M) && (N != 0 && M != 0)) {
        G.resize(N);
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %lf",&u,&v,&w);
            G[u].adj.emplace_back(v,w);
            G[v].adj.emplace_back(u,w);
        }
        printf("%.4f\n", dijkstra());
        G.clear();
    }
    return 0;
}

double dijkstra() {
    vector<double> fraction(N,-1); // fraction = reverse dist
    fraction[0] = 1; // start fraction
    priority_queue<pair<int,double>, vector<pair<int,double> >, Comp > pq;
    pq.push(make_pair(0,1.0));
    pair<int,double> curr;
    int node, f;
    while(!pq.empty()) {
        curr = pq.top();
        pq.pop();
        node = curr.first;
        if (node == N-1)
            return curr.second;
        for (int i = 0; i < G[node].adj.size(); ++i) {
            double newF = curr.second*G[node].adj[i].w;
            if(fraction[G[node].adj[i].v] < newF) {
                fraction[G[node].adj[i].v] = newF;
                pq.push(make_pair(G[node].adj[i].v, newF));
            }
        }
    }
}