/*
N points are placed in the coordinate plane.

Write a program that calculates how many ways we can choose three points so that they form a right triangle with legs parallel to the coordinate axes.

A right triangle has one 90-degree internal angle. The legs of a right triangle are its two shorter sides.

Input
The first line of input contains the integer N (3≤N≤100000), the number of points.

Each of the following N lines contains two integers X and Y (1≤X,Y≤100000), the coordinates of one point.

No pair of points will share the same pair of coordinates.

Output
Output the number of triangles.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> x[100001]; // array of vectors
int y_count[100001];

int main()
{
    int N,x_c,y_c;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &x_c, &y_c);
        x[x_c].push_back(y_c);
        y_count[y_c]++;
    }

    long long count = 0;
    for (int i = 1; i <= 100000; ++i) {
        int num_with_same_x = x[i].size();
        for (int j = 0; j < num_with_same_x; ++j) {
            int num_with_same_y = y_count[x[i][j]];
            if (num_with_same_y > 0)
                count += (long long)(num_with_same_x-1)*(num_with_same_y-1);
            // cout << "count += " << (num_with_same_x-1)*(num_with_same_y-1) << " for x = " << i << ", y = " << x[i][j] << endl;
        }
    }
    cout << count << endl;
}