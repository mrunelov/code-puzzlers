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

using namespace std;

void Union(int p, int q);
void move(int p, int q);
void info(int p);
void print_array(int array[], int n);

int id[100002];
int n;


int main() {
    int m, arg;

    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++i) {
            id[i] = i;
        }
        // print_array(id, n);
        string line;
        getline(cin, line); // clear previous line
        for (int i = 0; i < m; ++i) {
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
            // getline(cin, line);
        }
    }
    return 0;
}

void Union(int p, int q) {
    if (p == q)
        return;
    int p_id = id[p];
    int q_id = id[q];
    if (p_id == q_id)
        return;
    for (int i = 1; i <= n; ++i) {
        if (id[i] == p_id)
            id[i] = q_id;
    }
}

void move(int p, int q) {
    id[p] = id[q];
}

void info(int p) {
    long long sum = 0;
    int num = 0;
    int p_id = id[p];
    for (int i = 1; i <= n; ++i) {
        if (id[i] == p_id) {
            sum += i;
            ++num;
        }
    }
    cout << num << " " << sum << endl;
}


void print_array(int array[], int n) {
    for (int i = 1; i <= n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

}






