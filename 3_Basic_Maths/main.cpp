#include <bits/stdc++.h>
using namespace std;

int count_digits(int n) {
    int count = 0;
    while(n > 0){
        // int lastDigit = n % 10;
        count += 1;
        n = n / 10;
    }
    return count;
}

int reverse_number(int n) {
    int revNum = 0;
    while(n > 0){
        int lastDigit = n % 10;
        revNum = (revNum*10) + lastDigit;
        n = n / 10;
    }
    return revNum;
}

bool palindrome(int n) {
    int temp = n;
    int revNum = 0;
    while(n > 0){
        int lastDigit = n % 10;
        revNum = (revNum*10) + lastDigit;
        n = n / 10;
    }
    if (temp == revNum) return true;
    return false;
}

bool armstrong(int n) {
    int temp = n;
    int sum = 0;
    int power = 0;
    while(temp > 0){
        temp = temp / 10;
        power++;
    }
    temp = n;
    while(n > 0){
        int lastDigit = n % 10;
        sum = sum + round(pow(lastDigit, power));
        n = n / 10;
    }
    if (temp == sum) return true;
    return false;
}

void print_divisors(int n) {
    vector<int> vec;
    for (int i=1; i*i<=n; i++) { // condition i<=sqrt(n)
        if(n%i == 0){
            vec.push_back(i);
            if((n/i) != i) {
                vec.push_back(n/i);
            }
        }
    }
    sort(vec.begin(), vec.end());
    for(auto it: vec) cout << it << " ";
}

bool check_prime(int n) {
    int count = 0;
    for (int i=1; i*i<=n; i++) { 
        if(n%i == 0){
            count++;
            if((n/i) != i) {
                count++;
            }
        }
    }
    if(count == 2) return true;
    return false;
}

// Brute Force
int gcd_brute(int n1, int n2) {
    int gcd = 0;
    for(int i = min(n1, n2); i>=1; i--){
        if(n1%i==0 && n2%i==0){
            gcd = i;
            return gcd;
        }
    }
}

/* 
Optimal (By euclidean algorithm)

The Euclidean algorithm is based on the principle that the GCD of two numbers 
also divides their difference. 
In its optimized form, it repeatedly replaces the larger number by its remainder 
when divided by the smaller number until one of the numbers becomes zero. 
The non-zero number at that point is the GCD.
*/
int gcd_optimal(int n1, int n2) {
    while(n1 > 0 && n2 > 0) {
        if(n1 > n2) n1 = n1 % n2;
        else n2 = n2 % n1;
    }
    if(n1 == 0) return n2;
    return n1;
}

int main() {
    int n1, n2;
    cin >> n1 >> n2;
    print_divisors(36);
    return 0;
}