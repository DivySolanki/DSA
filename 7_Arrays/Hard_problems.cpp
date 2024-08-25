#include <bits/stdc++.h>
using namespace std;


/*
Pascal Triangle

     1     This is the pascal triangle, for n=4
    1 1      the questions can be 
   1 2 1      1. Generate the pascal triangle.
  1 3 3 1     2. An element at a row and column.
              3. Return a full row of the triangle.

For a particular element it is given by rCc.
( Only open up r for c times.
  eg. r=10, c=3 then 10*9*7 )
*/
int nCr_sub_function(int r, int c) {
    // provide (r-1) and (c-1)
    long long res = 1;
    for(int i=0; i<c; i++) {
        res = res * (r-i);
        res = res / (i+1);
    }
    return res;
}

// for printing the whole row.
void pascal_row_brute(int n) {
    for(int c=1; c<=n; c++) {
        cout << nCr_sub_function(n-1, c-1) << " ";
    }
}

vector<int> pascal_row_optimum(int n) {
    long long ans = 1;
    vector<int> ansRow;
    for(int c=1; c<n; c++) {
        ans = ans * (n-c);
        ans = ans / c;
        ansRow.push_back(ans);
    }
    return ansRow;
}

vector<vector <int>> pascal_triangle_optimum(int n) {
    vector<vector<int>> ans;
    for(int i=1; i<=n; i++) {
        ans.push_back(pascal_row_optimum(i));
    }
    return ans;
}


/*
Majority element (appearing > n/3 times)
At max there will be 2 majority elements

1. Brute Force -> 2 loop; ls to keep majority ele
                  and break when ls == 2
2. Better -> HashMap no iteration on it.
3. Optimal -> Extended Boyer Moore's Voting algorithm
*/
vector<int> majority_n_by_3_better(vector<int> &nums) {
    int n = nums.size();
    int mini = floor(n/3) + 1;
    vector<int> ls;
    unordered_map<int, int> mpp;

    for(int i=0; i<n; i++) {
        mpp[nums[i]]++;
        if(mpp[nums[i]] == mini) {
            ls.push_back(nums[i]);
        }
        if(ls.size() == 2) break;
    }
    return ls;
}


vector<int> majority_n_by_3_optimal(vector<int> &nums) {
    int cnt1 = 0, cnt2 = 0;
    int ele1 = INT_MIN;
    int ele2 = INT_MIN;
    for(int i=0; i<nums.size(); i++) {
        if(cnt1 == 0 && nums[i] != ele2) {
            ele1 = nums[i];
            cnt1++;
        }
        else if(cnt2 == 0 && nums[i] != ele1) {
            ele2 = nums[i];
            cnt2++;
        }
        else if(nums[i] == ele1) cnt1++;
        else if(nums[i] == ele2) cnt2++;
        else {
            cnt1--;
            cnt2--;
        }
    }
    vector<int> ls;
    cnt1 = 0, cnt2 = 0;
    for(int i=0; i<nums.size(); i++) {
        if(nums[i] == ele1) cnt1++;
        if(nums[i] == ele2) cnt2++;
    }
    int mini = floor(nums.size()/3) + 1;
    if(cnt1 >= mini) ls.push_back(ele1);
    if(cnt2 >= mini) ls.push_back(ele2);
    return ls;
}

