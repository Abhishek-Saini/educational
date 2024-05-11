#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){
    // check if prime is number or not
    // counting number of divisors = 2

    int n;
    int div = 0;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0) div++;
    }
    if(div == 2) {
        // prime
    }
    // O(n)


    // 45
    // 3 divides 45
    // 45/3 = 15 divides 45
    // i divides n
    // n / i also divides n
    // sqrt(n)
    // i * (n / i) = n

    auto countDivisors = [](int n) {
        int div = 0;
        for(int i = 1; i * i <= n; i++) {
            if(n % i == 0) {
                div++;
                if(i != n / i) {
                    div++;
                }
            }
        }
        return div;
    };

    // sqrt(n)
    // i * i <= n
    // i <= sqrt(n)
    // O(sqrt(n))

    // counting divisors of all the numbers from 1 to n
    for(int i = 1; i <= n; i++) {
        int divisors = countDivisors(i);
    }
    // O(n * sqrt(n))


    vector<int> divCnt(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            divCnt[j]++;
        }
    }
    // n = 6
    // [0, 0, 0, 0, 0, 0]
    // i = 1, j = 1, 2, 3, 4, 5, 6
    // [1, 1, 1, 1, 1, 1]
    // i = 2, j = 2, 4, 6
    // [1, 2, 1, 2, 1, 2]

    // n + n / 2 + n / 3 + (n / 4 + n / 5 + n / 6 + n / 7) ........1
    // O(n logn)
    // n + (n / 2 + n / 2) + (n / 4 + n / 4 + n / 4 + n / 4) +....
    // n +    (n) +               (n)
    // n * log(n)


    // find all prime numbers from 1 to n
    // find all divisors, if divCnt == 2 => prime
    // sieve of eratosthenes

    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for(int i = 1; i <= n; i++) {
        if(!isPrime[i]) continue;
        // we are here, this means i is a prime
        for(int j = i + i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }
    // n = 10
    // [false, false, true, true, true, true, true, true, true, true, true]
    // i = 2, j = 4, 6, 8, 10
    // // [false, false, true, true, false, true, false, true, false, true, false]
    // i = 3, j = 6, 9
    // // [false, false, true, true, false, true, false, true, false, false, false]
    // O(n log(log(n)))


    // gcd
    // greatest common divisor
    // euclidian 
    // gcd(a, b) = gcd(a, a - b);
    // gcd(a, b) = gcd(a, a % b) = gcd(a % b, b)
    // gcd(11, 2) = gcd(11, 11 % 2) = gcd(11, 1)
    // 45, 15 = 15
    // 12, 18 = 6
    // 15, 16 = 1 => coprime
    // a = 0, b => b
    

    // lcm = a * b / gcd(a, b)


    // find this value mod (10^9 + 7)
    // find this value - that's it - why complexity for no reason
    // int, long long int
    // x % m = 0.... m - 1

    // (a + b) % m  = (a % m + b % m) % m;
    // (10 + 4) % 3 = (10 % 3 + 4 % 3) % 3 = (1 + 1) % 3 = (2 % 3) = 2
    // (a + b + c) % m = ((a % m + b % m) % m + c % m) % m;
    
    // (a - b) % m = (a % m - b % m) % m = (a % m - b % m + m) % m;
    // (9 - 12) % 7 = (2 - 5) = -3;
    // 1 % 7 = 1....
    // +7
    // 8 % 7 = 1
    // +7
    // 15 % 7 = 1
    // -1 % 7 = 6
    // -7 % 7 = 0

    // (a * b) % m = (a % m * b % m) % m;
    // (a ^ b) % m = (a * a * a * .......) % m;
    // a ^ b = (a ^ (b / 2)) * (a ^ (b / 2));
    // b = 10, b / 2 = 5
    // b = 11, b / 2 = 5, 5 + 5 = 10, so we add more a to make it 11

    // a / b % m = a * (1 / b) = a * (b)^-1
    // 7 * (1 / 7) = 1

    // x * (y) % m = 1
    // m = 7
    // x = 3
    // y = 1, x * y = 3 % 7 = 3
    // y = 2, x * y = 6 % 7 = 6
    // y = 3, 9 = 2
    // y = 5, x * y = 15 % 7 = 1
    // x = 3, modulo inverse of x^(-1) = y = 5

    // a / b % m = a * (1 / b) = a * (b)^-1
    // when m is prime

    // fermat's little theroem
    // inverse of (x) = pow(x, m - 2);
    // x = 3
    // 3 ^ (5) = 243 % 7 = 5

    // a / b % m = a * inverse_modulo(b) % m

    // 15 / 89 % 17 = 15 * inverse_modulo(89) % 17 = 15 * pow(89, 15) % 17;

    // count probability of when this happens
    // 1400 / 3289 % m = 1400 * inverse_modulo(3289, m - 2) % m;

    // Euler's Totient function - can be used when not prime

    // a % m = a, m are co-prime = gcd = 1



    return 0;
}


int pow(int a, long long int b, int m) {
    if(b == 0) {
        return 1;
    }
    int half = pow(a, b / 2, m);
    int ans;
    if(b % 2 == 0) {
        ans = 1LL * half * half % m;
    }
    else {
        ans = 1LL * half * half % m;
        ans = 1LL * ans * a % m;
    }
    return ans;
}
// pow(a % m, b, m);
// pow(10, 7)
// pow(10, 3)
// pow(10, 1)
// pow(10, 0)
// log(b)



int gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
    // is a > b necessary?
    // a = 5, b = 11
    // a = 11, b = 5 (5 % 11)
}
// O(log(n)), n = max(a, b)
// TODO
// 11, 5, 11 % 5 = 1
// x % m = 0... m - 1