/*
 * Catenym
 * https://kth.kattis.scrool.se/problems/catenym
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct edge {
    bool visited;
    int v;
    int wi; // word index
    edge(int v, int wi) : v(v), wi(wi) { visited = false; }
};

int N;
vector< vector<edge> > G(26);
vector<string> dict;
vector<int> inDeg(26,0); // outDeg for 'i' is in G[i].size()
vector<int> path;

void reset() {
    fill(G.begin(), G.end(), vector<edge>());
    fill(inDeg.begin(), inDeg.end(), 0);
    dict.clear();
    path.clear();
}

void dfs(int node) {
    for (int i = 0; i < G[node].size(); ++i) { // loop all edges
        edge& e = G[node][i];
        if(!e.visited) {
            cout << "checking edge " << node << ", " << i << " which is " << dict[e.wi] << endl;
            e.visited = true;
            dfs(e.v);
            cout << "adding word " << dict[e.wi] << endl;
            path.push_back(e.wi); // store word
        }
    }
}

int main() {
    int t;
    string word;
    int fc, lc;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &N);
        dict.resize(N);
        cin.ignore();
        for (int i = 0; i < N; ++i) {
            cin >> dict[i];
        }

        sort(dict.begin(), dict.end()); // sort lexicographically
        // add edges in lexicographical order
        for (int i = 0; i < N; ++i) {
            fc = dict[i].front() - 'a'; // first char
            lc = dict[i].back() - 'a'; // last char
            G[fc].emplace_back(lc,i);
            ++inDeg[lc];
        }

        int start = -1;
        int end = -1;
        bool fail = false;
        for (int i = 0; i < 26; ++i) {
            if (G[i].size() == inDeg[i]) {
                // cout << "same deg for '" << (char)(i+'a') << "'" << endl;
                continue;
            }
            if (G[i].size() == inDeg[i]+1) {
                // cout << "start: '" << (char)(i+'a') << "'" << endl;
                start = i;
            }
            else if (G[i].size() == inDeg[i]-1) {
                // cout << "end: '" << (char)(i+'a') << "'" << endl;
                end = i;
            }
            else {
                fail = true;
                break;        
            }
        }
        if (!fail) {

            // all even, find first with outDeg > 0
            if (start == -1 && end == -1) {
                for (int i = 0; i < 26; ++i) {
                    if (!G[i].empty()) {
                        start = i;
                        break;
                    }
                }            
            }
            
            dfs(start);
            if (path.size() == N) { // didn't reach all words        
                for (int i = path.size()-1; i >= 0; --i) {
                    cout << dict[path[i]];
                    if (i > 0) cout << ".";
                }
                cout << endl;
            }
            else 
                fail = true;
        }

        if (fail)
            cout << "***" << endl;

        if (t > 0)
            reset();
    }

    // eulerian path? in this version we want all nodes exactly once

    return 0;
}



