/*
 * Knights in Fen
 * https://kth.kattis.scrool.se/problems/knightsfen
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

enum Tile { EMPTY, BLACK, WHITE };
typedef vector< vector<Tile> > graph;

struct gcomparison {
    bool operator() (pair<pair<graph,pair<int,int> >,pair<int,int> > a, pair<pair<graph,pair<int,int> >,pair<int,int> > b) {
        if (a.second.second == b.second.second)
            return a.second.first < b.second.first ? true : false;
        return a.second.second >= b.second.second ? true : false;
    }
};

vector<pair<int,int>> get_valid_moves(graph g, pair<int,int> empty_tile);
void print_board(graph g);
int a_star();
bool is_correct_tile(Tile type, int j, int k);

graph g;
pair<int,int> empty_square;
int g_score;

int main() {
    char c;
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        g.clear();
        g.resize(5, vector<Tile>(5));
        g_score = 0;
        for (int j = 0; j < 5; ++j) {
            scanf("%c", &c); // read newline
            for (int k = 0; k < 5; ++k) {
                scanf("%c", &c);
                if (c == '0') {
                    g[j][k] = WHITE;
                    if (is_correct_tile(WHITE,j,k)) {
                        ++g_score;
                    }
                }
                else if (c == '1') {
                    g[j][k] = BLACK;
                    if (is_correct_tile(BLACK,j,k)) {
                        ++g_score;
                    }
                }
                else if (c == ' ') {
                    g[j][k] = EMPTY;   
                    empty_square = make_pair(j,k);
                }
            }
        }
        int steps = a_star();
        if (steps == -1) {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        }
        else {
            cout << "Solvable in " << steps << " move(s)." << endl;
        }
    }
    return 0;
}


int a_star() {
    // ((board,empty tile), (score, depth))
    priority_queue<pair<pair<graph,pair<int,int> >,pair<int,int> >, vector< pair<pair<graph,pair<int,int> >,pair<int,int> > >, gcomparison> pq;
    pq.push(make_pair(make_pair(g,empty_square), make_pair(g_score,0)));
    if (g_score + 10 < 24) { // impossible!
        return -1;
    }
    while(!pq.empty()) {
        pair<pair<graph,pair<int,int> >,pair<int,int> >  state = pq.top();
        pq.pop();
        int current_score = state.second.first;
        int current_depth = state.second.second;
        if (current_score == 24) {
            return current_depth;
        }
        if ((current_score + (10-current_depth)) < 24) {
            // cout << "current score: " << current_score << ", after " << current_depth << " moves." << endl;
            continue;
        }
        if (current_depth == 10)
            continue;

        graph current_graph = state.first.first;
        
        // cout << "current score: " << current_score << endl;
        // print_board(current_graph);
        pair<int,int> empty_tile = state.first.second;
        // graph current_graph = state.first;
        vector<pair<int,int> > moves = get_valid_moves(current_graph,empty_tile);
        for (int i = 0; i < moves.size(); ++i) {
            pair<int,int> m = moves[i];
            int new_score = current_score;
            int new_depth = current_depth + 1;
            graph new_graph = graph(current_graph);
            Tile tile = current_graph[m.first][m.second];
            if (is_correct_tile(tile,m.first,m.second)) {
                if(!is_correct_tile(tile, empty_tile.first, empty_tile.second))
                    --new_score;
            }
            else {
                if (is_correct_tile(tile, empty_tile.first, empty_tile.second))
                    ++new_score;
            }
            new_graph[m.first][m.second] = EMPTY;
            new_graph[empty_tile.first][empty_tile.second] = tile;
            pair<int,int> new_empty_tile = m;
            pq.push(make_pair(make_pair(new_graph,new_empty_tile),make_pair(new_score,new_depth)));
        }
    }
    return -1;
}

vector<pair<int,int>> get_valid_moves(graph g, pair<int,int> empty_tile) {
    vector<pair<int,int> > moves;
    int x = empty_tile.first;
    int y = empty_tile.second;
    if (x-2 >= 0) {
        if (y-1 >= 0)
            moves.push_back(make_pair(x-2,y-1));
        if (y+1 <= 4)
            moves.push_back(make_pair(x-2,y+1));
    }
    if (x+2 <= 4) {
        if (y-1 >= 0)
            moves.push_back(make_pair(x+2,y-1));
        if (y+1 <= 4)
            moves.push_back(make_pair(x+2,y+1));
    }
    if (y-2 >= 0) {
        if (x-1 >= 0)
            moves.push_back(make_pair(x-1, y-2));
        if (x+1 <= 4)
            moves.push_back(make_pair(x+1, y-2));
    }
    if (y+2 <= 4) {
        if (x-1 >= 0)
            moves.push_back(make_pair(x-1,y+2));
        if (x+1 <= 4)
            moves.push_back(make_pair(x+1, y+2));
    }
    return moves;
}

void print_board(graph g) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << g[i][j];
        }
        cout << endl;
    }
}

bool is_correct_tile(Tile type, int j, int k) {
    if (type == WHITE) {
        if (j >= 1 && k <= j) {
            if (j == 1 || j == 2) {
                if (k != j) {
                    return true;
                }
            }
            else {
                return true;
            }
        }
        return false;
    }
    else if (type == BLACK) {
        if (j <= 3 && k >= j) {
            if (j == 2 || j == 3) {
                if (k != j) {
                    return true;
                }
            }
            else {
                return true;
            }
        }
        return false;
    }
} 