/*
3 Sum Problem (Google)
Return all unique triplets which add up to 0 or any other given target number.
No array element should be taken twice in a triplet.

1. Brute Force -> 3 loops basic approach
2. Better -> 2 loops and a Hashmap to search for element equating to 0.
    arr[k] = -(arr[i] + arr[j])
3. Optimal -> Sort the entire array. 
              2 pointer approach and a constant pointer to compare.
Simple logic:
1. the i pointer points to 1st ele
2. the j pointer is mid
3. the k pointer starts from last.
Move j to right if i+j+k < 0 
Moke k to left if i+j+k > 0
*/
vector<vector<int>> triplet_better(vector<int> &arr) {
    int n = arr.size();
    set<vector<int>> st;
    for(int i=0; i<n; i++) {
        set<int> tempSet;
        for(int j=i+1; j<n; j++) {
            int third = -(arr[i] + arr[j]);
            if(tempSet.find(third) != tempSet.end()) {
                vector<int> temp = {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            tempSet.insert(arr[j]);
        }
    }
    vector<vector<int>> res(st.begin(), st.end());
    return res;
}


vector<vector<int>> triplet_optimal(vector<int> &arr) {
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    for(int i=0; i<arr.size(); i++) {
        if(i > 0 && arr[i] == arr[i-1]) continue;
        int j = i+1, k = arr.size()-1;
        while(j<k) {
            int sum = arr[i] + arr[j] + arr[k];
            if(sum < 0) {
                j++;
            }
            else if(sum > 0) {
                k--;
            } 
            else {
                vector<int> temp = {arr[i], arr[j], arr[k]};
                ans.push_back(temp);
                j++;
                k--;
                while(j<k && arr[j] == arr[j-1]) j++;
                while(j<k && arr[k] == arr[k+1]) k--;
            }      
        }
    }
    return ans;
}


/*
4 Sum Problem (Google)
Return all unique quadlets which add up to 0 or any other given target number.
No array element should be taken twice in a quadlet.

1. Brute Force -> 4 loops basic approach (similar to 3 sum)
2. Better -> 3 loops and a Hashmap to search for element equating to target.
    arr[l] = -(arr[i] + arr[j] + arr[k])
3. Optimal -> Sort the entire array. 
              2 pointer approach similar to 3 Sum problem refer the above explanation.
*/
vector<vector<int>> quadlet_better(vector<int> &arr, int target) {
    int n = arr.size();
    set<vector<int>> st;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            set<long long> hashSet;
            for(int k=j+1; k<n; k++) {
                long long sum = arr[i] + arr[j];
                sum += arr[k];
                long long fourth = target - sum;
                if(hashSet.find(fourth) != hashSet.end()) {
                    vector<int> temp = {arr[i], arr[j], arr[k], int(fourth)};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hashSet.insert(arr[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

vector<vector<int>> quadlet_optimum(vector<int> &arr, int target) {
    int n = arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    for(int i=0; i<n; i++) {
        if(i>0 && arr[i-1] == arr[i]) continue;
        for(int j=i+1; j<n; j++) {
            if(j!=i+1 && arr[j-1] == arr[j]) continue;
            int k = j+1;
            int l = n-1;
            while(k<l) {
                // individual adding to avoid int overflow
                long long sum = arr[i];
                sum += arr[j];
                sum += arr[k];
                sum += arr[l];
                if(sum == target) {
                    vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                    ans.push_back(temp);
                    k++;
                    l--;
                    while(k<l && arr[k] == arr[k-1]) k++;
                    while(k<l && arr[l] == arr[l+1]) l--;
                } else if(sum < target) k++;
                else l--;
            }
        }
    }
    return ans;
}


/*
No. of subarray's with XOR K

1. Brute Force -> 3 loops Simple iterative approach.
2. Better -> 2 loops eliminates the loop to check subarray.
3. Optimal -> Similar to count subarray problem with sum k. (HashMap)
    Keeps the track of prior elements on which Xor gives K.
*/
int Xor_subarray_better(vector<int> &arr, int k) {
    int n = arr.size();
    int cnt = 0;
    for(int i=0; i<n; i++) {
        int Xor_k = 0;
        for(int j=i; j<n; j++) {
            Xor_k ^= arr[j];
            if(Xor_k == k) cnt++;
        }
    }
    return cnt;
}

int Xor_subarray_optimal(vector<int> &arr, int k)  {
    int n = arr.size();
    int xr = 0;
    unordered_map<int, int> mp;
    mp[xr]++;
    int cnt = 0;
    for(int i= 0; i<n; i++) {
        xr ^= arr[i];
        int x = xr ^ k;
        cnt += mp[x]; // if(mp.find(x) != mp.end()) not required as [] searchs for an ele and returns 0 if not found
        mp[xr]++;
    }
    return cnt;
}

/*
Merge Overlapping SubIntervals
EG: {{1, 3}, {2, 6}, {8, 9}, {9, 11}, {8, 10}, {2, 4}, {15, 18}, {16, 17}}
Will be 
[(1, 6), (8, 11), (15, 18)]

1. Brute Force -> sort the array and check for the second element which is less than the first of the last tuple.
2. Optimal -> Similar to brute approach just eliminate the loop to check if it is a part of the last tuple.
*/
vector<vector<int>> Intervals_brute(vector<vector<int>> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;
    for(int i = 0; i < n; i++) {
        int start = arr[i][0];
        int end = arr[i][1];
        if(!result.empty() && end <= result.back()[1]) {
            continue;
        }
        for(int j = i+1; j< n; j++) {
            if(arr[j][0] <= end) {
                end = max(end, arr[j][1]);
            } else {
                break;
            }
        }
        result.push_back({start, end});
    }
    return result;
}

vector<vector<int>> Intervals_optimal(vector<vector<int>> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;
    for(int i = 0; i < n; i++) {
        if(result.empty() || arr[i][0] > result.back()[1]) {
            result.push_back(arr[i]);
        } else {
            result.back()[1] = max(result.back()[1], arr[i][1]);
        }
    }
    return result;
}

/*
Merge 2 sorted array without extra space
Eg: arr1 = {1, 3, 5, 7} and arr2 = {0, 2, 6, 8, 9}
 The merged version is {0, 1, 2, 3, 5, 6, 7, 8, 9}
But we have to individually return it as
{0, 1, 2, 3} and {5, 6, 7, 8, 9}

1. Brute Force -> Use an extra array of size n + m.
Solve using two pointer simple approach.
2. Optimal -> It has 2 optimal solutions
    1. Use two pointer
     left pointing at arr1 last element and
     right pointing at arr2 first element
     Swap them it left > than right.
     Then simply sort the two arrays.
    2. Uses Gap method (Derived from shell sort algorithm)
*/
void merge_sort_array_brute(vector<int> &arr1, vector<int> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    vector<int> res;
    int left = 0;
    int right = 0;
    while (left < n && right < m) {
        if(arr1[left] <= arr2[right]) {
            res.push_back(arr1[left]);
            left++;
        } else {
            res.push_back(arr2[right]);
            right++;
        }
    }
    while(left < n) {
        res.push_back(arr1[left]);
        left++;
    }
    while (right < m) {
        res.push_back(arr2[right]);
        right++;
    }
    for(int i = 0; i < n+m; i++){
        if(i<n) arr1[i] = res[i];
        else arr2[i-n] = res[i];
    }
}

void merge_sort_array_optimum1(vector<int> &arr1, vector<int> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int left = n-1;
    int right = 0;
    while(left >=0 && right < m) {
        if(arr1[left] > arr2[right]){
            swap(arr1[left], arr2[right]);
            left--, right++;
        } else break;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

void swapIfGreater(vector<int> &arr1, vector<int> &arr2, int ind1, int ind2) {
    if(arr1[ind1] > arr2[ind2]) {
        swap(arr1[ind1], arr2[ind2]);
    }
}

void merge_sort_array_optimum2(vector<int> &arr1, vector<int> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int len = (n + m);
    int gap = (len / 2) + (len % 2);
    while(gap > 0) {
        int left = 0;
        int right = left + gap;
        while(right < len) {
            // arr1 and arr2
            if(left < n && right >=n) {
                swapIfGreater(arr1, arr2, left, right - n);
            }
            // arr2 and arr2
            else if(left >= n) {
                swapIfGreater(arr2, arr2, left - n, right - n);
            }
            // arr1 and arr1
            else {
                swapIfGreater(arr1, arr1, left, right);
            }
            left++, right++;
        }
        if(gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }
}


/*
Find the missing number and repeating number

1. Brute Force -> Two indented loops simple approach.
2. Better -> Using HashArray to keep track of numbers
3. Optimal -> There are two optimal strategies
             1. Using Simple Maths formula in which the the two formulas are found and then solved simultaneously.
             -First eq is the sum of all the ele in the array - sum of all natural no. till the size of the array.
             -Second eq is simpy the squared sums.
             2. Uses Xor technique and bit manipulation.
             Take the xor of all the elements of the array and all natural no. till the size of the array.
             Find the differentiating bit in the answer from xoring.
             split the arr elements into 2 groups of differentiating bit.
             XOR again and find the x & y.
*/
vector<int> findMissingRepeatingNumbers_better(vector<int> &a) {
    int n = a.size();
    int hash[n+1] = {0};
    for(int i = 0; i < n; i++) {
        hash[a[i]]++;
    }
    int repeating = -1, missing = -1;
    for(int i = 1; i<=n; i++) {
        if(hash[i] == 2) repeating = i;
        else if(hash[i] == 0) missing = i;

        if(repeating == -1 && missing == -1) {
            break;
        }
    }
    return {repeating, missing};
}

vector<int> findMissingRepeatingNumbers_optimal1(vector<int> &a) {
    long long n = a.size();
    // S - SN = x-y
    // S2 - S2N = x^2 - y^2
    long long SN = (n*(n+1)) /2;
    long long S2N = (n*(n+1)*(2*n+1)) / 6;
    long long S = 0, S2 = 0;
    for(int i =0; i<n; i++) {
        S += a[i];
        S2 += (long long)a[i] * (long long)a[i];
    }
    long long val1 = S - SN; // x-y
    long long val2 = S2 - S2N; //  x^2 - y^2
    val2 = val2 / val1; // x+y
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    return {(int)x, (int)y};
}

vector<int> findMissingRepeatingNumbers_optimal2(vector<int> &a) {
    long long n = a.size();
    int xr = 0;
    for(int i = 0; i < n; i++) {
        xr = xr ^ a[i];
        xr = xr ^ (i+1);
    }
    int bitNo = 0;
    while(1) {
        if((xr & (1 << bitNo)) != 0) {
            break;
        }
        bitNo++;
    }
    int zero = 0; 
    int one = 0;
    for(int i = 0; i<n; i++) {
        // part of 1 club
        if(((i + 1) & (1<<bitNo)) != 0) {
            one = one ^ (i + 1);
        }
        // zero club
        else {
            zero = zero ^ (i + 1);
        }
        // part of 1 club
        if((a[i] & (1 << bitNo)) != 0) {
            one = one ^ a[i];
        } 
        // zero club
        else {
            zero = zero ^ a[i];
        }
    }

    int cnt = 0;
    for(int i = 0; i<n; i++) {
        if(a[i] == zero) cnt++;
    }
    if(cnt==2) return {zero, one};
    return {one, zero};
}

/*
Count Inversions in an array
i < j & a[i] > a[j] (left ele is greater than right)

1. Brute Force -> Two indented loops simple approach.
2. Optimal -> Using Merge Sort Algorithm with modifications to count the no of time left > than right.
Store the size of the left array as it is sorted.
*/
int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;

    int left = low;
    int right = mid+1;

    int cnt = 0;
    while(left <= mid && right <= high){
        if(arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            cnt += (mid - left +1);
            right++;
        }
    }
    while(left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while(right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
    for(int i=low; i <= high; i++){
        arr[i] = temp[i-low];
    }
    return cnt;
}

int merge_sort(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if(low>=high) return cnt;
    int mid = (low+high) / 2;
    cnt += merge_sort(arr, low, mid);
    cnt += merge_sort(arr, mid+1, high);
    cnt += merge(arr, low, mid, high);
    return cnt;
}

int count_inversion_optimal(vector<int> &a) {
    int n = a.size();
    return merge_sort(a, 0, n-1);
}

/*
Reverse Pairs Problem (Modification of count inversion problem)
    -> i < j && a[i] > 2 a[j]
The above condition needs to be satisfied
i and j are in ascending and consecutive order

1. Brute Force -> Two indented loops simple approach.
2. Optimal -> Using Merge Sort Algorithm with modifications to count the no of time left > than right.
*/
void merge_rev(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;

    int left = low;
    int right = mid+1;

    while(left <= mid && right <= high){
        if(arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }
    while(left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while(right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
    for(int i=low; i <= high; i++){
        arr[i] = temp[i-low];
    }
}

int countPairs(vector<int> &arr, int low, int mid, int high) {
    int right = mid + 1;
    int cnt = 0;
    for(int i = low; i <= mid; i++) {
        while(right <= high && arr[i] > 2 * arr[right]) {
            right++;
        }
        cnt += (right - (mid + 1));
    }
    return cnt;
}

int merge_sort_rev(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if(low>=high) return cnt;
    int mid = (low+high) / 2;
    cnt += merge_sort_rev(arr, low, mid);
    cnt += merge_sort_rev(arr, mid+1, high);
    cnt += countPairs(arr, low, mid, high);
    merge_rev(arr, low, mid, high);
    return cnt;
}

int reverse_pair_optimal(vector<int> &a) {
    int n = a.size();
    return merge_sort_rev(a, 0, n-1);
}


/*
Maximum product subarray

1. Brute Force -> 3 loops Simple iterative approach. (keep prod=1 at first)
2. Better -> 2 loops eliminates the loop to check subarray.
3. Optimal -> Simple observation based approach
        The array has 4 scenarios:
        1. All +ve elements
        2. Even -ve elements (The max product is the whole array)
        3. Odd -ve elements (The max product is either prefix or suffix from that -ve element)
        4. Some zeros (reset the prefix or suffix to 1)

    Kadan algorithm is also there but it is not that intuitive
*/
int max_product_subarray_better(vector<int> &a) {
    int maxi = INT_MIN;
    for(int i = 0; i < a.size(); i++) {
        int prod = 1;
        for(int j = i; j < a.size(); j++) {
            prod = prod * a[j];
            maxi = max(maxi, prod);
        }
    }
    return maxi;
}

int max_product_subarray_optimal(vector<int> &a) {
    int ans = INT_MIN;
    int prefix = 1, suffix = 1;
    int n = a.size();
    for(int i = 0; i < n; i++) {
        if(prefix == 0) prefix = 1;
        if(suffix == 0) suffix = 1;

        prefix = prefix * a[i];
        suffix = suffix * a[n-i-1];
        ans = max(ans, max(prefix, suffix));
    }
    return ans;
}

int main() {
    // cout << nCr_sub_function(4, 2); provide (r-1) and (c-1)
    // vector<int> arr1 = {1, 3, 5, 7};
    // vector<int> arr2 = {0, 2, 6, 8, 9};
    // vector<vector<int>> arr = {{1, 3}, {2, 6}, {8, 9}, {9, 11}, {8, 10}, {2, 4}, {15, 18}, {16, 17}};
    vector<int> arr1 = {2, 3, -2, 4};
    cout << max_product_subarray_optimal(arr1);
    // vector<vector<int>> vec = Intervals_optimal(arr);
    // for(auto it: arr1) {
    //     cout << it << " ";
    // }
    // cout << endl;
    // for(auto it: arr2) {
    //     cout << it << " ";
    // }
    // for (int i = 0; i < vec.size(); i++) { 
    //     for (int j = 0; j < vec[i].size(); j++) 
    //         cout << vec[i][j] << " "; 
    //     cout << endl; 
    // } 
    return 0;
}
