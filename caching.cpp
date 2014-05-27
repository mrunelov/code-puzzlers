/*
 * Introspective caching
 * https://kth.kattis.scrool.se/problems/caching
 *
 * @author Martin Runelöv
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <utility>

using namespace std;

int calculate_cache_reads(int C, int N, vector<int> v);

int main() {
    int c, n, a;
    cin >> c >> n >> a;
    vector<int> accesses;
    accesses.reserve(a);
    int input;
    // for (int i = 0; i < a; ++i) {
    //     cin >> input;
    //     accesses.push_back(input);
    // }
    std::copy(std::istream_iterator<int>(std::cin), // read 'a' object accesses
          std::istream_iterator<int>(),
          std::back_inserter(accesses));
    printf("%d\n", calculate_cache_reads(c, n, accesses));
    return 0;
}


/*
 * C = cache size
 * N = number of objects
 * v = vector of accesses
 * @return: The minimum number of cache writes
 */
int calculate_cache_reads(int C, int N, vector<int> v) {
    int V = v.size();
    int c = 0;
    int cache_writes = 0;
    pair<int,int> replacement;
    vector<bool> cache(N);
    vector<int> next_access_i(V); // next_access list for indices
    vector<int> next_access_o(N); // next_access list for objects
    priority_queue< pair<int,int> > least_needed_q; // queue of next_access-object pairs that is sorted by access time
    for (int i = 0; i < N; ++i) { // default next access = infinity (= V)
        next_access_o[i] = V;
    }
    for (int i = (V-1); i >= 0; --i) { // sets next occurrence of element at position i
        next_access_i[i] = next_access_o[v[i]]; // next access for index set to next_access for element at index i
        next_access_o[v[i]] = i; // next_access for element i updated to current index
    }

    // cout << "next_access_i vector: ";
    // for (std::vector<int>::const_iterator i = next_access.begin(); i != next_access.end(); ++i)
    //     cout << *i << ' ';
    // cout << endl;

    for (int i = 0; i < V; ++i) {
        if(!cache[v[i]]) {
            if (c < C) {
                cache[v[i]] = true;
                // cout << "Adding " << v[i] << " to the cache." << endl;
                ++cache_writes;
                ++c;
            } 
            else {
                replacement = least_needed_q.top();
                least_needed_q.pop();
                cache[replacement.second] = false;
                cache[v[i]] = true;
                // cout << "Adding " << v[i] << " to the cache, replacing " << replacement.second << endl;
                ++cache_writes;
            }
        }
        // push access time info for this cache entry. 
        // TODO: comment on why old entries aren't invalid!
        least_needed_q.push(make_pair(next_access_i[i], v[i])); // next_access is paired with the cached object
    }
    return cache_writes;
}




