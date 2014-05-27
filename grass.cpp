/*
 * Watering Grass
 * https://kth.kattis.scrool.se/problems/grass
 *
 * @author Martin Runelöv
 *
 * Idea: Interval cover on the x-axis
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int index;
    double start;
    double end;
    Interval() : index(-1), start(0), end(0) {};
    Interval(double start, double end, int index) : start(start), end(end), index(index) {};
    Interval(const Interval& other) : index(other.index), start(other.start), end(other.end) {};
    bool operator < (const Interval& i) const { return (end < i.end); } // compare intervals by end
};

vector<int> cover(Interval interval, vector<Interval> intervals) 
{
    double start, end;
    vector<int> cover;
    bool zeroInterval = interval.start == interval.end;

    sort(intervals.begin(), intervals.end()); // sorted by end

    double covered = interval.start;
    while (covered < interval.end || zeroInterval) 
    {
        int foundIndex = -1;
        for (int i = intervals.size()-1; i >= 0; --i) 
        {
            if (intervals[i].start > covered)
                continue; 
            if (intervals[i].end < covered) // no intervals can cover
                return vector<int>();

            foundIndex = i;
            covered = intervals[i].end;
            break;
        }

        if (foundIndex != -1) 
        {
            cover.push_back(intervals[foundIndex].index);
            // cout << "adding idx to cover: " << intervals[foundIndex].index << endl;
            intervals.erase(intervals.begin()+foundIndex);
        }
        else
        {
            return vector<int>();
        }

        if (zeroInterval) // 0-intervals only need one pass
            break;
    }
    if (covered < interval.end) 
        return vector<int>();
    
    return cover;
}

int main() {
    int n,l;
    double x,w,r;
    while(scanf("%d %d %lf",&n, &l, &w) == 3) {
        vector<Interval> intervals;
        Interval grass(0.0, (double)l, -1);
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &x, &r);
            if (r*2 > w) {
                double dx = sqrt(r*r - (w/2)*(w/2));
                intervals.emplace_back(x-dx,x+dx,intervals.size());
             }
        }
        vector<int> cvr = cover(grass, intervals);
        if (cvr.empty())
            cout << "-1" << endl;
        else {
            for (int i = 0; i < cvr.size(); ++i) {
                // cout << "interval index: " << cvr[i] << endl;
                // cout << intervals[cvr[i]].start << "-" << intervals[cvr[i]].end << endl; 
            }
            cout << cvr.size() << endl;
        }
    }

}

