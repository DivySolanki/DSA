#include <bits/stdc++.h>
using namespace std;

/*
IMPORTANT QUESTION
FIND THE LONGEST SUB ARRAY WITH SUM K (Positive and Negative)

1. Brute Force -> 3 indented for loops then 2 indented for loops
2. Better -> Hashing and in case if the key is too
large than Map<long long, int>

Better is an optimal solution in case the arr contains negative numbers

3. Optimal -> Using 2 pointer approach
*/
int longestSubarrayWithSumK_better(vector<int> &arr, long long k) {
    map<long long, int> preSumMap; // key is the sum and value is the last index till sum
    long long sum = 0;
    int maxLen = 0;
    for(int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        if(sum == k) {
// checking if start till current index is max sub array
            maxLen = max(maxLen, i+1);
        }
        long long rem = sum - k;
        if(preSumMap.find(rem) != preSumMap.end()) {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }
        if(preSumMap.find(sum) == preSumMap.end()) {
            preSumMap[sum] = i;
        }
    }
    return maxLen;
}


/*
 The time complexity is O(2N) and not O(N^2) as 
 the inner while loop is running combined equivalent to N 
 and not for every outer N loop.
*/
int longestSubarrayWithSumK_optimal(vector<int> &arr, long long k) {
    int left = 0, right = 0;
    long long sum = arr[0];
    int maxLen = 0;
    int n = arr.size();
    while(right < n) {
        while(left <= right && sum > k) {
            sum -= arr[left];
            left++;
        }
        if(sum == k) {
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if(right < n) sum += arr[right];
    }
    return maxLen;
}

/*
Two Sum Problem
It has 2 versions
1. Just return Yes or No
2. Return the indices of the element

1. Brute Force -> 2 indented loops 
2. Better -> Hashing is used
3. Optimal -> Using 2 pointer approach
*/
vector<int> twoSum_better(vector <int> &arr, int total) {
    map<int, int> mpp;
    for(int i = 0; i<arr.size(); i++) {
        int ele = arr[i];
        int rem = total - ele;
        if(mpp.find(rem) != mpp.end()) {
            return {mpp[rem], i};
        }
        mpp[ele] = i;
    }
    return {-1, -1};
}

/*
If you are trying to solve the 2nd version then a map data structure is required so that the indices can be preserved and they are not distorted by sorting.

For 2nd varity better is the optimal one.
*/
string towSum_optimal(vector <int> &arr, int total) {
    int left = 0, right = arr.size() - 1;
    sort(arr.begin(), arr.end());
    while(left < right) {
        int sum = arr[left] + arr[right];
        if(sum == total) {
            return "Yes";
        }
        else if(sum < total) left++;
        else right--;
    }
    return "No";
}

/*
Sort the array containing 0's 1's and 2's

1. Brute Force -> Use sorting algorithm
2. Better -> 3 counter approach and 3 loops to fill the array
3. Optimal -> Dutch National Flag Algorithm
*/
void sort_012_better(vector <int> &arr) {
    int n = arr.size();
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    for (int i=0; i<n; i++) {
        if(arr[i] == 0) cnt0++;
        else if(arr[i] == 1) cnt1++;
        else cnt2++;
    }
    for(int i=0; i<cnt0; i++) {
        arr[i] = 0;
    }
    for(int i=cnt0; i<cnt0+cnt1; i++) {
        arr[i] = 1;
    }
    for(int i=cnt0+cnt1; i<n; i++) {
        arr[i] = 2;
    }
}

/*
Optimal Approach: Dutch National Flag Algorithm
Intution: take 3 pointer
low, mid, high
Assumption
[0, ..., low-1] -> all 0's
[low, ...., mid-1] -> all 1's
[high+1, ...., n-1] -> all 2's (n is the size of the array)

[mid, ..., high] -> contains the unsorted elements
*/
void sort_012_optimal(vector <int> &arr) {
    int n = arr.size();
    // As the start is low prev is till low-1 assume contains 0
    // mid is the start of unsorted array i.e. 0
    int low = 0, mid = 0, high = n-1;

    while(mid <= high) {
        if(arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if(arr[mid] == 1) {
            mid++;
        }
        else {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}


/*
Majority element appearing (> N/2 times)

1. Brute Force -> 2 indented loops and a counter inside the outer loop to keep track of number of occurences
2. Better -> Hashing Data structure
3. Optimal -> Moore's Voting Algorithm
*/
int majorityElement_better(vector <int> &arr) {
    int n = arr.size();
    map<int, int> mpp;

    for(int i=0; i<n; i++) {
        mpp[arr[i]]++;
    }
    for(auto it: mpp) {
        if(it.second > (n/2)) return it.first;
    }
    return -1;
}

/*
Moore's Voting Algorithm
Requires 2 var
1. Count (No used to store a count of single element).
2. Element (Represents the element in consideration)

For each ele 
    at initial stage count++ for that ele.
    iterate through arr: 
        increase if the ele appears again.
        decrease if it is not the same ele.
    if the count is 0 then set current ele as new ele and repeat the process.

After the loop is executed.
check is the ele is the majority or not.
*/
int majorityElement_optimal(vector <int> &arr) {
    int n = arr.size();
    int cnt = 0;
    int ele;
    for (int i=0; i<n; i++) {
        if(cnt == 0) {
            cnt = 1;
            ele = arr[i];
        }
        else if(arr[i] == ele) {
            cnt++;
        }
        else {
            cnt--;
        }
    }
    // The below steps will not be performed if it is stated that there always exist majority element.
    int checkCnt = 0;
    for (int i=0; i<n; i++) {
        if(arr[i] == ele) checkCnt++;
    }
    if(checkCnt > (n/2)) return ele;
    return -1;
}


/*
Maximum Subarray Sum

1. Brute Force -> 3 indented loops (trying out all the possible combinations of subarrays)
2. Better -> 2 indented loops
3. Optimal -> Kadane's Algorithm
*/
int maxSubarrSum_better(vector <int> &arr) {
    int n = arr.size();
    int maxi = INT_MIN;
    for (int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            if(sum > maxi) maxi = sum;
        }
    }
    return maxi;
}

/*
Kadane's Algorithm to find the Maximum Subarray Sum:
1. Initialize two variables:
   - sum: Tracks the running sum of the current subarray.
   - maxi: Tracks the maximum sum encountered so far.
2. Iterate through each element of the array:
   - Add the current element to the running sum (sum).
   - Update maxi if the current running sum (sum) is greater than maxi.
   - If the running sum (sum) becomes negative, reset it to 0, as starting a new subarray will yield a higher sum.
3. If all elements are negative, return 0 (optional based on problem requirements).
4. Return maxi, which contains the maximum subarray sum.
*/
int maxSubarrSum_optimum(vector <int> &arr) {
    int n = arr.size();
    int sum = 0;
    int maxi = INT_MIN;
    // Gives the indexes of the subarray
    // int ansStart; 
    // int ansEnd;

    for(int i=0; i<n; i++) {
        // int start;
        // if(sum == 0) start = i;

        sum += arr[i];

        if(sum > maxi) {
            maxi = sum;
            // ansStart = start;
            // ansEnd = i;
        }

        if(sum < 0) {
            sum = 0;
        }
    }
    if(maxi < 0) maxi = 0;
    return maxi;
}


/*
Buy and Sell stocks
prices = {7, 1, 5, 3, 6, 4}
Buy on a day and sell when the profit is maximum.
Always buying has to happen before selling.
At the end return the max profit
*/
int maxProfit(vector<int> &arr) {
    int n = arr.size();
    int mini = arr[0];
    int profit = 0;
    for(int i=1; i<n; i++) {
        int cost = arr[i] - mini;
        profit = max(profit, cost);
        mini = min(mini, arr[i]);
    }
    if(profit < 0) profit = 0;
    return profit;
}   


/*
Rearrange array elements by sign 

An array will be provided containing equal positive and negative elements.
Eg: {-5 , 1, 3, -6, -2, 2}
Rearrange the array such that all positive elements are all negative elements occur in alternate fashion.
Eg: {1, -5, 3, -6, 2, -2}

The order of the elements should not be distorted
such as {-5, -6, -2} and {1, 3, 2} occur in this order in the original array

1. Brute: Maintain 2 sub arrays Positive and Negative and accordingly assign them to the new array

2. Optimal: Use 1 ans array and hold all the even indexes for the +ve ele and
odd indexes for the -ve elements.
*/
vector<int> rearrangeArray_optimal(vector<int> &nums) {
    int n = nums.size();
    vector<int> res(n);
    int pos = 0, neg = 1;
    for(int i=0; i<n; i++) {
        if(nums[i] > 0) {
            res[pos] = nums[i];
            pos += 2;
        } else {
            res[neg] = nums[i];
            neg += 2;
        }
    }
    return res;
}

/*
The above problem has another variety in which
the positive and negative ele are not equal

To solve it Brute Force is the best solution.
*/
vector<int> rearrangeArray_diff_optimal(vector<int> &nums) {
    int n = nums.size();
    vector<int> pos;
    vector<int> neg;
    for(int i=0; i<n; i++) {
        if(nums[i] > 0) {
            pos.push_back(nums[i]);
        } else {
            neg.push_back(nums[i]);
        }
    }
    if(pos.size() > neg.size()) {
        for(int i=0; i<neg.size(); i++) {
            nums[2*i] = pos[i];
            nums[2*i+1] = neg[i];
        }
        // It is multiplied by 2 as the pos and neg take up 2 places in each iteration.
        int index = neg.size() * 2;
        for(int i=neg.size(); i<pos.size(); i++) {
            nums[index] = pos[i];
            index++;
        }
    } else {
        for(int i=0; i<pos.size(); i++) {
            nums[2*i] = pos[i];
            nums[2*i+1] = neg[i];
        }
        int index = pos.size() * 2;
        for(int i=pos.size(); i<neg.size(); i++) {
            nums[index] = neg[i];
            index++;
        }
    }
    return nums;
}


/*
Next Greater Permutation

All possible arrangements of values [1, 2, 3] can
have 3! combinations i.e. 6.
1. [1, 2, 3]
2. [1, 3, 2]
3. [2, 1, 3]
4. [2, 3, 1]
5. [3, 1, 2]
6. [3, 2, 1] and all these are in dictionary order.
123 < 132 and so on.

The problem is to find the next combination of a given value and array.

Edge case if 321 is given then next is 123.

1. Brute Force -> generate all permutations and perform linear search
2. Better -> In C++ STL is next_permutation
3. Optimal -> 
    - Longer prefix match; a[i] < a[i+1]
    - find > i, but the smallest one.
    - Try to place rem in sorted order
*/
vector<int> next_greater_permutation(vector<int> &a) {
    int index = -1;
    int n = a.size();
    for(int i=n-2; i>=0; i--){
        if(a[i] < a[i+1]){
            index = i;
            break;
        }
    }
    if(index == -1){
        reverse(a.begin(), a.end());
        return a;
    }
    for(int i=n-1; i>index; i--) {
        if(a[i]> a[index]) {
            swap(a[i], a[index]);
            break;
        }
    }
    reverse(a.begin() + index + 1, a.end()); // sorting from lowest to highest
    return a;
}

/*
Leaders in the array problem

Return the leader(s) from the array
A leader is an element to which all the right elements are smaller than it.
Eg: {10, 22, 12, 3, 0, 6}

The leaders are {22, 12, 6}

1. Brute Force -> linear search (2 loops)
2. Optimal -> Use loop from back and store the max.
*/
vector<int> superiorElements(vector<int> &a) {
    vector<int> res;
    int maxi = INT_MIN;
    int n = a.size();
    for(int i=n-1; i>=0; i--) {
        if(a[i]>maxi) {
            res.push_back(a[i]);
            maxi=a[i];
        }
    }
    return res;
}

/*
Longest consecutive sequence
As the name suggest return the length of the longest
consecutive sequence in the array
Eg: {100, 4, 200, 1, 3, 2}
Output: 4 as {1, 2, 3, 4} are present

1. Brute Force -> linear search (2 loops)
2. Better -> Uses sorting
3. Optimal -> Uses Set data structure
*/
int longest_consecutive_sequence_better(vector<int> &a) {
    int n = a.size();
    if(n == 0) return 0;
    sort(a.begin(), a.end());
    int longest = 1, countCurr = 0, lastSmall=INT_MIN;
    for(int i=0; i<n; i++) {
        if(a[i]-1 == lastSmall) {
            countCurr++;
            lastSmall = a[i]; 
        }
        else if(a[i] != lastSmall) {
            countCurr = 1;
            lastSmall = a[i];
        }
        longest = max(longest, countCurr);
    }
    return longest;
}

int longest_consecutive_sequence_optimum(vector<int> &a) {
    int n = a.size();
    unordered_set<int> st;
    int longest = 1;
    for(int i=0; i<n; i++) {
        st.insert(a[i]);
    }

    for(auto it: st) {
        if(st.find(it-1) == st.end()) {
// 3 is present it will return 3 and if will not execute
// 99 is not present then it will return st.end()
// and the if condition will execute assuming 100 the start of the sequence
// st.find() returns st.end()
// if the element is not found in the set
            int currNum = it, currStreak = 1;
            while(st.find(currNum+1) != st.end()) {
                currNum += 1;
                currStreak += 1;
            }
            longest = max(longest, currStreak);
        }
    }
    return longest;
}

/*
Set Matric Zeros
A matrix of 0's and 1's will be provided.
the task is to locate all the 0 and correspondingly
mark all the rows and columns 0.

1. Brute Force -> 2 Times iteration is performed.
    - the non zeros are marked -1 (2 loops)
    - then -1 are converted to 0 (2 loops)
2. Better -> Similar to Brute force approach
    just additional ds is used to keep track of the
    rows and columns to be marked 0.
3. Optimal -> Similar to better 
    just the use of additional ds is eliminated by
    using the first row and column of the matrix itself
*/
vector<vector <int>> set_matrix_zeros_better() {
    vector<vector<int>> mat = {{1, 1, 1, 1}, 
                               {1, 0, 1, 1},
                               {1, 1, 0, 1},
                               {0, 1, 1, 1}};
    int n = mat.size();
    int m = mat[0].size();
    int col[m] = {0};
    int row[n] = {0};
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(mat[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(row[i] || col[j]) {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}

vector<vector <int>> set_matrix_zeros_optimum() {
    vector<vector<int>> mat = {{1, 1, 1, 1}, 
                               {1, 0, 1, 1},
                               {1, 1, 0, 1},
                               {0, 1, 1, 1}};
    // int col[m] = {0}; -> mat[0][..]
    // int row[n] = {0}; -> mat[..][0]
    int n = mat.size();
    int m = mat[0].size();
    int col0 = 1;
    for(int i=0; i<n;i++) {
        for(int j=0; j<m; j++) {
            if(mat[i][j] == 0) {
                // mark the i-th row i.e. additional ds to keep track of row
                mat[i][0] = 0;
                // mark the j-th col i.e. additional ds to keep track of col
                if(j != 0) mat[0][j] = 0;
                else col0 = 0;
            }
        }
    }
    for(int i=1; i<n;i++) {
        for(int j=1; j<m; j++) {
            if(mat[i][j] != 0) {
                // check for col & row
                if(mat[0][j] == 0 || mat[i][0] == 0) {
                mat[i][j] = 0;
                }
            }
        }
    }
    if(mat[0][0] == 0) {
        for(int j=0; j<m; j++) {
            mat[0][j] = 0;
        }
    }
    if(col0 == 0) {
        for(int i=0; i<n; i++) {
            mat[i][0] = 0;
        }
    }
    return mat;
}

/*
Rotate Matrix by 90^o / Rotate Image

1. Brute Force -> row -> column 
                  (i -> n-1-i) 
                  (j -> j) 2 loops
2. Optimal -> - Transpose the matrix
             - Reverse every row
*/
vector<vector <int>> rotate_matrix_optimal() {
    vector<vector<int>> mat = {{1, 2, 3, 4}, 
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16}};
    int n = mat.size();
    for(int i=0; i<n-2; i++) {
        for(int j=i+1; j<n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    for(int i=0; i<n; i++){
        reverse(mat[i].begin(), mat[i].end());
    }
    return mat;
}


/*
Spiral Matrix 
Print the elements of the matrix in spiral from
(l to r then top to bottom then r to l then bottom to top)

It has only optimal solution
1. Optimal: Print right, bottom, left, top
            Use 4 pointers.
*/
vector<int> spiral_matrix_optimal() {
    vector<vector<int>> mat = {{1, 2, 3, 4}, 
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16}};
    int n = mat.size();
    int m = mat[0].size();
    int left = 0, right = m-1;
    int top = 0, bottom = n-1;
    vector<int> ans;
    while(left <= right && top <= bottom){
        for(int i=left; i<=right; i++){
            ans.push_back(mat[top][i]);
        }
        top++;
        for(int i=top; i<=bottom; i++){
            ans.push_back(mat[i][right]);
        }
        right--;
        if(top <= bottom){
            for(int i=right; i>=left; i--){
                ans.push_back(mat[bottom][i]);
            }
            bottom--;
        }
        if(left <= right){
            for(int i=bottom; i>=top; i--){
                ans.push_back(mat[i][left]);
            }
            left++;
        }
    }
    return ans;
}


/*
No of sub arrays with sum k 

1. Brute Force -> 3 loops keep track of sum == k
2. Better -> 2 loops keep track of sum == k
3. Optimal -> uses prefix sum (Hash Map)
*/
int no_sum_k_better(vector<int> &arr, int k) {
    int n = arr.size();
    int cnt = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            if(sum == k) cnt++;
        }
    }
    return cnt;
}

int no_sum_k_optimal(vector<int> &arr, int k) {
    int n = arr.size();
    unordered_map<int, int> mp;
    mp[0] = 1;
    int preSum = 0, cnt = 0;
    for(int i=0; i<n; i++) {
        preSum += arr[i];
        int rem = preSum - k;
        cnt += mp[rem];
        mp[preSum]++;
    }
    return cnt;
}

int main() {
    vector<int> arr = {7, 1, 5, 3, 6, 4};
    // int n;
    // cin >> n;
    // int input;
    // while(cin >> input) {
    //     arr.push_back(input);
    // }
    // vector<vector <int>> res = rotate_matrix_optimal();
    // int n = res.size();
    // int m = res[0].size();
    // for(int x = 0; x < n; ++x){
    //         for(int y = 0; y < m; ++y){
    //             cout << res[x][y] << " ";
    //         }
    //     cout << "\n";
    // }
    cout << maxProfit(arr);
    // for(auto it: arr) {
    //     cout << it << " ";
    // }
    return 0;
}