/*
 * Ladder
 * https://kth.kattis.scrool.se/problems/ladder
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

#define PI 3.14159265

using namespace std;

double deg_sin(double rad) {
    return (std::sin(rad*PI/180));
}

int main() { 
    double ladder;
    double h,v;
    scanf("%lf %lf", &h, &v);
    ladder = h/deg_sin(v);
    cout << ceil(ladder) << endl;
    return 0;
}