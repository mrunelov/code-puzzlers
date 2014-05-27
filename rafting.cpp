/*
 * White Water Rafting
 * https://kth.kattis.scrool.se/problems/rafting
 *
 * @author Martin Runelöv
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>

using namespace std;

struct coord {
    double lat;
    double lon;
    coord(double lat, double lon) : lat(lat), lon(lon) {}
    coord() {}
 };

double distance(coord a, coord b) {
    double x = a.lat - b.lat;
    double y = a.lon - b.lon;
    return sqrt(x*x + y*y);
} 

double distanceBetweenPointAndLine(coord p, coord a, coord b) {
    double segment_size = distance(a,b);
    double u = ((p.lat - a.lat)*(b.lat-a.lat) + (p.lon-a.lon)*(b.lon-a.lon))/(segment_size*segment_size);

    double x = a.lat + u*(b.lat-a.lat);
    double y = a.lon + u*(b.lon-a.lon);
    coord projection(x,y);
    double line_projection_dist = distance(p, projection);
    if (line_projection_dist < 1e-8) { // if projection_dist is 0, the full line contains p and the calculation is invalid
        line_projection_dist = 1e9;
    }
    if (distance(projection,a) + distance(projection,b) - distance(a,b) > 1e-12) { // projection not on segment, also invalid
        line_projection_dist = 1e9;        
    }

    double endpoint1_dist = distance(p, a);
    double endpoint2_dist = distance(p, b);

    double result = min(line_projection_dist,endpoint1_dist);
    result = min(result, endpoint2_dist);
    return result;
}

double distanceBetweenLines(coord a1, coord b1, coord a2, coord b2) {
    double dist = 1e9;
    dist = min(dist, distanceBetweenPointAndLine(a1, a2, b2));
    dist = min(dist, distanceBetweenPointAndLine(b1, a2, b2));
    dist = min(dist, distanceBetweenPointAndLine(a2, a1, b1));
    dist = min(dist, distanceBetweenPointAndLine(b2, a1, b1));
    return dist;
}

int main() {
    int t, outer_points, inner_points;
    double x, y;
    scanf("%d", &t);
    while(t--) {
        vector<coord> outer_poly;
        vector<coord> inner_poly;
        scanf("%d", &inner_points);
        for(int i = 0; i < inner_points; ++i) {
            scanf("%lf %lf", &x, &y);
            inner_poly.emplace_back(x,y);
        }
        scanf("%d", &outer_points);
        for(int i = 0; i < outer_points; ++i) {
            scanf("%lf %lf", &x, &y);
            outer_poly.emplace_back(x,y);
        }

        // for each pair of lines:
        double minDistance = 1e9;
        for (int i = 0; i < outer_points; ++i) {
            coord outer1(outer_poly[i]);
            coord outer2;
            if (i == outer_points-1) { // wrap around to beginning
                outer2 = coord(outer_poly[0]);
            }
            else {
                outer2 = coord(outer_poly[i+1]);
            }
            for (int j = 0; j < inner_points; ++j) {
                minDistance = min(minDistance, distanceBetweenPointAndLine(inner_poly[j], outer1, outer2));
            }
        }
        cout << setprecision(14) << minDistance*0.5 << endl;
    }



}

