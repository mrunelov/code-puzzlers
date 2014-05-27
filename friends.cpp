/*
 * All Friends
 * https://kth.kattis.scrool.se/problems/friends
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;



void BronKerbosch(set<int> R, set<int> P, set<int> X);

vector<set<int> > graph;
int N; // size of graph
int numMaximalCliques;

int main() { 
    int M, u, v;
    while(scanf("%d %d", &N, &M) == 2) {
        graph.clear();
        graph.resize(N);
        numMaximalCliques = 0;
        for (int i = 0; i < M; ++i) {
            scanf("%d %d", &u, &v);
            --u; --v;
            graph[u].insert(v);
            graph[v].insert(u);
        }
        set<int> R, P, X;
        for (int i = 0; i < N; ++i) P.insert(i); // initialize P to all vertices
        BronKerbosch(R,P,X);
        if (numMaximalCliques > 1000) {
            cout << "Too many maximal sets of friends." << endl;
        }
        else 
            cout << numMaximalCliques << endl;
    }
    return 0;
}


void printSet(set<int> S) {
    set<int>::iterator it;
    cout << "(";
    for (it = S.begin(); it != S.end(); ++it) {
        cout << *it << ",";
    }
    cout << ")" << endl;
}

void BronKerbosch(set<int> R, set<int> P, set<int> X) {
    if (numMaximalCliques > 1000)
        return;
    // cout << "Sizes: " << R.size() << ", " << P.size() << ", " << X.size() << endl; 
    if (P.empty() && X.empty()) {
        ++numMaximalCliques;
        return;
    }
    int pivot;
    if (!P.empty())
        pivot = *P.begin();
    else 
        pivot = *X.begin();
    set<int> smartP;
    set_difference(P.begin(), P.end(), graph[pivot].begin(), graph[pivot].end(),
        insert_iterator<set<int> >(smartP, smartP.begin()));
    vector<int> Pv;
    set<int>::iterator it;
    for(it = smartP.begin(); it != smartP.end(); ++it) {
        Pv.push_back(*it);
    }
    // for(it = P.begin(); it != P.end();) {
    for(int i = 0; i < Pv.size(); ++i) {
        int v = Pv[i];
        // cout << "P.size: " << P.size() << endl;
        set<int>::iterator it2 = graph[pivot].find(v);
        if (it2 != graph[pivot].end()) {
            it++;
            continue;
        }
        // cout << "v: " << v << endl;
        set<int> PNv, XNv; // P ⋂ N(v), X ⋂ N(v)
        R.insert(v); // R ⋃ {v}
        set_intersection(P.begin(), P.end(), graph[v].begin(), graph[v].end(),
            insert_iterator<set<int> >(PNv, PNv.begin()));
        set_intersection(X.begin(), X.end(), graph[v].begin(), graph[v].end(),
            insert_iterator<set<int> >(XNv, XNv.begin()));
        BronKerbosch(R,PNv,XNv);
        // cout << " PNv: ";
        // printSet(PNv);
        // cout << " XNv: ";
        // printSet(XNv);
        X.insert(v);
        P.erase(v);
        // it++;
        // smartP.erase(it++);
    }
    return;
}