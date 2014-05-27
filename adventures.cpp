/*
 * Adventures in Moving IV
 * https://kth.kattis.scrool.se/problems/adventuremoving4
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Station {
    int d;
    int p;
};

int cost[102][201]; // cost at station with certain amount of gas
vector<Station> stations; 

int main() {
    int D, d, p;
    scanf("%d", &D);
    stations.push_back(Station{0,0});
    while(scanf("%d %d", &d, &p) == 2) {
        if (d == D)
            p = 20000001;
        stations.push_back(Station{d,p});
    }
    if (stations.size() == 1) {
        cout << "impossible" << endl;
        return 0;
    }

    if (stations[stations.size()-1].d != D)
        stations.push_back(Station{D,20000001}); // goal city as endpoint station

    Station cs;
    int minCost;
    // obs, memset not working
    // memset(cost, 1e9, sizeof(cost)); // fixes starting point and minCost comparison for rest
    for(int i = 0; i < 102; ++i)
        for (int j = 0; j < 201; ++j) {
            cost[i][j] = 1e9;
        }
    cost[0][100] = 0; // starting point
    for (int i = 1; i < stations.size(); ++i) { // loop over all stations, get minimum one by one
        cs = stations[i];
        d = cs.d - stations[i-1].d;
        int bought = -1; // debug
        for (int j = 0; j <= 200; ++j) { // tank
            // if (j+d <= 200) {
                minCost = 1e9;
                for (int k = 0; k <= j+d; ++k) { // amount to buy
                    if (j+d-k >= d && j+d-k <= 200 && cost[i-1][j+d-k] != 1e9) {
                        minCost = min(minCost, cost[i-1][j+d-k] + cs.p*k); // cost[i][j] = cost[i-1][j-distance+bought] + price*bought
                        // cout << " checking cost["<< i-1 << "][" << j+d-k << "] (" << (cost[i-1][j+d-k]) <<") + " << cs.p*k << " = " << (cost[i-1][j+d-k] + cs.p*k) << endl;  
                    }                
                }
                // cout << "setting mincost for (" << i << ", " << j << ") to " << minCost << endl;
                cost[i][j] = minCost;
            // }
        }
    }

    int lowestAns = cost[stations.size()-1][100];
    if (lowestAns < 20000001 && lowestAns > 0) // ugly handling of overflows. use long long?
        cout << lowestAns << endl;
    else 
        cout << "impossible" << endl;



    return 0;
}




