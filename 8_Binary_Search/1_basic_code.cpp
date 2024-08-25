#include <bits/stdc++.h>
using namespace std;

int binary_search_iterative(vector<int> &nums, int target) {
    int n = nums.size();
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int binary_search_recursive(vector<int> &nums, int low, int high, int target) {
    if(low > high) return -1;
    int mid = (low + high) / 2;
    if(nums[mid] == target) return mid;
    else if(nums[mid] > target) return binary_search_recursive(nums, low, mid - 1, target);
    return binary_search_recursive(nums, mid + 1, high, target);
}

int main() {
    vector<int> arr = {1, 3, 7, 9, 11, 12, 45};
    cout << binary_search_recursive(arr, 0, arr.size() - 1, 1);
    return 0;
}