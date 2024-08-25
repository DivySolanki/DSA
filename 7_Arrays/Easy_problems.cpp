#include <bits/stdc++.h>
using namespace std;

/*
For all the below problems. Learn in the following way
1. Brute
2. Better
3. Optimal

All the listed solution below are implemented in Optimal way.
*/

int largest_element(vector <int> &arr) {
    int largest = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if(arr[i] > largest) largest = arr[i];
    }
    return largest;
}

int second_largest_element(vector <int> &arr) {
    int largest = arr[0];
    int slargest = INT_MIN;
    for (int i = 0; i< arr.size(); i++) {
        if(arr[i] > largest) {
            slargest = largest;
            largest = arr[i];
        }
        else if (arr[i] < largest && arr[i] > slargest) {
            slargest = arr[i];
        }
    }
    if(slargest == INT_MIN) {
        return -1;
    }
    return slargest;
}

int second_smallest_element(vector <int> &arr) {
    int smallest = arr[0];
    int ssmallest = INT_MAX;
    for (int i = 0; i< arr.size(); i++) {
        if(arr[i] < smallest) {
            ssmallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] != smallest && arr[i] < ssmallest) {
            ssmallest = arr[i];
        }
    }
    if(ssmallest == INT_MAX) {
        return -1;
    }
    return ssmallest;
}

int isSorted(vector <int> &arr) {
    for(int i = 1; i < arr.size(); i++) {
        if(arr[i] >= arr[i-1]) {

        }
        else {
            return false;
        }
    }
    return true;
}

/*
Asked many times
The array is in sorted order,
just replace the staring indexes with the unique element
and return the no of unique elements
*/
int remove_duplicates(vector <int> &arr) {
    int i = 0;
    for (int j = 1; j < arr.size(); j++) {
        if(arr[i] != arr[j]) {
            arr[i+1] = arr[j];
            i++;
        }
    }
    return i + 1;
}


// left rotate an array
// 1 2 3 4 5 by 2 -> 3 4 5 1 2

// this is the brute force approach takes O(d) extra space.
void left_rotate_brute(vector <int> &arr, int d) {
    int n = arr.size();
    d = d % n;
    int temp[d];
    
    for (int i = 0; i < d; i++) {
        temp[i] = arr[i];
    }

    for (int i = d; i < n; i++) {
        arr[i - d] = arr[i];
    }

    for (int i = n - d; i < n; i++) {
        arr[i] = temp[i-(n-d)];
    }

}

