/*
 * Dominant Strings
 * https://kth.kattis.scrool.se/problems/dominant
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

bool dominates(const string &s1, const string &s2) {
    // if (s2 == "camp")
    //     cout << "checking if camp is dominated by " << s1 << endl;
    if (s1.length() <= s2.length())
        return false;
    int freq[26];
    memset(freq, 0, sizeof(freq));
    int toMatch = s2.length();
    for (int i = 0; i < s2.length(); ++i)
        ++freq[s2[i] - 'a'];
    for (int i = 0; i < s1.length(); ++i) {
        if (toMatch > s1.length()-i)
            return false;
        if (freq[s1[i]- 'a'] > 0) {
            --freq[s1[i]- 'a'];
            --toMatch;
            // if (s2 == "camp")
            //     cout << "found matching char " << s1[i] << endl;
        }
    }
    // if (s2 == "camp")
    //     cout << "match count: " << match << endl;
    if (toMatch == 0)
        return true;
    return false;
}

int main() {
    set<string> ds;
    string line;
    bool dominator;
    set<string>::iterator it;
    while(cin >> line) {
        dominator = true;
        it = ds.begin();
        while (it != ds.end()) {
            if (dominates(line, *it)) {
                it = ds.erase(it); // dominates dominator, remove it
                continue;
            }
            else if (dominates(*it, line)) {
                dominator = false;
                break; // dominated, doesn't dominate anything in this list
            }
            else {
                ++it;
            }
        }
        if (dominator)
            ds.insert(line);
    }
    for(it = ds.begin(); it != ds.end(); ++it)
        cout << *it << "\n";
    cout << flush;
    return 0;
}





