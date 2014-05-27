#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

/*
 * Euclid's Game
 * https://kth.kattis.scrool.se/problems/euclidsgame
 *
 * @author Martin Runelöv
 */

using namespace std;

// recursive gcd-ish
bool play(int a, int b) {
    // cout << "a = " << a << ", b = " << b << endl;
    if (a > b)
        return play(b,a); // keep lower number in "a"
    if (b%a == 0) // winning move
        return true;
    if (b/a == 1) // floor division. forced move. other player gets the upper hand
        return !play(a,b-a);
    return true; // winning position since the player has at least two choices, one of which is winning.
}

int main() {
    int a,b;
    while (scanf("%d%d",&a,&b) && a && b) {
        if (play(a,b))
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
            
    }
}