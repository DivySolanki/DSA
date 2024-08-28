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
    set<string> st(wordList.begin(), wordList.end());

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


int main() {
    string startWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {
        "hot", "dot", "dog", "lot", "log", "cog"
    };

    cout << wordLadderLength(startWord, endWord, wordList);

    return 0;
}