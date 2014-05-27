/*
 * The SetStack Computer
 * https://kth.kattis.scrool.se/problems/setstack
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int Push(stack<int> &s);
int Duplicate(stack<int> &s);
int Union(stack<int> &s);
int Intersect(stack<int> &s);
int Add(stack<int> &s);
void add_setindex(set<int> se);
set<int> popset(stack<int> &s);

vector< set<int> > sets;
map<set<int>, int> setindex;

int main() {
    add_setindex(set<int>()); // empty set
    stack<int> s;
    int N, M, c;
    string op;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &M);
        for (int j = 0; j < M; ++j) {
            cin >> op;
            if (op[0] == 'P')
                c = Push(s);
            else if (op[0] == 'D')
                c = Duplicate(s);
            else if (op[0] == 'U')
                c = Union(s);
            else if (op[0] == 'I')
                c = Intersect(s);
            else 
                c = Add(s);
            // cout << c << "\n";
            printf("%d\n", c);
        }
        // cout << "***" << "\n";
        printf("***\n");
    }
    // cout << std::flush;
    return 0;
}

int Push(stack<int> &s) {
    s.push(0);
    return 0;
}

int Duplicate(stack<int> &s) {
    set<int> duplicate = sets[s.top()];
    s.push(setindex[duplicate]);
    return duplicate.size();
}

int Union(stack<int> &s) {
    set<int> A = popset(s);
    set<int> B = popset(s);
    B.insert(A.begin(), A.end());
    add_setindex(B);
    s.push(setindex[B]);
    return B.size(); 
}

int Intersect(stack<int> &s) {
    set<int> A = popset(s);
    set<int> B = popset(s);
    set<int> intersection;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(intersection, intersection.end()));
    add_setindex(intersection);
    s.push(setindex[intersection]);
    return intersection.size();
}

int Add(stack<int> &s) {
    set<int> A = popset(s);
    set<int> B = popset(s);
    B.insert(setindex[A]);
    add_setindex(B);
    s.push(setindex[B]);
    return B.size();
}

void add_setindex(set<int> se) {
    if (!setindex.count(se)) {
        setindex[se] = sets.size(); // store set index in map
        sets.push_back(se); // store set
    }
}

set<int> popset(stack<int> &s) {
    set<int> res = sets[s.top()];
    s.pop();
    return res;
}


