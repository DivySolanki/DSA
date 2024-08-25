#include<bits/stdc++.h>
using namespace std;

// Maximum 10^7 size array can be declared globally

// using array
int hashing_num(){
    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }

    // precompute
    int hash[13] = {0}; // assumption there are 12 ele to search
    // Maximum 10^6 size array can be declared inside main()
    for(int i=0; i<n; i++){
        hash[arr[i]] += 1;
    }

    int q;
    cin >> q;
    while(q--){
        int number;
        cin >> number;

        //fetch
        cout << hash[number] << endl;
    }
    return 0;
}

int hashing_char(){
    string s;
    cin >> s;

    // pre compute
    int hash[256] = {0};
    for(int i=0; i<s.size(); i++){
        hash[s[i]]++;
    }

    int q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        // fetch
        cout << hash[c] << endl;
    }

    return 0;
}

// using map
int hashing_num_map(){
    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }

    // pre compute
    map<int, int> mpp; // stores value in sorted order
    for(int i=0; i<n; i++){
        mpp[arr[i]]++; // [] operator automatically inserts a key if not found 
    }

    int q;
    cin >> q;
    while(q--){
        int number;
        cin >> number;

        //fetch
        cout << mpp[number] << endl;
    }
    return 0;
}

/*
First preference should be always given to unordered_map
as it has O(1) complexity in best and average case
and O(n) in worst case. (This will rarely occur)
This happens due to collisions

While map has O(log N) in all the cases


Any data structure can be a key in map 
but not in unordered map.
*/

int main() {
    hashing_num_map();
    return 0;
}