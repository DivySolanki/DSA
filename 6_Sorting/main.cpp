#include <bits/stdc++.h>
using namespace std;

/*
Takes minimum and places it at the begining

The time complexity is always O(n^2)
*/
void selection_sort(vector<int> &arr, int n) {
    for(int i=0; i<=n-2;i++) {
        int mini=i;
        for(int j=i; j<=n-1; j++){
            if(arr[j]<arr[mini]) mini=j;
        }
        int temp = arr[mini];
        arr[mini] = arr[i];
        arr[i] = temp;
    }
}

/*
Sorts 2 elements in correct order and iteratively decreases the range.

If the array is already sorted then the time complexity is O(n)
else it is O(n^2)
*/
void bubble_sort(vector<int> &arr, int n) {
    for(int i=n-1; i>=0; i--) {
        int didSwap = 0;
        for(int j=0; j<=i-1; j++){
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                didSwap = 1; 
            }   
        }
        if (didSwap == 0){
            break;
        }
    }
}

/*
Takes an element and places it in the correct order.

Best case is O(n) and worst case is O(n^2)
*/
void insertion_sort(vector<int> &arr, int n) {
    for(int i=0; i<=n-1; i++){
        int j = i;
        while(j>0 && arr[j-1] > arr[j]) {
            int temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            j--;
        }
    }
}

/*
Merge sort sub function
*/
void merge(vector<int> &arr, int low, int mid, int high) {
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
    /*
Let's say you are merging the subarrays of arr with low = 3, mid = 4, and high = 6.

Indices in arr that are being merged: 3, 4, 5, 6.
temp array will have elements with indices: 0, 1, 2, 3.
When i = 3 in the loop, temp[i - low] translates to temp[3 - 3] which is temp[0].
When i = 4, temp[i - low] translates to temp[4 - 3] which is temp[1].
And so on...

By using i - low, you map the indices from the original array arr to the corresponding indices in temp and copy the sorted elements back into arr.
    */
    for(int i=low; i <= high; i++){
        arr[i] = temp[i-low];
    }
}

/*
Divide and merge.

Time complexity is O(N log base2 N)
where N is from the merge function and
log base2 N is by recursively dividing the array.

Space complexity is O(N)
*/
void merge_sort(vector<int> &arr, int low, int high) {
    if(low==high) return;
    int mid = (low+high) / 2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid+1, high);
    merge(arr, low, mid, high);
}


/*
Quick sort sub function
*/
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j) {
        while(arr[i] <= pivot && i <= high-1) { // Finding ele greater than pivot
            i++;
        }
        while(arr[j] > pivot && j >= low+1) { // Finding ele smaller than pivot
            j--;
        }
        if(i<j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}
/*
Divide and conqure
1. Pick a pivot and place it in correct position in sorted array.
(The pivot can be any element)
2. Smaller on the left and larger on the right.

Time complexity is O(N log base2 N)

Space complexity is O(1)
*/
void quick_sort(vector<int> &arr, int low, int high) {
    if(low < high) {
        int pIndex = partition(arr, low, high);
        quick_sort(arr, low, pIndex - 1);
        quick_sort(arr, pIndex + 1, high);
    }
}

int main(){
    int n;
    cin >> n;
    // int arr[n];
    // for (int i=0; i<n; i++){
    //     cin >> arr[i];
    // }
    vector<int> arr;
    int input;
    while(cin >> input){
        arr.push_back(input);
    }
    quick_sort(arr, 0, 5);
    for(auto it: arr){
        cout << it << " ";
    }
    return 0;
}

