#include<bits/stdc++.h>
using namespace std;

void reverse_print(int i, int n) {
    if(i < 1) return;
    cout << i << endl;
    reverse_print(i - 1, n);
}

// Using Backtracking
void print_numbers(int i, int n) {
    if(i<1) return;
    print_numbers(i-1, n);
    cout << i << endl;
}

void reverse_print_rec(int i, int n){
    if(i > n) return;
    reverse_print_rec(i+1, n);
    cout << i << endl;
}
// end

// Sum of n numbers
// 1. Parametarized approach
void sum_n_p(int i, int sum){
    if(i < 1) {
        cout << sum;
        return;
    }
    sum_n_p(i-1, sum+i);
}

// 2. Functional approach
int sum_n_f(int n){
    if(n == 0) return 0;
    return n + sum_n_f(n-1);
}


// Factorial
// 1. Parametarized approach
void fact_p(int n, int mul) {
    if(n == 0){
        cout << mul;
        return;
    }
    fact_p(n-1, mul*n);
}

// 2. Functional approach
int fact_f(int n){
    if(n == 0) return 1;
    return n * fact_f(n-1);
}

// Reverse Array
// 1. Using 2 pointers
void reverse_using_2p(int arr[],int l, int r) {
    if(l >= r) return;
    swap(arr[l], arr[r]);
    reverse_using_2p(arr, l+1, r-1);
}

// 2. Using 1 pointer
void reverse_using_1p(int arr[],int i, int n) {
    if(i >= n/2) return;
    swap(arr[i], arr[n-i-1]);
    reverse_using_1p(arr, i+1, n);
}

// Palindrome
// Using 1 pointer
bool palindrome_1p(int i, string &s) {
    if(i >= s.size() / 2) return true;
    if(s[i] != s[s.size() - i - 1]) return false;
    return palindrome_1p(i+1, s);
}


// Multiple Recursion
// Fibonnaci
int fibonacci(int n){
    if(n <= 1) return n;
    int last = fibonacci(n-1);
    int slast = fibonacci(n-2);
    return last + slast;
}


int main() {
    cout << fibonacci(4);
    // string s = "MADAM";
    // cout << palindrome_1p(0, s);
    /*
    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    // reverse_using_2p(arr, 0, n-1);
    // reverse_using_1p(arr, 0, n);
    for(auto it: arr) {
        cout << it << " ";
    }
    */
    // fact_p(n, 1);
    // cout << fact_f(n);
    // cout << sum_n_f(n);
    // sum_n_p(n, 0);
    // reverse_print(10, 100);
    // print_numbers(n, n);
    // reverse_print_rec(1, n);
    return 0;
}
