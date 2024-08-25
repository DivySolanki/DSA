#include <bits/stdc++.h>
using namespace std;

/*
Binary Search on answers -> (min)max or (max)min
*/

/*
Aggressive Cows

stalls[] = {0, 3, 4, 7, 10, 9} cows = 4

Place the cows in any stalls where minimum dist between cows is maximum.

EG: Cow 1 -> 0
    Cow 2 -> 4 -> C2 - C1 = 4
    Cow 3 -> 7 -> C3 - C2 = 3
    Cow 4 -> 10 -> C4 - C3 = 3

    Hence the max(min) distance is 3.

1. Brute force -> Sort the array then   perform linear iteration.
    Run the loop from distance = 1 till the a distance can't be satisfied.

2. Optimum -> Using Binary Search on answers -> (min)max or (max)min
*/
bool canWePlace(vector<int> &arr, int distance, int cows)
{
    int cntCows = 1, last = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] - last >= distance)
        {
            cntCows++;
            last = arr[i];
        }
        if (cntCows >= cows)
        {
            return true;
        }
    }
    return false;
}

int AggCowsBrute(vector<int> &arr, int cows)
{
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++)
    {
        if (canWePlace(arr, i, cows) == true)
        {
            continue;
        }
        else
        {
            return i - 1;
        }
    }
    return -1;
}

int AggCowsOptimum(vector<int> &arr, int cows)
{
    sort(arr.begin(), arr.end());
    int n = arr.size();
    int low = 0, high = arr[n - 1] - arr[0];
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (canWePlace(arr, mid, cows) == 1)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return high;
}

/*
Hard!!
Allocate Books

Given a list of books indicating pages and m no of students.

Allocate books to students such that
1. Allocation of books is in contigious order.
2. Each student should be assigned at least 1 book.
3. Each book should be allocated to only one student.

Allocation should be such that maximum no of pages assigned should be minimum and return it.

If not possible, return -1

1. Brute -> Linear search from max(arr) to sum(arr).
i.e. max(arr) -> no of pages that should be assigned to hold a book.

2. Optimal -> Use Binary Search for the above range.

*/
int noOfStudents(vector<int> &arr, int pages)
{
    int pagesStudent = 0;
    int students = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (pagesStudent + arr[i] <= pages)
        {
            pagesStudent += arr[i];
        }
        else
        {
            students++;
            pagesStudent = arr[i];
        }
    }
    return students;
}

int allocateBooks(vector<int> &arr, int students)
{
    if (students > arr.size())
        return -1;
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int noStudents = noOfStudents(arr, mid);
        if (noStudents > students)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low;
}

/*
Painter's Partition / Split array - largest sum

Both the questions are similar.

Given a vector of time taken to paint and k painters.
Split the array into contigious subsets whose max(sum of all subsets) is minimum.

Both the questions are similar to Allocate Books Problem.
*/
int findLargestMinDistance(vector<int> &arr, int k)
{
    if (k > arr.size())
        return -1;
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int noStudents = noOfStudents(arr, mid);
        if (noStudents > k)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low;
}

/*
Hard!!!!!!!!!!

Minimise max adjacent distance between Gas stations.
By adding k new gas stations in the array.

arr[] -> {1, 13, 17, 23}  k = 5

Note: 1. The coordinates of the new k gas stations can be in decimal.
      2. Return maximum of 10^-6 decimal places.
      3. The array is in sorted order.

1. Brute -> 1. Identify the spaces in the array.
            2. Try to place K elements in the space while reducing the distance between em.

2. Better -> Eliminating the double loops and using priority queue.

3. Optimal -> Using Binary Search.
        The range is from [0 ... max(distance between consecutive gas stations)]
*/

long double minimiseMaxDistanceBrute(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<int> howMany(n - 1, 0);
    for (int gasStation = 1; gasStation <= k; gasStation++)
    {
        long double maxSection = -1;
        int maxInd = -1;
        for (int i = 0; i < n - 1; i++)
        {
            long double diff = (arr[i + 1] - arr[i]);
            long double sectionLength = diff / (long double)(howMany[i] + 1);
            if (sectionLength > maxSection)
            {
                maxSection = sectionLength;
                maxInd = i;
            }
        }
        howMany[maxInd]++;
        ;
    }
    long double maxAns = -1;
    for (int i = 0; i < n - 1; i++)
    {
        long double diff = (arr[i + 1] - arr[i]);
        long double sectionLength = diff / (long double)(howMany[i] + 1);
        maxAns = max(maxAns, sectionLength);
    }
    return maxAns;
}

long double minimiseMaxDistanceBetter(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<int> howMany(n - 1, 0);
    priority_queue<pair<long double, int>> pq;
    for (int i = 0; i < n - 1; i++)
    {
        pq.push({arr[i + 1] - arr[i], i});
    }
    for (int gasStation = 1; gasStation <= k; gasStation++)
    {
        auto tp = pq.top();
        pq.pop();
        int secInd = tp.second;
        howMany[secInd]++;
        long double iniDiff = arr[secInd + 1] - arr[secInd];
        long double newSecLen = iniDiff / (long double)(howMany[secInd] + 1);
        pq.push({newSecLen, secInd});
    }
    return pq.top().first;
}

int numberofGasStationsRequired(long double dist, vector<int> &arr)
{
    int cnt = 0;
    for (int i = 1; i < arr.size(); i++)
    {
        int numberInBetween = ((arr[i] - arr[i - 1]) / dist);
        if ((arr[i] - arr[i - 1]) == (numberInBetween * dist))
        {
            numberInBetween--;
        }
        cnt += numberInBetween;
    }
    return cnt;
}

