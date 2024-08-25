#include <bits/stdc++.h>
using namespace std;

/*
Find the square root of an integer.

1. Brute Force -> Linear search from 1 to n till i * i <= n.
2. Optimum -> Binary Search technique eliminating the no. i.e. (i * i) greater than n.
*/
int SquareRoot(int num) {
    int low = 1, high = num;
    int ans = 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if ((mid * mid) <= num) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans; // or High as it'll also store answer
}

/*
Find the nth root of an integer.

1. Brute Force -> Linear search from 1 to n till (i * till the nth value) == number.
2. Optimum -> Binary Search technique eliminating the no. i.e. (i * till the nth value) greater than n.
*/
int power(int mid, int n, int m) {
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans * mid;
        if(ans > m) return 2;
    }
    if(ans == m) return 1;
    return 0; // ans < m
}

int NthRoot(int num, int N) {
    int low = 1, high = num;
    int ans = 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        int DecisionMid = power(mid, N, num);
        if (DecisionMid == 1) {
            return mid;
        }
        else if (DecisionMid == 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

/*
Koko eating Bananas
Return the min integer k such that koko can eat all bananas within h hours
where k is bananas/hour

pile[] = [3 6 7 11]  h=8  then find k

1. Brute Force -> iterate from 1 till max(arr) and compute the required time. 
If it exceeds h discard else accept.

2. Optimum -> Binary Search technique eliminating the values > than h.
*/
int calculateTime(vector<int> &arr, int h) {
    int n = arr.size();
    int totalTime = 0;
    for(int i=0; i<n; i++) {
        totalTime += ceil((double)arr[i]/(double)h);
    }
    return totalTime;
}

int kokoEatingBanana(vector<int> &arr, int h) {
    int low = 1;
    int high = *max_element(arr.begin(), arr.end());
    while(low <= high) {
        int mid = (low + high) / 2;
        int resTime = calculateTime(arr, mid);
        if(resTime <= h) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low; // it will always point to lowest of possible value
}

/*
Minimum no. of days to make M bouquet
An array of bloomDays will be given we have to satisfy m (no of bouquets required) such that k (no of adjacent flowers required) is also satisfied

bloomDays[] = [7 7 7 7 13 11 12 7] m=2 k=3

1. Brute Force -> iterate from min(arr) till max(arr) and compute the bouquets formed. 
If it is < m discard else accept.

2. Optimum -> Binary Search technique 
*/
bool possible(vector<int> &arr, int day, int m, int k) {
    int cnt = 0;
    int noBouquets = 0;
    int n = arr.size();
    for(int i=0; i<n; i++) {
        if(arr[i] <= day) {
            cnt++;
        } else {
            noBouquets += (cnt/k);
            cnt = 0;
        }
    }
    noBouquets += (cnt/k);
    return noBouquets >= m;
}

int MBouquets(vector<int> &arr, int m, int k) {
    if((m*k) > arr.size()) return -1;
    int low = *min_element(arr.begin(), arr.end());
    int high = *max_element(arr.begin(), arr.end());
    while(low <= high) {
        int mid = (low + high) / 2;
        if(possible(arr, mid, m, k)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

/*
Smallest divisor given a threshold

arr[] = {1, 2, 5, 9} threshold = 6

if divisor = 4
then ceil of every element/divisor = 7
which is > than 6. Thus reject

1. Brute Force -> iterate from 1 till max(arr) and compute the ceil(sum of divisons).

2. Optimum -> Binary Search technique
*/
int sumOfD(vector<int> &arr, int d) {
    int sumD = 0;
    for(int i = 0; i < arr.size(); i++) {
        sumD += ceil((double)arr[i]/(double)d);
    }
    return sumD;
}

int smallestDivisorWithinThreshold(vector<int> &arr, int threshold) {
    if(arr.size() > threshold) return -1;
    int low = 1;
    int high = *max_element(arr.begin(), arr.end());
    while(low <= high) {
        int mid = (low + high) / 2;
        if(sumOfD(arr, mid) <= threshold) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

/*
Least Capacity to ship packages within D days

weights[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}   days = 5

The Capacity ranges from Max(arr) to Sum(arr)
*/
int daysRequired(vector<int> &arr, int capacity) {
    int days = 1;
    int load = 0;
    for(int i = 0; i < arr.size(); i++) {
        if(load + arr[i] > capacity) {
            days += 1; // next day
            load = arr[i]; // move load to next day
        } else {
            load += arr[i]; // load on the same day
        }
    }
    return days;
}

int leastCapacity(vector<int> &arr, int days) {
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);
    while(low<=high) {
        int mid = (low + high) / 2;
        if(daysRequired(arr, mid) <= days) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

/*
(HARD!!!!!!!!)
Find Kth missing element

arr[] = {2, 3, 4, 7, 11} k = 5

1 2 3 4 5 6 7 8 9 10 11 
Here 1 5 6 8 9 10 are missing and 9 is the 5th missing element (k). 
Thus return 9.

1. Brute Force -> Linear Search
    add 1 to the k if the current element is lesser than k.
2. Optimum -> Binary Search Technique.
    BS on Numbers wont work here.
    1. Find the no of missing elements at every index.
    EG: 7 is at 4 place thus 7-4 = 3
    2. Apply BS on that arr of missing elements.
    3. Get high and low as they would end at opposite polarity
    4. more = high - k. more + element at high index.
    5. By derivation high + more == low + k.
*/
int KthElementBrute(vector<int> &arr, int k) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] <= k) k++;
        else break;
    }
    return k;
}

int KthElementOptimum(vector<int> &arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;
    if (k < arr[low]) return k;
    if (k > arr[high] - n) return k + n;
    while(low <= high) {
        int mid = (low + high) / 2;
        int missing = arr[mid] - (mid + 1);
        if(missing < k) {
            low = mid + 1;
        } else {
            high = mid - 1; 
        }
    }
    return low + k; // or high + 1 + k
}

int main() {
    vector<int> arr = {5, 7, 10 ,12};
    cout << KthElementOptimum(arr, 6);
    return 0;
}