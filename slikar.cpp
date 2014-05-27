/*
 * Slikar
 * https://kth.kattis.scrool.se/problems/slikar
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct coord {
    int x;
    int y;
    coord() {}
    coord(int x, int y) : x(x), y(y) {}
};

int R,C;
char grid[50][50]; 
int floodedAt[50][50];
int delta[] = {-1, 0, 1, 0, 0, -1, 0, 1};

void print_flood();
void print_grid();
void flood(coord start);
vector<coord> getAdj(coord c);
bool validCoord(coord c);

int main() {
    char c;
    vector<coord> flooded;
    coord start;
    scanf("%d%d",&R,&C);
    for (int i = 0; i < R; ++i) {
        c = getchar(); // read newline
        for (int j = 0; j < C; ++j) {
            c = getchar();
            if (c == 'S')
                start = coord(i,j);
            else if (c == '*')
                flooded.push_back(coord(i,j));
            grid[i][j] = c;
            if (c == 'X' || c == 'D')
                floodedAt[i][j] = -1; // for printing
            else
                floodedAt[i][j] = INT_MAX;
        }
    }
    // print_grid();
    // calculate flooding times
    for (int i = 0; i < flooded.size(); ++i) {
        flood(flooded[i]);
    }
    // printf("\n");
    // print_flood();

    // main search:
    int ans = -1;
    coord curr;
    int time;
    pair<coord,int> a;
    vector< vector<bool> > visited(R, vector<bool>(C, false));
    queue< pair<coord,int> > q; 
    q.push(make_pair(start,0));
    visited[start.x][start.y] = true;
    while(!q.empty()) {
        a = q.front();
        curr = a.first;
        time = a.second;
        q.pop();
        if (grid[curr.x][curr.y] == 'D') {
            ans = time;
            break;
        }
        if (floodedAt[curr.x][curr.y] <= time)
            continue;
        else {
            // cout << "checking (" << curr.x << "," << curr.y << ")" << endl;
            vector<coord> adj = getAdj(curr);
            // cout << "numadj: " << adj.size() << endl;
            for (int i = 0; i < adj.size(); ++i) {
                if (!visited[adj[i].x][adj[i].y]) {
                    q.push(make_pair(adj[i],time+1));
                    visited[adj[i].x][adj[i].y] = true;
                }
            }
        }
    }
    if (ans == -1)
        cout << "KAKTUS" << endl;
    else 
        cout << ans << endl;
}

void flood(coord start) {
    coord current;
    pair<coord,int> item;
    int timestep = 0;
    vector< vector<bool> > visited(R, vector<bool>(C, false));
    queue< pair<coord,int> > q;
    q.push(make_pair(start,0));
    visited[start.x][start.y] = true;
    while(!q.empty()) {
        item = q.front();
        current = item.first;
        q.pop();
        if (floodedAt[current.x][current.y] > item.second) {
            floodedAt[current.x][current.y] = item.second;
            vector<coord> adj = getAdj(current);
            // cout << "num Adj: " << adj.size() << endl;
            for (int i = 0; i < adj.size(); ++i) {
                if (!visited[adj[i].x][adj[i].y] && grid[adj[i].x][adj[i].y] != 'S') {
                    q.push(make_pair(adj[i],item.second+1));
                    visited[adj[i].x][adj[i].y] = true;
                }
            }
        }
    }
}

vector<coord> getAdj(coord c) {
    vector<coord> adj;
    // cout << "getAdj for (" << c.x << "," << c.y << ")" << endl;
    for (int i = 0; i < 8; i+=2) { // loop directions
        coord m(c.x+delta[i],c.y+delta[i+1]);
        if (validCoord(m)) { 
            adj.push_back(m);
        }
    }
    return adj;
}
    
bool validCoord(coord c) {
    if (c.x >= 0 && c.x < R && c.y >= 0 && c.y < C && grid[c.x][c.y] != '*' && grid[c.x][c.y] != 'X')
        return true;
    return false;
}


void print_grid() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void print_flood() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << floodedAt[i][j] << " ";
        }
        cout << endl;
    }
}
