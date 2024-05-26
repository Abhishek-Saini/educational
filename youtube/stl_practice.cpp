#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){
    // STL is a tool

    // Problem -------------------
    // You are given a list of n integers.
    // your task is to calculate the number of distinct values in the list.
    
    
    
    


    
    // Brute force - Compare each element with all other elements that came before it

    // for(int i = 1; i <= n; i++) {
    //     // another loop to check whether this is the first time 
    //     O(n)
        // S.find(A[i]);
    // }
    // Time complexity - O(n^2)
    


    // for(int i = 1; i <= n; i++) {
    //     // auto it = S.find(A[i]);
    //     // S.insert(A[i]);
    // }




    // Efficient approach - Use a set to store the distinct values
    // Intuition - Set is a faster way to do the same thing as above
    // comparing each element with all other elements
    // Time complexity - N * (log(N) + log(N)) = O(nlogn)






    // Bob went to market with his kid. There were n toys in the market.
    // Whenever kid sees a new toy, he wants to buy it.
    // Bob wants to know how many toys his kid bought.








    // It's the same as the above problem. Just there is this story added to it.
    // Story -> Raw Problem -> Brute Force Approach -> Efficient approach -> Code



    // Problem -------------------
    // You are given a array of n integers.
    // Find the number of pairs (i, j) index such that i < j and A[i] == A[j].







    // Brute Force
    // Compare each element with all other elements before it and count this.
    // for counting frequency of an element?
    // Time complexity - O(n^2)






    // Data Structure ??





    // map?
    // same thing as what we did in previous one but with frequency
    // Time complexity - N logN

    // n = 1e5
    // n * (n + 1) / 2
    long long int ans = 0;
    map<int, int> mp;
    int n;
    vector<int> A(n);

    for(int j = 0; j < n; j++) {
        // at this point, only the element before it are present in the map
        ans = ans + mp[A[j]];

        // add to the map, increase frequency
        mp[A[j]]++;
    }

    // [1, 1, 5 ,4, 5, 1], ans = 4
    // mp = {
    //     1 : 3
    //     5 : 2
    //     4 : 1
    // }
    // ans = 0 + 1 + 0 + 0 + 1 + 2 = 4

















    // Problem -------------------
    // You are given a list of n integers and a number k.
    // Find number of pairs (i, j)index such that i < j and A[i] + A[j] = k.










    // Brute Force
    // Compare each element with all other elements before it, A[i] + A[j] == k
    // Time complexity - O(n^2)
    int k;

    // A[i] + A[j] = k

    // A[i] = k - A[j]

    // rem + A[j] = k

    // rem = k - A[j]



    for(int j = 0; j < n; j++) {
        // at this point, only the element before it are present in the map
        int rem = k - A[j];

        ans = ans + mp[rem];

        // add to the map, increase frequency
        mp[A[j]]++;
    }
    // O(nlogn)
    // [1, 4 , 7, 4, 3], k = 8







    // Use map to store the frequency of each element
    // Now we can use map to compare this efficiently
    // Time complexity - ??







    // Problem -------------------
    // What if we find to find A[j] - A[i] = k
    // ??

    // A[j] - element = k
    // element = A[j] - k;


    for(int j = 0; j < n; j++) {
        // at this point, only the element before it are present in the map
        int element = A[j] - k;

        ans = ans + mp[element];

        // add to the map, increase frequency
        mp[A[j]]++;
    }











    // Problem -------------------
    // You are given a array of n integers.
    // find number of subarrays with sum equal to k.

    // Prefix[i] = Sum of first i elements = 1, 2 ,3 , i 
    // i < j
    // Prefix[j] - Prefix[i] = sum of elements between i + 1 to j
    // 1, 2, 3, .... i, i + 1.....j  -  1, 2, 3.....i
    // i + 1, i + 2.......j
    
    // Prefix[j] - Prefix[i] = k
    // A[j] - A[i] = k

    // Prefix[i + 1] = Prefix[i] + A[i]
    // O(n) + O(nlogn)











    // Problem -------------------
    // You are given a list of n integers.
    // Your task is to find the number of pairs (i, j) such that i < j and A[i] != A[j]
    
    

    // total number of pairs = total
    // pairs equal = equal
    // pairs not equal = total - equal

    // pairs with A[i] == A[j], these pairs = 500
    // total number of pairs = (n - 1) * (n) / 2 - 500 = not equal pairs
    // 0 + 1 + 2 + 3......... n - 1
    // j = 0, 0 elements before this
    // j = 1, 1 
    // j = 2, 2


    // x + y = total
    // find x, that may be hard to find
    // but finding y is easy
    // x = total - y








    // Brute Force
    // Compare each element with all other elements before it and count not equal elements
    // Time complexity - O(n^2)

    


    // Which data structure we can use to find elements which are not equal to the current element
    // ??






    // Problem -------------------
    // You are given a list of n integers.
    // Your task is to find the number of triplets (i, j, k) such that i < j < k and A[i] == A[j] == A[k].

    // X elements
    // X * (X - 1) / 2

    // n elements
    // n * (n - 1) / 2

    for(int k = 0; k < n; k++) {
        int freq = mp[A[k]];

        ans = ans + freq * (freq - 1) / 2;



        // increase freq in map
        mp[A[k]]++;
    }
    // [1, 3, 1, 1, 3, 3, 1], ans = 5





    // what do we do?






    // map - stores the frequency of each element
    // At ith index, what do we do now?
    // Time complexity - ??



    // Problem -------------------
    // We are getting operations
    // - add an integer - remove an integer [which is present]
    // After each new integer, find distinct values

    // add 5 [5] - 1
    // add 10 [5, 10] - 2
    // add 5 [5, 5, 10] - 2
    // del 10 [5, 5] - 1
    // del 5 [5] - 1


    int distinct_count = 0;
    int queries;
    while(queries--) {
        int x;
        // add x
        {
            mp[x]++;
            if(mp[x] == 1) {
                distinct_count++;
            }
        } 
        // del x
        {
            mp[x]--;
            if(mp[x] == 0) {
                distinct_count--;
            }
        }
    }








    // We solved distinct values problem in the begining
    // Difference - we have to remove as well
    // Data structure ??






















    // Problem -------------------
    // In a movie festival n movies will be shown.
    // You know the starting and ending time of each movie. You can watch one movie at a time.
    // What is the maximum number of movies you can watch entirely?
    // ??









    // Problem -------------------
    // Maintain median
    // We are getting operations - add new integer to the list
    // After each new integer, find median
    // Median - middle element of the sorted array
    // ??
    






    // Two sets?





    // What if we had to delete as well?
    // ??






    // rebalance the sets













    // Code


    struct Median {
        void balance() {
            while(left.size() < right.size()) {
                left.insert(*right.begin());
                right.erase(right.begin());
            }

            while(left.size() > right.size()) {
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

        multiset<int> left, right;
    };


    return 0;
}