// sub part of optimal approach
void reverse_self(vector <int> &arr, int start, int end) {
    while(start <= end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// this is the optimal approach takes O(1) extra space.
// i.e. it solves it in place
void left_rotate_optimal(vector <int> &arr, int d) {
    int n = arr.size();
    reverse_self(arr, 0, d-1);
    reverse_self(arr, d, n-1);
    reverse_self(arr, 0, n-1);
}

// Move all the zeros to end (Optimal)
int move_zeros(vector <int> &arr) {
    int n = arr.size();
    int j = -1;
    for(int i=0; i<n; i++) {
        if(arr[i] == 0){
            j = i;
            break;
        }
    }
    if(j == -1) return -1;
    for (int i=j+1; i<n; i++) {
        if(arr[i] != 0) {
            swap(arr[i], arr[j]);
            j++;
        }
    }
    return 0;
}

int move_zeros_Optimal2(vector<int> &arr) {
    int first = 0;
    int n = arr.size();
    for(int i=0; i<n; i++) {
        if(arr[i] != 0) {
            swap(arr[i], arr[first]);
            first++;
        }
    }
    return 0;
}

int linear_search(vector <int> &arr, int ele) {
    for (int i = 0; i< arr.size(); i++) {
        if(arr[i] == ele) {
            return i;
        }
    }
    return -1;
}


// Union of 2 *sorted* array (Optimal)
vector <int> union_arr(vector <int> &arr1, vector <int> &arr2) {
    int n1 = arr1.size();
    int n2 = arr2.size();
    vector <int> unionArr;
    int i, j = 0;
    while (i<n1 && j<n2) {
        if(arr1[i]<=arr2[j]) {
            if(unionArr.size() == 0 || unionArr.back() != arr1[i]) {
                unionArr.push_back(arr1[i]);
            } 
            i++;
        } else {
            if(unionArr.size() == 0 || unionArr.back() != arr2[j]) {
                unionArr.push_back(arr2[j]);
            } 
            j++;
        }
    }

    while(i<n1) {
        if(unionArr.size() == 0 || unionArr.back() != arr1[i]) {
                unionArr.push_back(arr1[i]);
        } 
        i++;
    }
    
    while(j<n2) {
        if(unionArr.size() == 0 || unionArr.back() != arr2[j]) {
                unionArr.push_back(arr2[j]);
        } 
        j++;
    }
    return unionArr;
}


// Intersection of 2 *sorted* array (Optimal)
vector<int> intersection_arr(vector <int> &arr1, vector <int> &arr2) {
    vector<int> intersectArr;
    int n1 = arr1.size();
    int n2 = arr2.size();
    int i = 0, j = 0;
    while(i<n1 && j<n2) {
        if(arr1[i] < arr2[j]) {
            i++;
        }
        else if(arr2[j] < arr1[i]) {
            j++;
        }
        else {
            intersectArr.push_back(arr1[i]);
            i++;
            j++;
        }
    }
    return intersectArr;
}


// Find the missing no. in the array
/*
1. Brute force -> using 2 array
2. Better solution -> using hashing
3. Optimal solution -> 2 methods (Sum and XOR)
*/
int missing_number_sum(vector<int> &arr, int N) {
    int totalSum = ((N * (N + 1)) / 2);
    int arrSum = 0;
    for (int i=0; i<N-1; i++) {
        arrSum += arr[i];
    }
    return totalSum - arrSum;
}
// The only drawback of the above solution is that in case of N being 10^5 the totalSum will exceed 10^10 which is not possible to store

// It is solved using the xor method

int missing_number_xor(vector<int> &arr, int N) {
    int xor1 = 0;
    int xor2 = 0;
    int n = N-1;
    for (int i = 0; i<n; i++) {
        xor2 = xor2 ^ arr[i];
        xor1 = xor1 ^ (i+1);
    }
    xor1 = xor1 ^ N;
    return xor1 ^ xor2 ;
}

// Maximum no. of 1's
int find_max_consecutive_ones(vector<int> &arr) {
    int n = arr.size();
    int count = 0;
    int max = 0;
    for (int i = 0; i < n; i++) {
        if(arr[i]==1) {
            count += 1;
            if(max < count) max = count;
        } else {
            count = 0;
        }
    }
    return max;
}

/*
Find the number that appears twice
1. Brute Force -> 2 indented for loops
2. Better -> Hashing and in case if the key is too
large than Map<long long, int>
3. Optimal -> Simply using Xor method.
*/
int repeated_number(vector<int> &arr) {
    int xor_res = 0;
    for (int i = 0; i < arr.size(); i++) {
        xor_res = xor_res ^ arr[i];
    }
    if(xor_res == 0) return -1;
    return xor_res;
}


int main() {
    // vector<int> arr;
    // // int n;
    // // cin >> n;
    // int input;
    // while(cin >> input) {
    //     arr.push_back(input);
    // }
    // bool readingFirstArray = true;

    // while(cin >> input){
    //     if (input == -1) {  
    //         readingFirstArray = false;
    //         continue;
    //     }
        
    //     if (readingFirstArray) {
    //         arr1.push_back(input);
    //     } else {
    //         arr2.push_back(input);
    //     }
    // }
    vector<int> arr1 = {1, 2, 2, 2, 3, 4};
    vector<int> arr2 = {2, 2, 3, 3};
    vector<int> res = intersection_arr(arr1, arr2);
    for(auto it: res) {
        cout << it << " ";
    }
    return 0;
}