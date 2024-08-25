#include <bits/stdc++.h>
using namespace std;

/*
Lower bound 
smallest index such that (arr[ind] >= x) return (index) 
eg: arr = {3, 5, 8, 15, 19, 19, 19, 19}
x = 8 then lb = 2
x = 9 then lb = 3
x = 16 then lb = 4
x = 20 (not present in the range of the array) then lb = 8 (last possible index i.e. size of array)

1. Brute force -> Linear search algorithm
2. Optimum -> Using binary search algorithm 
*/
int lower_bound_optimal(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0;
    int high = n - 1;
    int index = n;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] >= x) {
            index = mid;
            high = mid - 1;
        } 
        else low = mid + 1;
    }
    return index;
}

/*
Upper bound 
smallest index such that (arr[ind] > x) return (index) 
eg: arr = {3, 5, 8, 15, 19, 19, 19, 19}
x = 8 then ub = 3
x = 9 then ub = 3
x = 16 then ub = 4
x = 20 (not present in the range of the array) then ub = 8 (last possible index i.e. size of array)

1. Brute force -> Linear search algorithm
2. Optimum -> Using binary search algorithm 
*/
int upper_bound_optimal(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0;
    int high = n - 1;
    int index = n;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] > x) {
            index = mid;
            high = mid - 1;
        } 
        else low = mid + 1;
    }
    return index;
}

/*
Search Insert position
If element is present then return index.
If it is not present then return the position where it should be inserted

If we observe carefully it is finding the lower bound of the element to insert.

Thus we can use the lower bound
*/
int SI_lower_bound_optimal(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0;
    int high = n - 1;
    int index = n;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] >= x) {
            index = mid;
            high = mid - 1;
        } 
        else low = mid + 1;
    }
    return index;
}

/*
Floor and ceil in the sorted array
Floor -> largest element <= x
Ceil -> smallest element >= x (lower bound)

arr = {10, 20, 30, 40, 50}
x=25 then floor = 20, ceil = 30
x=30 then floor = 30, ceil = 30
*/
int floor(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = -1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] <= x) {
            ans = arr[mid];
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int ceil(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = -1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] >= x) {
            ans = arr[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

vector<int> floor_ceil(vector<int> &arr, int x) {
    return {floor(arr, x), ceil(arr, x)};
}

/*
First and the last occurring index of x.
arr = {10, 20, 30, 40, 50, 50}
x = 50 then first = 4, last = 5
x = 40 then first = 3, last = 3
x = 60 then first = -1, last = -1

1. Brute -> Simple linear search algorithm.
2. Optimum -> 1. Using lower and upper bound.
              2. Using standard binary search.
*/
vector<int> first_and_last_position_optimum1(vector<int> &arr, int x) {
    int n = arr.size();
    int lb = lower_bound_optimal(arr, x);
    if(lb == n || arr[lb] != x) return {-1, -1};
    return {lb, upper_bound_optimal(arr, x) - 1};
}

vector<int> first_and_last_position_optimum2(vector<int> &arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int first = -1, last = -1;

    // finding first occurence
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == x) {
            first = mid;
            high = mid - 1;
        } 
        else if(arr[mid] > x) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    low = 0, high = n - 1;
    // finding last occurence
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == x) {
            last = mid;
            low = mid + 1;
        } 
        else if(arr[mid] > x) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return {first, last};
}

/*
Count Occurences
Similar to first and last occurences just subtract the last - first + 1
*/
int countOccurences(vector<int> &arr, int x) {
    vector<int> ans = first_and_last_position_optimum2(arr, x);
    if(ans[0] == -1) return 0;
    return (ans[1] - ans[0]) + 1;
}

/*
Search in rotated sorted array (Unique elements)

arr = {30, 40, 50, 60, 70, 10, 20};
target = 10

1. Brute force -> Linear search
2. Optimum -> First search for the sorted half
            Simply as the low < mid for sorted left and mid < right for sorted right.

*/
int SearchRotatedSortedUnique(vector<int> &arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while(low < high) {
        int mid = (low + high) / 2;
        if(arr[mid] == target) return mid;
        
        // left sorted
        if(arr[low] <= arr[mid]) {
            if(arr[low] <= target && target <= arr[mid]) high = mid - 1;
            else low = mid + 1;
        }
        // right sorted
        else {
            if(arr[mid] <= target && target <= arr[high]) low = mid + 1;
            else high = mid - 1; 
        }
    }
    return -1;
}

