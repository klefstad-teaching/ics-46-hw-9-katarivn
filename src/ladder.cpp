#include "ladder.h"
using namespace std;

void error(string msg) {
    cerr << "Error: " << msg  << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    
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
    queue<vector<string>> ladder_queue; // queue of vector of strings
    ladder_queue.push({begin_word})
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        string ladder = ladder_queue.front();
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
        return;
    }

    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
    }
    cout << endl;
}


void verify_word_ladder() {
    return;
}