long double minimiseMaxDistanceOptimal(vector<int> &arr, int k)
{
    int n = arr.size();
    long double low = 0;
    long double high = 0;
    for (int i = 0; i < n - 1; i++)
    {
        high = max(high, (long double)(arr[i + 1] - arr[i]));
    }

    long double diff = 1e-6;
    while (high - low > diff)
    {
        long double mid = (low + high) / (2.0);
        int cnt = numberofGasStationsRequired(mid, arr);
        if (cnt > k)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    return high;
}

/*
Median of two sorted arrays

arr1 -> {1, 3, 4, 7, 10, 12} m = 6
arr2 -> {2, 3, 6, 15} n = 4


1. Brute -> Combine (Merge Sort) then resultant arr size is m + n
    as here m + n is 10 (even)
    then median is (x/2)(x/2 - 1)
    else odd addition (x/2).

2. Better -> Solving using pointer without physically merging arrays.

Hard!!!!!!!!
3. Optimal -> Divide the array and find the symmetry position.
*/
double medianBrute(vector<int> &arr1, vector<int> &arr2)
{
    vector<int> arr3;
    int n1 = arr1.size();
    int n2 = arr2.size();
    int i = 0, j = 0;
    while (i < n1 && j < n2)
    {
        if (arr1[i] < arr2[j])
        {
            arr3.push_back(arr1[i]);
            i++;
        }
        else
        {
            arr3.push_back(arr2[j]);
            j++;
        }
    }
    while (i < n1)
    {
        arr3.push_back(arr1[i]);
        i++;
    }
    while (j < n2)
    {
        arr3.push_back(arr2[j]);
        j++;
    }
    int n = (n1 + n2);
    if (n % 2 == 1)
    {
        return arr3[n / 2];
    }
    return (double)((double)(arr3[n / 2]) + (double)(arr3[n / 2 - 1])) / 2.0;
}

double medianBetter(vector<int> &arr1, vector<int> &arr2)
{
    int n1 = arr1.size();
    int n2 = arr2.size();
    int n = (n1 + n2);
    int ind2 = n / 2;
    int ind1 = ind2 - 1;
    int i = 0, j = 0;
    int cnt = 0;
    int ind1el = -1, ind2el = -1;
    while (i < n1 && j < n2)
    {
        if (arr1[i] < arr2[j])
        {
            if (cnt == ind1)
                ind1el = arr1[i];
            if (cnt == ind2)
                ind2el = arr1[i];
            cnt++;
            i++;
        }
        else
        {
            if (cnt == ind1)
                ind1el = arr2[j];
            if (cnt == ind2)
                ind2el = arr2[j];
            cnt++;
            j++;
        }
    }
    while (i < n1)
    {
        if (cnt == ind1)
            ind1el = arr1[i];
        if (cnt == ind2)
            ind2el = arr1[i];
        cnt++;
        i++;
    }
    while (j < n2)
    {
        if (cnt == ind1)
            ind1el = arr2[j];
        if (cnt == ind2)
            ind2el = arr2[j];
        cnt++;
        j++;
    }
    if (n % 2 == 1)
    {
        return ind2el;
    }
    return (double)((double)(ind1el + ind2el)) / 2.0;
}

double medianOptimum(vector<int> &a, vector<int> &b)
{
    int n1 = a.size();
    int n2 = b.size();
    if (n1 > n2)
        return medianOptimum(b, a);
    int low = 0, high = n1;
    int left = (n1 + n2 + 1) / 2;
    int n = n1 + n2;
    while (low <= high)
    {
        int mid1 = (low + high) / 2;
        int mid2 = left - mid1;
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
        if (mid1 < n1)
            r1 = a[mid1];
        if (mid2 < n2)
            r2 = b[mid2];
        if (mid1 - 1 >= 0)
            l1 = a[mid1 - 1];
        if (mid2 - 1 >= 0)
            l2 = b[mid2 - 1];
        if (l1 <= r2 && l2 <= r1)
        {
            if (n % 2 == 1)
                return max(l1, l2);
            return ((double)(max(l1, l2) + min(r1, r2))) / 2.0;
        }
        else if (l1 > r2)
            high = mid1 - 1;
        else
            low = mid1 + 1;
    }
    return 0;
}

/*
Kth element of two sorted arrays

Similar to median to two sorted arrays
*/
int kthElement(vector<int> &arr1, vector<int> &arr2, int k) {
    int n1 = arr1.size();
    int n2 = arr2.size();
    if(n1 > n2) return kthElement(arr2, arr1, k);
    int left = k;
    int n = n1 + n2;
    int low = max(0, k - n2);
    int high = min(k, n1);
    while(low <= high) {
        int mid1 = (low + high) / 2;
        int mid2 = left - mid1;
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
        if (mid1 < n1)
            r1 = arr1[mid1];
        if (mid2 < n2)
            r2 = arr2[mid2];
        if (mid1 - 1 >= 0)
            l1 = arr1[mid1 - 1];
        if (mid2 - 1 >= 0)
            l2 = arr2[mid2 - 1];
        if (l1 <= r2 && l2 <= r1)
        {
            return max(l1, l2);
        }
        else if (l1 > r2)
            high = mid1 - 1;
        else
            low = mid1 + 1;
    }
    return 0;
}


int main()
{
    vector<int> arr1 = {3, 8, 9, 16};
    vector<int> arr2 = {2, 4, 5, 6, 7, 9, 10, 11};
    cout << kthElement(arr1, arr2, 6);
    return 0;
}