/*
Search in rotated sorted array (Duplicate elements)

Only return does it exist or not.

arr = {30, 40, 50, 50, 50, 60, 70, 10, 20};
target = 10

1. Brute force -> Linear search
2. Optimum -> First search for the sorted half
            Simply as the low < mid for sorted left and mid < right for sorted right.
    But as the elements are duplicate it can occur that low == mid == high then we cannot identify the sorted half.
    In such case we should shrink the array as the mid != target and mid == high == low
    low = low + 1
    high = high - 1
*/
int SearchRotatedSortedDuplicate(vector<int> &arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == target) return 1;
        if(arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low = low + 1;
            high = high - 1;
            continue;
        }
        // left sorted
        if(arr[low] <= arr[mid]) {
            if(arr[low] <= target && target <= arr[mid]) high = mid - 1;
            else low = mid + 1;
        }
        // right sorted
        else {
            if(arr[mid] <= target && target <= arr[high]) low = mid + 1;
            else high = mid - 1; 
        }
    }
    return 0;
}

/*
Minimum in rotated sorted array
(Unique as well as duplicates)
arr = {30, 40, 50, 60, 70, 10, 20};
ans = 10

1. Brute force -> Linear search
2. Optimum -> First search for the sorted half
            and take the minimum from it.
            (Simply as the low < mid for sorted left and mid < right for sorted right.)
    Then eliminate the half and reduce accordingly.
    Repeat this process and eventually min fill be found
*/
int MinimumRotatedSorted(vector<int> &arr) {
    int n = arr.size();
    int low = 0, high = n-1;
    int ans = INT_MAX;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        // for duplicates
        if(arr[low] == arr[mid] && arr[mid] == arr[high]) {
            ans = min(ans, arr[low]);
            low = low + 1;
            high = high - 1;
            continue;
        }
        // optimization 
        // if the search space is already sorted then arr[low] will be smaller.
        if(arr[low] <= arr[high]) {
            ans = min(ans, arr[low]);
            break;
        }
        // left sorted
        if(arr[low] <= arr[mid]) {
            ans = min(ans, arr[low]);
            low = mid + 1;
        }
        // right sorted 
        else {
            ans = min(ans, arr[mid]);
            high = mid - 1;
        }
    }
    return ans;
}

/*
Times the rotated sorted array has been rotated.

Involves finding the minimum in the array and the 
index of that minimum element in the array is the
no. of times for which the array has been rotated.
*/
// using above code with minor changes
int RotatedTimes(vector<int> &arr) {
    int n = arr.size();
    int low = 0, high = n-1;
    int ans = INT_MAX;
    int index = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        // for duplicates
        if(arr[low] == arr[mid] && arr[mid] == arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = low + 1;
            high = high - 1;
            continue;
        }
        // optimization 
        // if the search space is already sorted then arr[low] will be smaller.
        if(arr[low] <= arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            break;
        }
        // left sorted
        if(arr[low] <= arr[mid]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = mid + 1;
        }
        // right sorted 
        else {
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            high = mid - 1;
        }
    }
    return index;
}

/*
Single element in a sorted array
Only one element will be single rest all double.

arr = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6};

1. Brute force -> Linear search
    The element's left and right should not be same then unique.
2. Optimum -> Works on indices
    these even and odd indices are the adjacent indices of duplicates.
    The unique element will create 2 halfs
    (even, odd) -> double element in left half.
    (odd, even) -> double element in right half.
*/
int SingleElement(vector<int> &arr) {
    int n = arr.size();
    int low = 1, high = n-2;
    if(n == 1) return arr[0];
    if(arr[0] != arr[1]) return arr[0];
    if(arr[n-1] != arr[n-2]) return arr[n-1];
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1]) return arr[mid];
        // left half
        if((mid%2 == 1 && arr[mid-1] == arr[mid]) || (mid%2 == 0 && arr[mid+1] == arr[mid])) low = mid + 1;
        // right half
        else high = mid - 1;
    }
    return -1;
}

/*
Peak Element
arr[i-1] < arr[i] > arr[i+1]
Then arr[i] is peak element
In the problem statement it is mentioned to take -infinity on the left and right of the array.

arr = {1, 5, 1, 2, 1};

1. Brute force -> Linear search
    with this condition arr[i-1] < arr[i] > arr[i+1]
2. Optimum -> Identify the curve on which the    peak element lies.
    if the mid is on left increasing curve then the peak element is on right
    if the mid is on right decreasing curve then the peak element is on left
    An additional condition is required in case of multiple peaks.
    As the mid can also point to trench curve
*/
int PeakElement(vector<int> &arr) {
    int n = arr.size();
    int low = 1, high = n-2;
    if(n == 1) return 0;
    if(arr[0] > arr[1]) return 0;
    if(arr[n-1] > arr[n-2]) return n-1;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] > arr[mid+1] && arr[mid] > arr[mid-1]) return mid;
        // increasing curve
        else if(arr[mid] > arr[mid-1]) low = mid + 1;
        // decreasing curve
        else if(arr[mid] > arr[mid+1]) high = mid - 1;
        // trench condition
        else low = mid + 1; // can also be high = mid - 1;
    }
    return -1;
}

int main() {
    vector<int> arr = {1, 5, 1, 2, 1};
    cout << PeakElement(arr);
    // vector<int> ans = first_and_last_position_optimum1(arr, 40);
    // for(auto it: ans) {
    //     cout << it << " ";
    // }
    return 0;
}