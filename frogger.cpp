/*
 * frogger
 * https://kth.kattis.scrool.se/problems/frogger
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

int N,M,T;
char grid[22][50]; 
vector<vector<vector<int> > > carAt(22, vector<vector<int> >(50, vector<int>()));
int delta[] = {0, -1, 0, 1, -1, 0, 1, 0};

void print_flood();
void print_grid();
void flood(coord start);
vector<coord> getAdj(coord c, int time);
bool validCoord(coord c, int time);
bool hasCar(coord c, int time);

int main() {
    int S;
    char c;
    coord start, goal;
    scanf("%d",&S);
    for (int i = 0; i < S; ++i) {
        scanf("%d%d%d", &T, &N, &M);
        for (int j = 0; j < N+2; ++j) {
            c = getchar(); // read newline
            for (int k = 0; k < M; ++k) {
                c = getchar();
                if (c == 'F')
                    start = coord(j,k);
                else if (c == 'G')
                    goal = coord(j,k);
                grid[j][k] = c;
            }
        }
        // print_grid();

        // main search:
        bool reached = false;
        coord curr;
        int time;
        pair<coord,int> a;
        // vector< vector<bool> > visited(N+2, vector<bool>(M, vector<bool>(false)));
        vector<vector<vector<bool> > > visited(N+2, vector<vector<bool> >(M, vector<bool>(T+1)));
        queue< pair<coord,int> > q; 
        q.push(make_pair(start,0));
        visited[start.x][start.y][0] = true;
        while(!q.empty()) {
            a = q.front();
            curr = a.first;
            time = a.second;
            q.pop();
            if (curr.x == goal.x && curr.y == goal.y) { // reached goal
                cout << "The minimum number of turns is " << time << "." << endl;
                reached = true;
                break;
            }
            if (time + curr.x + abs(curr.y-goal.y) >= T)
                continue;
            // cout << "checking (" << curr.x << "," << curr.y << ") at time " << time << endl;
            vector<coord> adj = getAdj(curr, time+1);
            // cout << "numadj: " << adj.size() << endl;
            for (int i = 0; i < adj.size(); ++i) {
                // printf("Checking visited[%d][%d][%d]\n", adj[i].x,adj[i].y,time+1);
                if (!visited[adj[i].x][adj[i].y][time+1]) {
                    q.push(make_pair(adj[i],time+1));
                    visited[adj[i].x][adj[i].y][time+1] = true;
                }
            }
        }
        if (!reached) {
            cout << "The problem has no solution." << endl;
        }
        if (i < S-1) {
            // cout << "CLEARING" << endl;
            for (int i = 1; i <= N; ++i) {
                for (int j = 0; j < M; ++j) {
                    carAt[i][j].clear();
                }
            }
            // cout << "CLEARED" << endl;
        }
    }
}

/**
 * Positive modulo for circular car occurrences
 */
inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}

bool hasCar(coord c, int time) {
    int direction;
    if((N+1)%2 == c.x%2)
        direction = 1;
    else
        direction = -1;
    int corresponding_pos = positive_modulo(c.y+time*direction, M);
    // if (c.x == 10 && c.y == 0 && time == 4) {
    //     cout << "corresponding_pos: " << corresponding_pos << endl;
    //     cout << "AND grid: " << grid[c.x][corresponding_pos] << endl;
    // }
    if (grid[c.x][corresponding_pos] == 'X') {
        // cout << "Found car at (" << c.x << "," << c.y << ")" << endl;
        return true;
    }
    return false;
}

vector<coord> getAdj(coord c, int time) {
    vector<coord> adj;
    // cout << "getAdj for (" << c.x << "," << c.y << ")" << endl;
    for (int i = 0; i < 8; i+=2) { // loop directions
        coord m(c.x+delta[i],c.y+delta[i+1]);
        if (validCoord(m, time)) { 
            adj.push_back(m);
        }
    }
    if (validCoord(c,time))
        adj.push_back(c); // stand still
    return adj;
}
    
bool validCoord(coord c, int time) {
    if (c.x >= 0 && c.x < N+2 && c.y >= 0 && c.y < M) {
        if (hasCar(c,time))
            return false;
        return true;
    }
    return false;
}


void print_grid() {
    for (int i = 0; i < N+2; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
