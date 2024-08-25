#include <bits/stdc++.h>
using namespace std;

/*
Find the row with maximum 1's

vector<vector<int>> mat = {
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1}
    };

return 2 as the second row has maximum no of 1's = 4.
As the 4th row has also 4 1's but always return the lower index with max 1's.

1. Brute force -> Simple Matrix traversal

2. Optimal -> Optimizing the column traversal
    Instead of inner loop using lower bound concept.
*/
int max1sBrute(vector<vector<int>> mat)
{
    int max1s = 0;
    int index = -1;
    int m = mat.size();
    int n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        int currCnt = 0;
        for (int j = 0; j < n; j++)
        {
            currCnt += mat[i][j];
        }
        if (currCnt > max1s)
        {
            max1s = currCnt;
            index = i;
        }
    }
    return index;
}

int lower_bound(vector<int> arr, int k)
{
    int n = arr.size();
    int ind = n;
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] >= k)
        {
            ind = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ind;
}

int max1sOptimal(vector<vector<int>> mat)
{
    int max1s = 0;
    int index = -1;
    int n = mat.size();
    for (int i = 0; i < n; i++)
    {
        int m = mat[i].size();
        int currCnt = m - lower_bound(mat[i], 1);
        if (currCnt > max1s)
        {
            max1s = currCnt;
            index = i;
        }
    }
    return index;
}

/*
Search in 2D matrix

vector<vector<int>> mat = {
        {3, 4, 7, 9},
        {12, 13, 16, 18},
        {20, 21, 23, 29}};
target = 23

1. Brute force -> Using linear search on 2D matrix by using 2 loops.

2. Better -> Performing Binary Search and eliminate the inner loop.

3. Optimal -> Hypothetically convert the 2D mat to 1D array and map the index to matrix index and perform BS.
*/
bool binarySearch(vector<int> &arr, int low, int high, int target)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
        {
            return true;
        }
        else if (arr[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return false;
}

bool search2DMatrixBetter(vector<vector<int>> mat, int n, int m, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (mat[i][0] <= target && target <= mat[i][m - 1])
        {
            return binarySearch(mat[i], 0, m - 1, target);
        }
    }
    return false;
}

bool search2DMatrixOptimal(vector<vector<int>> mat, int n, int m, int target)
{
    int low = 0, high = (n * m) - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int row = mid / m;
        int col = mid % m;

        if (mat[row][col] == target)
        {
            return true;
        }
        else if (mat[row][col] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return false;
}

/*
Search in 2D Matrix ||

vector<vector<int>> mat = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}};
target = 13

Here the above matrix is sorted from left to right and top to bottom.

return the coordinate if the element exists.

1. Brute force -> Simple 2D linear traversal.

2. Better -> Similar to previous 2D binary Search.

3. Optimal -> Start at row = 0 and column = m-1 and observe.
To the left of that element all the values are small and to the bottom of that element all the values are large.
Based on the above logic eliminate the row and column by performing row++ and column--
*/
pair<int, int> search2DMatrix2Optimal(vector<vector<int>> mat, int n, int m, int target)
{
    int row = 0;
    int col = m - 1;

    while (row < n && col >= 0)
    {
        if (mat[row][col] == target)
        {
            return {row, col};
        }
        else if (mat[row][col] > target)
        {
            col--;
        }
        else
        {
            row++;
        }
    }
    return {-1, -1};
}

/*
Find peak element in a matrix

A peak element is an element which is greater than top, bottom, left and right counterpart elements.

Given no 2 adjacent elements will be same.
All the outer elements of the matrix will be -1.

Return the coordinate of any 1 peak element in the matrix.

vector<vector<int>> mat = {
        {4, 2, 5, 1, 4, 5},
        {2, 1, 3, 2, 3, 2},
        {1, 7, 6, 0, 1, 3},
        {3, 6, 2, 3, 7, 2}};

1. Brute force -> Using Linear search.

2. Optimal -> Use the concept of the peak element derived previously for 1D array.
*/
int findMaxIndex(vector<vector<int>> &mat, int n, int col)
{
    int maxValue = -1;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (mat[i][col] > maxValue)
        {
            maxValue = mat[i][col];
            index = i;
        }
    }
    return index;
}

pair<int, int> findPeakElement(vector<vector<int>> &mat, int n, int m)
{
    int low = 0;
    int high = m - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int maxRowIndex = findMaxIndex(mat, n, mid);
        int left = mid - 1 >= 0 ? mat[maxRowIndex][mid - 1] : -1;
        int right = mid + 1 < m ? mat[maxRowIndex][mid + 1] : -1;
        int currElement = mat[maxRowIndex][mid];

        if (currElement > left && currElement > right)
        {
            return {maxRowIndex, mid};
        }
        else if (currElement < right)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return {-1, -1};
}

/*
Median of row wise sorted matrix

vector<vector<int>> mat = {
        {3, 4, 7, 9, 13},
        {12, 13, 16, 18, 20},
        {2, 4, 6, 7, 9}};

In the above matrix both rows and columns are odd. Here n = 3 & m = 5

1. Brute force -> Scan through the whole matrix and transform it into 1D array.
    Sort the computed array.
    Then find the median element.

2. Optimal -> Using BS 
    Find the no of elements <= mid.
    The first occurrence of value > then above computed value is the median.
    Else reduce the search space.
    low = smallest element of the matrix
    high = largest ele of the matrix
*/
int upperBound(vector<int> &arr, int m, int target) {
    int low = 0;
    int high = m - 1;

    while(low <= high) {
        int mid = (low + high) / 2;
        
        if(arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int calculateSmallerEqual(vector<vector<int>> &mat, int n, int m, int target) {
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += upperBound(mat[i], m, target);
    }
    return cnt;
}

int medianOptimal(vector<vector<int>> &mat, int n, int m) {
    int low = INT_MAX;
    int high = INT_MIN;

    for(int i = 0; i < n; i++) {
        low = min(low, mat[i][0]);
        high = max(high, mat[i][m-1]);
    }

    int required = (n * m) / 2;

    while(low <= high) {
        int mid = (low + high) / 2;
        int smallerEqual = calculateSmallerEqual(mat, n, m, mid);

        if(smallerEqual <= required) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}


int main()
{
    vector<vector<int>> mat = {
        {3, 4, 7, 9, 13},
        {12, 13, 16, 18, 20},
        {2, 4, 6, 7, 9}};
    int n = mat.size();
    int m = mat[0].size();
    int target = 13;
    cout << medianOptimal(mat, n, m);
    // cout << res.first << " " << res.second;
    return 0;
}