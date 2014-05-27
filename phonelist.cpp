/*
 * Phone List
 * https://kth.kattis.scrool.se/problems/phonelist
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

struct Trie {
    bool end;
    Trie *children[10];
    Trie() {
        end = false;
        for (int i = 0; i < 10; ++i) {
            children[i] = NULL; // NULL
        }
    }
    bool isEnd() { return end; }
};

bool addWord(Trie &root, string w) {
    // cout << "Called addWord with " << w << endl;
    Trie *trie = &root;
    bool collision = true;
    for (char& c : w) {
        // cout << "loop char: " << c;
        int i = c - '0';
        if (trie->children[i] != NULL) {
            // cout << " and node exists." << endl;
            if (trie->children[i]->isEnd()) {
                return collision = true;
            }
        }
        else {
            trie->children[i] = new Trie();
            collision = false;
            // cout << " and node was created." << endl;
        }
        trie = trie->children[i];
    }
    trie->end = true;
    return collision;
}

void freeTrie(Trie *trie) {
    for (int i = 0; i < 10; ++i) {
        if (trie->children[i] != NULL)
            freeTrie(trie->children[i]);
        delete(trie->children[i]);
    }
}


int main() {
    int T, N;
    string line;
    scanf("%d",&T);
    for (int i = 0; i < T; ++i) {
        Trie root;
        scanf("%d",&N);
        getline(cin, line);
        bool collision = false;
        for (int i = 0; i < N; ++i) {
            getline(cin, line);
            if (addWord(root, line)) {
                collision = true;
            }
        }
        if (collision)
            cout << "NO" << endl;
        else 
            cout << "YES" << endl;
        freeTrie(&root);
    }
    return 0;
}