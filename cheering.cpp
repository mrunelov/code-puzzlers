/*
 * Cheering game
 * https://kth.kattis.scrool.se/problems/cheergame
 * Hemtal 1 - Popup14
 *
 * @author Martin Runelöv
 */

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::vector;
using std::min;
using std::max;


pair<int,int> recursive_cheering(int game_min, int scoring_window, int cheer_mins);
pair<int,int> get_best_score(pair<int,int> score1, pair<int,int> score2);
pair<int,int> recursive_cheering2(int game_min, int cheer_mins, int scoring_window);
bool better(pair<int,int> &p1, pair<int,int> &p2);


// DP matrix. Best scores given dimensions (game min) x (scoring window) x (minutes to spend)
pair<int,int> score[100][2000][10];
int cheers[91]; // opponent's cheers
int N;

pair<int,int> get_best_score(pair<int,int> score1, pair<int,int> score2) {
    if (score1.first == -1)
        return score2;
    int diff = (score1.first - score1.second) - (score2.first - score2.second);
    if (diff > 0) // score1 is better
        return score1;
    else if (diff < 0) // score2 is better
        return score2;
    else if (score1.first >= score2.first) // compare own team score if diff is 0 
        return score1;
    return score2;
}

int main() {
    memset(score, -1, sizeof(score));
    int T, M, interval_start, interval_end;
    cin >> N >> T >> M;
    for (int i = 0; i < M; ++i) {
        cin >> interval_start >> interval_end;
        for (int j = interval_start; j < interval_end; ++j) {
            ++cheers[j+1];
        }
    }
    pair<int,int> best_score = recursive_cheering(90, T*N, 0);
    cout << best_score.first << " " << best_score.second << endl;
}


pair<int,int> recursive_cheering(int game_min, int cheer_mins, int scoring_window) {
    // cout << "recursive cheering called with (" << game_min << "," << cheer_mins << "," << scoring_window <<  "). ";
    // cout << "score for pos: (" << score[game_min][cheer_mins][scoring_window+4].first << "," << score[game_min][cheer_mins][scoring_window+4].second << ")." <<  endl;

    if (score[game_min][cheer_mins][scoring_window+4].first != -1)
        return score[game_min][cheer_mins][scoring_window+4];
    if (game_min == 0)
        return make_pair(0,0);
    if (game_min == 45)
        scoring_window = 0; // reset scoring window at half-time
    
    int mins_spent;
    pair<int,int> best_score;
    pair<int,int> result;
    int mins_to_spend = min(cheer_mins, N);
    int current_cheers = cheers[game_min];
    int new_window = 0;
    if (current_cheers > 0) { // preparation for do nothing. if opponent cheers, they win
        if (scoring_window < 0)
            new_window = scoring_window - 1;
        else
            new_window = -1;
    }

    new_window = min(scoring_window, 0) - 1;

    best_score = recursive_cheering(game_min-1, cheer_mins, new_window%5); // always try to do nothing
    if (new_window == -5)
        ++best_score.second;
    if (current_cheers < mins_to_spend) {
        mins_spent = current_cheers + 1;
        if (scoring_window < 0)
            new_window = 1;
        else
            new_window = scoring_window + 1;
        result = recursive_cheering(game_min-1, cheer_mins-mins_spent, new_window%5);
        if (new_window == 5)
            ++result.first;
        best_score = get_best_score(best_score, result);
    }
    if (current_cheers <= mins_to_spend) { // try current_cheers == mins_to_spend
        new_window = 0;
        best_score = get_best_score(best_score, recursive_cheering(game_min-1, cheer_mins-current_cheers, new_window)); // let them increase their window    
    }
    return score[game_min][cheer_mins][scoring_window+4] = best_score;
}

