/*
 * Help!
 * https://kth.kattis.com/problems/help2
 *
 * @author Martin Runelöv
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stringstream;
using std::vector;
using std::map;
using std::to_string;

vector<string> split(const string &s, char delim);
vector<string> &split(const string &s, char delim, vector<string> &elems);
string find_match(vector<string> a, vector<string> b);
string kmp(vector<string> a, vector<string> b);

const string FAILURE_STRING = "-";
const int MAX_VALUE = 1e9;
int memo[11][101][101];

int main() {
    int num_cases;
    string a, b;
    vector<string> a_tokens;
    vector<string> b_tokens;
    cin >> num_cases;
    getline(cin, a); // read past num_cases line
    for (int i = 0; i < num_cases; ++i) {
        getline(cin, a);
        getline(cin, b);
        a_tokens = split(a, ' ');
        b_tokens = split(b, ' ');
        cout << find_match(a_tokens,b_tokens) << endl;
    }
    return 0;
}

string find_match(vector<string> a, vector<string> b) {
    // TODO: find error.
    // maybe try KMP: http://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm
    // see also, kompendium.
    // It's a single pattern search, which is applicable here.
    // we might need to rewrite one of the strings before matching.
    if (a.size() != b.size())
        return FAILURE_STRING;
    int numtokens = a.size();
    map<string,string> token_match_a;  // map tokens (placeholders+words) to values
    map<string,string> token_match_b;
    // map<string,string> set_placeholders_a; // map placeholder values to placeholders
    // map<string,string> set_placeholders_b; 
    for (int i = 0; i < numtokens; ++i) {
        if (a[i][0] != '<')
            token_match_a[a[i]] = a[i];
        else 
            token_match_a[a[i]] = "";
        if (b[i][0] != '<')
            token_match_b[b[i]] = b[i];
        else
            token_match_b[b[i]] = "";
    }
    for (int j = 0; j < 2; ++j) { // repeat twice to discover contradictions
        for (int i = 0; i < numtokens; ++i) {
            if(a[i][0] == '<') { // a[i] is a placeholder
                if (b[i][0] == '<') { // both are placeholders
                    if (token_match_a[a[i]] == "") { // a[i] placeholder is unset
                        if (token_match_b[b[i]] != "") { // mapping exists for b[i] but not for a[i]
                            token_match_a[a[i]] = token_match_b[b[i]]; // set a[i] mapping to b[i] mapping
                        }
                        else {

                        }
                    }
                    else if (token_match_b[b[i]] == "") // mapping exists for a[i] but not for b[i]
                        token_match_b[b[i]] = token_match_a[a[i]]; // set b[i] mapping to a[i] mapping
                    else { // mapping exists for both
                        if (token_match_a[a[i]] != token_match_b[b[i]])
                            return FAILURE_STRING;
                    }
                }
                else if (token_match_a[a[i]] == "") { // a[i] but not b[i] is a placeholder
                    token_match_a[a[i]] = b[i];
                }
                else if (token_match_a[a[i]] != token_match_b[b[i]]) { // a[i] is placeholder, b[i] isn't. Doesn't match
                    return FAILURE_STRING;
                }
            }
            else if(b[i][0] == '<') { // b[i] but not a[i] is a placeholder
                if (token_match_b[b[i]] == "") // b[i] placeholder is unset
                    token_match_b[b[i]] = a[i];
                else if (token_match_a[a[i]] != token_match_b[b[i]]) // b[i] is set. match needed
                    return FAILURE_STRING;
            }
            else {
                if (a[i] == b[i]) // no placeholders, match needed
                    continue;
                else {
                    // cout << "3 Failure! No placeholders, no match" << endl;
                    return FAILURE_STRING;
                }
            }
        }
    }
    string match = "";
    string token;
    for (int i = 0; i < numtokens; ++i) {
        token = token_match_a[a[i]];
        // cout << "adding match (" << a[i] << " --> " << token_match_a[a[i]] << ")" << endl;
        if (token == "") { // unset token means that we have unmatched placeholders
            match += "foo ";
        }
        else 
            match += token + " ";
    }
    return match;
}

vector<string> split(const string &s, char delim) {
    vector<string> tokens;
    split(s, delim, tokens);
    return tokens;
}

vector<string> &split(const string &s, char delim, vector<string> &tokens) {
    stringstream ss(s);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}





