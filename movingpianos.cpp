/*
 * Moving pianos
 *
 * @author Martin Runelöv
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct Interval {
    int start;
    int end;
    Interval() : start(-1), end(-1) {};
    Interval(int start, int end) : start(start), end(end) {};
    Interval(const Interval& other) : start(other.start), end(other.end) {};
    bool operator < (const Interval& i) const {
        return (end < i.end);
    }
};

// struct sort_key {
//     inline bool operator() (const Interval& i1, const Interval& i2) {
//         return (i1.end < i2.end);
//     }
// };

string test_schedule(int num_pianos, int num_tuners, vector<Interval> intervals, bool weekends);


int main(int argc, char *argv[]) {
    int i, j, num_cases, num_pianos, num_tuners, start, end;

    cin >> num_cases;
    for (i = 0; i < num_cases; ++i) {
        cin >> num_pianos >> num_tuners;
        vector<Interval> intervals(num_pianos);
        for (j = 0; j < num_pianos; ++j) {
            cin >> start >> end;
            intervals[j].start = start;
            intervals[j].end = end;
        }
        cout << test_schedule(num_pianos, num_tuners, intervals, false) << endl;
    }
    return 0;
}

/*
 * Calculate if scheduling is possible and check if weekends are needed for more than one worker
 *
 * @return:
 * 0: "serious trouble"
 * 1: "weekend work"
 * 2: "fine"
 */
string test_schedule(int num_pianos, int num_tuners, vector<Interval> intervals, bool weekends) {
    std::sort(intervals.begin(), intervals.end());
    int start, end;
    bool scheduled;
    int limit = num_tuners/2;
    vector<int> schedule(1000);
    for (int i = 0; i < intervals.size(); ++i) { // schedule all intervals
        start = intervals[i].start - 1; // 0-indexing
        end = intervals[i].end - 1;     // 0-indexing
        scheduled = false;
        for (int j = start; j <= end; ++j) { // loop over interval
            if (!weekends && j%7 > 4) // weekends = 5,6
                continue;
            if (schedule[j] < limit) {
                schedule[j] = schedule[j] + 1;
                scheduled = true;
                break;
            }
        }
        if (!scheduled) {
            if (!weekends) { // try with weekends enabled
                return test_schedule(num_pianos, num_tuners, intervals, true);
            } 
            else // if weekends were enabled the scheduling has failed
                return "serious trouble";
        }
    }
    if (weekends) // succeeded with weekends enabled
        return "weekend work";
    else // succeeded without using weekends
        return "fine";
}

