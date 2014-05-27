/*
 * almostunionfind
 * https://kth.kattis.scrool.se/problems/almostunionfind
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

 #define MAX 100000

using namespace std;

void Union(int p, int q);
void move(int p, int q);
void info(int p);
int root(int x);
void print_array(int array[], int n);

int id[MAX+1];
int sum[MAX+1];
int cnt[MAX+1];
int n;


int main() {
    int m, arg;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        id[i] = i;
        sum[i] = i;
        cnt[i] = 1;
    }
    // print_array(id, n);

    string line;
    getline(cin, line); // clear previous line
    for (int i = 0; i < m; ++i) {
        print_array(id,n);
        vector<int> args;
        getline(cin, line);
        istringstream in(line);
        while (in >> arg) {
            args.push_back(arg);
        }
        if (args.size() == 3) {
            if (args[0] == 1)
                Union(args[1],args[2]);
            else if (args[0] == 2)
                move(args[1],args[2]);
        }
        else 
            info(args[1]);
        // print_array(id, n);
    }
    return 0;
}

void Union(int p, int q) {
    int p_id = root(p);
    int q_id = root(q);
    if (p_id == q_id)
        return;
    id[p_id] = q_id;
    sum[q_id] += sum[p_id];
    // sum[p_id] = 0;
    cnt[q_id] += cnt[p_id];
    // cnt[p_id] = 0;
}

void move(int p, int q) {
    int p_id = root(p);
    int q_id = root(q);
    id[p] = q_id;
    ++cnt[q_id];
    --cnt[p_id];
    sum[p_id] -= p;
    sum[q_id] += p;
}

int root(int x) {
    while(x != id[x])
        x = id[x];
    return x;
}

void info(int p) {
    int p_id = root(p);
    printf("%d %d\n", cnt[p_id], sum[p_id]);
}


void print_array(int array[], int n) {
    for (int i = 1; i <= n*2; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

}






