#include "ladder.h"
#include <algorithm>
#include <unordered_set>
using namespace std;

void error(string msg) {
    cerr << "Error: " << msg  << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) {
        return false;
    }

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; i++) {
        dp[i][0] = i; 
    }
    for (int j = 0; j <= len2; j++) {
        dp[0][j] = j; // Cost of inserting all characters in str2 to match empty str1
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {

                dp[i][j] = dp[i - 1][j - 1];

            } else {
                dp[i][j] = 1 + min({dp[i - 1][j],
                                    dp[i][j - 1],
                                    dp[i - 1][j - 1]});
            }
        }
    }
    return dp[len1][len2] <= d;
}


// Use BFS to guarantee that the first solution you find will
// be as short as any other. Start by examining ladders that 
// are one step away from the original word, where only one 
//letter is changed. 
// That is the purpose of is_adjacent(last_word, word
bool is_adjacent(const string& word1, const string& word2) {
    // eliminate case more than one letter is added/deleted
    int len1 = word1.length();
    int len2 = word2.length();
    if (abs(len1 - len2) > 1) return false;

    int changes = 0;
    int i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++changes > 1) 
                return false;

            if (len1 > len2) 
                i++;

            else if (len2 > len1) 
                j++;

            else 
                i++;
                j++;
        } else {
            i++;
            j++;
        }
    }
    return true;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}


void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}



void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}


void verify_word_ladder() {
    return;
}
