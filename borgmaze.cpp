/*
 * Killing Aliens in a Borg Maze
 * https://kth.kattis.scrool.se/problems/borg
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

#define FLOOR ' '
#define WALL '#'
#define ALIEN 'A'
#define START 'S'


struct coord {
    int x;
    int y;
    coord() {}
    coord(int x, int y) : x(x), y(y) {}
};

struct edge {
    coord u;
    coord v;
    int dist;
    edge() {}
    edge(coord u, coord v, int dist) : u(u), v(v), dist(dist) {}
    bool operator < (const edge& e) const {
        return dist < e.dist;
    }
};

void printMaze();
bool validCoord(coord c);
vector<coord> getAdj(coord c);
void bfs(coord start);
int mst_kruskal(vector<edge>& edges);

char maze[50][50]; 
int delta[] = {-1, 0, 1, 0, 0, -1, 0, 1};
int X, Y, aliens;
vector<edge> distances;
// unionfind
int parent[2500];


int gridToIndex(coord c) {
    return c.x*Y + c.y;
}

// union-find find for kruskal
int find(int i) {
    while(i != parent[i])
        i = parent[i];
    return i;
}

int main() {
    int T;
    char c;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        vector<coord> starting_points;
        scanf("%d%d",&Y,&X);
        for (int j = 0; j < X; ++j) {
            c = getchar(); // read newlines
            for (int k = 0; k < Y; ++k) {
                scanf("%c", &maze[j][k]);
                if(maze[j][k] == 'A' || maze[j][k] == 'S')
                    starting_points.emplace_back(j,k);
            }
        }
        // printMaze();
        // find distances to 'A's:
        for (int i = 0; i < starting_points.size(); ++i) {
            bfs(starting_points[i]);
        }

        sort(distances.begin(),distances.end());

        // printf("Distances:\n");
        // coord a,b;
        // int d;
        // for (int i = 0; i < distances.size(); ++i) {
        //     a = distances[i].u;
        //     b = distances[i].v;
        //     d = distances[i].dist;
        //     printf("From (%d, %d) to (%d, %d), dist = %d\n", a.x,a.y,b.x,b.y,d);
        // }

        // starting parents: self.
        for (int i = 0; i < 2500; ++i) {
            parent[i] = i;
        }

        cout << mst_kruskal(distances) << endl;
        if (i < T-1) {
            distances.clear();
        }
    }

}

void bfs(coord start) {
    // cout << "BFS from starting point (" << start.x << "," << start.y << ")" << endl;
    int dist;
    pair<coord,int> a;
    vector< vector<bool> > visited(X, vector<bool>(Y, false));
    queue< pair<coord,int> > q; 
    q.push(make_pair(start,0));
    visited[start.x][start.y] = true;
    coord curr;
    while(!q.empty()) {
        a = q.front();
        q.pop();
        curr = a.first;
        dist = a.second;
        // cout << "checking (" << curr.x << "," << curr.y << ")" << endl;

        if (dist != 0 && maze[curr.x][curr.y] == 'A') { // Alien! (and an ugly way to avoid visiting start)
            distances.emplace_back(start,curr,dist);
        }
        vector<coord> adj = getAdj(curr);
        // cout << "numadj: " << adj.size() << endl;
        for (int i = 0; i < adj.size(); ++i) {
            if (!visited[adj[i].x][adj[i].y]) {
                q.push(make_pair(adj[i],dist+1));
                visited[adj[i].x][adj[i].y] = true;
            }
        }
    }
}

int mst_kruskal(vector<edge>& edges) {
    int cost = 0;
    int parent_u, parent_v;
    for (int i = 0; i < edges.size(); ++i) {
        parent_u = find(gridToIndex(edges[i].u));
        parent_v = find(gridToIndex(edges[i].v));
        if (parent_u != parent_v) {
            cost += edges[i].dist;
            parent[parent_u] = parent[parent_v];
        }
    }
    return cost;
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
    if (c.x >= 0 && c.x < X && c.y >= 0 && c.y < Y && maze[c.x][c.y] != '#')
        return true;
    return false;
}


void printMaze() {
    cout << endl;
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
    cout << endl;
}





