/*
 * Airline Hub
 * https://kth.kattis.scrool.se/problems/airlinehub
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

struct coord {
    double lat;
    double lon;
    coord(double lat, double lon) : lat(lat), lon(lon) {}
    coord() {}
 };

double toRadians(double deg) {
    double res = deg*PI/180;
    while(res < 0) {
        res += 2*PI;
    }
    return res;
}

/* Haversine formula */
double latlongDist(coord c1, coord c2) {
    double R = 6372.797560856; // earth radius in km
    double la1_r = toRadians(c1.lat);
    double la2_r = toRadians(c2.lat);
    double delta1 = toRadians(c2.lat-c1.lat);
    double delta2 = toRadians(c2.lon-c1.lon);

    double latH = sin(delta1*0.5);
    latH *= latH; // squared
    double lonH = sin(delta2*0.5);
    lonH *= lonH; //squared 

    double tmp = cos(la1_r)*cos(la2_r);
    return 2*R*asin(sqrt(latH + tmp*lonH));
}

int main() {
    int a;
    double lat, lon;
    while(scanf("%d", &a) == 1) {
        vector<coord> coords;
        double minMaxDist = 1e9;
        coord hub;
        while(a--) {
            scanf("%lf %lf", &lat, &lon);
            coords.emplace_back(lat,lon);
        }
        for(coord c1 : coords) {
            double maxDist = 0;
            for(coord c2 : coords) {
                if (c1.lat == c2.lat && c1.lon == c2.lon) {
                    continue;
                }
                maxDist = max(maxDist,latlongDist(c1,c2));
            }
            if (maxDist < minMaxDist) {
                minMaxDist = maxDist;
                hub = c1;
            }
        }
        printf("%.2lf %.2lf\n", hub.lat, hub.lon);
    }
}

