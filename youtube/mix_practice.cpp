#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){
    // Problem --------------------
    // Given N elements
    // Find sum of Ai XOR Aj for all pairs of i and j 
    // (k1, k2) and (k2, k1) are same pairs => count once

    int n;
    vector<int> A(n + 1);
    long long ans = 0;
    for(int i = 1; i <= n; ++i) for(int j = i + 1; j <= n; j++) {
        ans += A[i] ^ A[j];
    }
    
    for(int bit = 0; bit <= 30; bit++) {
        int cntSet = 0;
        for(int i = 1; i <= n; i++) {
            if(A[i] & (1 << bit)) {
                cntSet++;
            }
        }
        int notSet = n - cntSet;
        // We have two boxes
        // Box 1 have 6 balls, Box 2 have 10 balls
        // pick one ball from each, how many cases are possible
        int totalPairsWithSetBit = cntSet * notSet;

        ans += totalPairsWithSetBit * (1 << bit);
    }





    // Problem --------------------
    // Find sum of XOR of all subarrays [L, R] for all L < R.
    // [L, R] = A[L] ^ A[L + 1] ^ A[L + 1].......A[R]
    



















    // B is prefix XOR array of A
    // B[i] = A[1] ^ A[2] ^ A[3].......A[i]
    // B[L - 1] = A[1] ^ A[2] ^ A[3].......A[L - 1]
    // B[R] = A[1] ^ A[2] ^ A[3].......A[R]

    // [L, R] = B[L - 1] ^ B[R] = A[L] ^ A[L + 1] ^ A[L + 1].......A[R]

    // Just XOR of two elements in array B (prefix array)












    // Problem --------------------
    // Maintain median
    // We are getting operations
    // 1. add new integer
    // 2. remove integer
    // 3. find median
    // Median - middle element of the sorted array
    // ??


    // Find kth smallest element
    






















    struct Median {
        void balance() {
            while(left.size() < right.size()) { // left.size() < k
                left.insert(*right.begin());
                right.erase(right.begin());
            }

            while(left.size() > right.size()) { // left.size() > k
                right.insert(*left.rbegin());
                left.erase(left.find(*left.rbegin())); // OR left.erase(prev(left.end()));
            }

        }

        void insert(int x) {
            if(x < *left.rbegin()) left.insert(x);
            else right.insert(x);

            balance();
        }

        void erase(int x) {
            auto it = right.find(x);
            if(it != right.end()) right.erase(it);
            else left.erase(left.find(x)); // Why deleting like this? Why not directly left.erase(x) ?

            balance();
        }

        int getMedian() {
            // check for 0 size
            if(left.size() == right.size()) {
                return (*left.rbegin() + *right.begin()) / 2;
            }
            return *left.rbegin();
        }

        multiset<int> left, right;
    };








    // Problem --------------------
    // There is a street of length n whose positions are numbered 0, 1, 2.....n.
    // Initially there are light at position 0 and n.

    // Now n - 1 sets of lights are added to the street one after another.
    // Your task is to calculate the length of the longest passage
    // without lights after each addition.


    // Bonus Problem 1
    // Let's say we have numbers written at every position
    // After each addition, calculate maximum of (length of passage without lights) * (sum of elements in that passage)



    // Bonus Problem 2
    // Let's say we have numbers written at every position
    // After each addition, calculate maximum of (length of passage without lights) * (max element in that passage)

















    // Code
    set<int> lights;
    multiset<int> passageLength, maxValue;

    lights.insert(0);
    lights.insert(n);

    passageLength.insert(n); // n * (whole array sum)

    for(int times = 1; times <= n - 1; times++) {
        int pos;
        cin >> pos;

        // find the nearest lights in both directions
        auto it = lights.lower_bound(pos);
        int right = *it;
        int left = *prev(it);

        // update passageLength
        passageLength.erase(passageLength.find(right - left)); // (right - left) * (subarray sum [left, right])
        passageLength.insert(pos - left); // (pos - left) * (subarray sum [left, pos])
        passageLength.insert(right - pos); // (right - pos) * (subrray sum [pos, right])

        // update lights
        lights.insert(pos);

        // find max gap
        cout << *passageLength.rbegin() << " ";
    }


    // find max of passageLength * (sum of elements in that subarray)


    // 1 5 1 5 4















    // Problem --------------------
    // Array of N elements
    // K operations we can do
    // In each operation, we can set any bit of any element.
    // Find the maximum possible AND of all elements after K operations



    // for any bit, when is AND 1 ? - all set?
    // we will try to make MSB 1 first? Why?

    // 2 ^ 0 + 2 ^ 1........2 ^ i = 2 ^ (i + 1) - 1   <  2 ^ (i + 1)

    // bit.....30 -> 0
    // bit 30 = how many operations are needed? = number of elements where 30th bit is not set





























    // Problem --------------------
    // Array of N elements (positive and negative) N <= 5000
    // Find the maximum subarray sum
    // We can increase K elements by X (X >= 0)

    // Find for all values of K from 0 to N




    // Let's say K is fixed
    // Find all possible subarray sums and take maximum

    int mx = 0, k, x;
    for(int l = 1; l <= n; l++) {
        int sum = 0;
        for(int r = l; r <= n; r++) {
            sum += A[r];
            int cntWhichCanBeIncreased = min(k, r - l + 1);
            mx = max(mx, sum + cntWhichCanBeIncreased * x);
        }
    }

    // O(n * n)


    // O(n ^ 3)



    // z length = max sum of any z length subarray = sum + min(k, z);

    // max sum of 1-length subarray
    // max....... 2-length......
    // .....
    // .....
    // max........n-length subarray

    vector<int> maxSumOfLength(n + 1, 0);

    for(int l = 1; l <= n; l++) {
        int sum = 0;
        for(int r = l; r <= n; r++) {
            sum += A[r];
            int len = r - l + 1;
            maxSumOfLength[len] = max(maxSumOfLength[len], sum);
        }
    }


    for(int k = 0; k <= n; k++) {
        int mx = 0;
        for(int z = 1; z <= n; z++) {
            int sum = maxSumOfLength[z]; // max sum we have found
            int cnt = min(z, k);
            mx = max(mx, sum + cnt * x);
        }
    }

    // O(n ^ 2)
    // Homework - Can we do it better than this?























    // Problem --------------------
    // N people standing in queue 1 to N, N <= 1e5
    // All are friends except M pairs, M <= 1e5
    // Find number of sub-segments in which everyone is friends with each other

    // 4 people
    // [1 , 4] are not friends
    // [1] [2] [3] [4] [1, 2], [1, 2, 3], [2, 3], [2, 3, 4] [3, 4]...


    // 7 people
    // [1, 4], [2, 6], [4, 6] are not friends
    // [5, 6, 7]
    // how many sub-segmentes ending at 1 = 1
    // ending at 2 = 2
    // ending at 3 = 3
    // ending at 4 = 3
    // 5 = 4
    // 6 = 2
    // 7 = 3




    // Maximum previous element which is not friend
    // MaxPrevious[i]

    vector<int> maxPrevious(n + 1); // iterate over m pairs and store this
    int ans = 0;
    int left = 1;
    
    for(int right = 1; right <= n; right++) {
        left = max(left, maxPrevious[right] + 1);
        ans += right - left + 1;
    }


    





































    // 1. Homework Problem from bit manipulation lecture
    // 2. Remaining Hard Median problem from stl lecture
    // 3. Homework Problem from sorting and searching lecture
    // 4. https://codeforces.com/problemset/problem/1669/H
    // 5. https://codeforces.com/problemset/problem/1644/C
    // 6. https://codeforces.com/problemset/problem/1771/B

    return 0;
}