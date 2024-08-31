#include <bits/stdc++.h>
using namespace std;

/*
Exteremely Hard Problem
Word Ladder 1

Given two distinct words startWord and endWord and a lsit denoting wordList of unique words of equal length.

We have to find the shortest transformation sequence from startWord to endWord.

The condition to obey are:
1. Only one letter can be changed in each transformation.
2. Each transformed word must exist in the wordList including the endWord.

If it is not possible to change the startWord to endWord return 0 else return the length of the shortest steps of transformation.

It uses the BFS traversal as the finding of the words occur level wise.

The solution is that change a char from the word and if it exists in the wordList then push it into the queue with step also remove the word from the set.

If the queue is empty return 0 else the code in the queue will return the step required to make targetWord.
*/
int wordLadderLength(string startWord, string targetWord, vector<string> &wordList) {
    queue<pair<string, int>> q;
    q.push({startWord, 1});
    unordered_set<string> st(wordList.begin(), wordList.end());

    while(!q.empty()) {
        string word = q.front().first;
        int steps = q.front().second;
        q.pop();

        if(word == targetWord) {
            return steps;
        }

        for(int i=0; i<word.size(); i++) {
            char original = word[i];

            for(char ch='a'; ch<='z'; ch++) {
                word[i] = ch;

                if(st.find(word) != st.end()) {
                    st.erase(word);
                    q.push({word, steps + 1});
                }
            }
            word[i] = original;
        }
    }
    return 0;
}

/*
There is another variety of the above problem in which we have to return the vector of vectors.
They contain all the shortest transformations from start to end word.
*/
vector<vector<string>> wordLadder2(string startWord, string targetWord, vector<string> &wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<vector<string>> q;
    q.push({startWord});
    vector<string> usedOnLevel;
    usedOnLevel.push_back(startWord);
    int level = 0;
    vector<vector<string>> ans;

    while(!q.empty()) {
        vector<string> vec = q.front();
        q.pop();

        if(vec.size() > level) {
            level++;
            for(auto it: usedOnLevel) {
                st.erase(it);
            }
            usedOnLevel.clear();
        }

        string word = vec.back();

        if(word == targetWord) {
            if(ans.size() == 0) {
                ans.push_back(vec);
            }
            else if(ans[0].size() == vec.size()) {
                ans.push_back(vec);
            }
        }

        for(int i=0; i<word.size(); i++) {
            char original = word[i];
            for(char ch='a'; ch<='z'; ch++) {
                word[i] = ch;
                if(st.find(word) != st.end()) {
                    vec.push_back(word);
                    q.push(vec);
                    usedOnLevel.push_back(word);
                    vec.pop_back();
                }
            }
            word[i] = original;
        }
    }
    return ans;
}

/*
Word Ladder 2 Optimized.

This solution is the optimized version of the above problem.

It involves 2 steps:
1. Store all the possible words from the dictionary in a map with their level.
Initially 0 or 1.
2. Backtrack using dfs from the endword to the begin word and store the sequence.
Add the new word only if it lies on the lower level.
*/
void dfs(string word, string startWord,  unordered_map<string, int> &mpp, vector<string> &seq, vector<vector<string>> &ans) {
    if(word == startWord) {
        reverse(seq.begin(), seq.end());
        ans.push_back(seq);
        reverse(seq.begin(), seq.end());
        return;
    }

    int steps = mpp[word];

    for(int i=0; i<word.size(); i++) {
        char original = word[i];
            for(char ch='a'; ch<='z'; ch++) {
                word[i] = ch;
                if(mpp.find(word) != mpp.end() && mpp[word] == steps - 1) {
                    seq.push_back(word);
                    dfs(word, startWord, mpp, seq, ans);
                    seq.pop_back();
                }
            }
        word[i] = original;
    }

}

vector<vector<string>> wordLadder2_Optimized(string startWord, string targetWord, vector<string> &wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<string> q;
    q.push(startWord);
    unordered_map<string, int> mpp;
    mpp[startWord] = 0;
    st.erase(startWord);
    while(!q.empty()) {
        string word = q.front();
        int steps = mpp[word];
        q.pop();
        if(word == targetWord) break;
        for(int i=0; i<word.size(); i++) {
            char original = word[i];
                for(char ch='a'; ch<='z'; ch++) {
                    word[i] = ch;
                    if(st.count(word)) {
                        mpp[word] = steps + 1;
                        st.erase(word);
                        q.push(word);
                    }
                }
            word[i] = original;
        }
    }

    vector<vector<string>> ans;
    if(mpp.find(targetWord) != mpp.end()) {
        vector<string> seq;
        seq.push_back(targetWord);
        dfs(targetWord, startWord, mpp, seq, ans);
    }
    return ans;
}


int main() {
    string startWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {
        "hot", "dot", "dog", "lot", "log", "cog"
    };

    vector<vector<string>> res =  wordLadder2_Optimized(startWord, endWord, wordList);

    for(auto f: res) {
        for(auto s: f) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}