#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;


int main() {
    // Bit Manipulation


    // 10 = 2 ^ 3 + 2 ^ 1
    // 15 = 1111
    // 10 = 1010
    // 5 = 0101
    // 1 = 0001


    // 21
    // 21 % 2 = 1
    // 1 - first bit
    // 21 >> 1 = 10
    // 10 % 2 = 0 - second bit
    // 10 >> 1 = 5
    // 5 % 2 = 1 - third bit




    // Bitwise Operators
    // & (AND)
    // | (OR)
    // ^ (XOR) - if both bits are different, then 1
    // ~ (NOT)
    // << (Left Shift)
    // >> (Right Shift)


    // 5 = 0101 -> left shift by 1 = 01010 = 10
    // x << 1
    // x << 2 = 4x
    // 18 = 10010 -> right shift by 1 = 1001 = 9
    // x >> 1






    // 2's complement 


    // 32 bit integer, often 1 bit is used for sign
    // So do operations on 31 bits (or 63 bits for long long int)






    // x
    // 1001 & 0101 = 0001
    // 1 << 3 = 1000
    // 00001000 & x = 00000(3rd bit)00000000 = 8 or 0

    // check if ith bit is set
    // y = 1 << i
    // x & y == 0 -> ith bit not set






    // set ith bit
    // y = 1 << i
    // x = x | y  => ith bit is set






    // unset ith bit
    // if bit is already set
    // x = x ^ (1 << i)
    // if we don't care bit is set or not
    // y = 1 << i
    // x = x & (~y)




    // toggle ith bit / flip ith bit
    // x = x ^ (1 << i)
    // xor
    // 0 0 = 0
    // 0 1 = 1
    // 1 0 = 1
    // 1 1 = 0



    // 12     = 1100
    // 12 - 1 = 1011
    // take & = 1000

    // 32     = 100000
    // 32 - 1 = 011111
    // &      = 000000

    // unset rightmost set bit
    // x = x & (x - 1)












    // check if number is power of 2
    // x & (x-1) == 0


    


    // find leftmost set bit (MSB) in 32-bit integer
    int setBit = -1, x;
    for(int bit = 30; bit >= 0; bit--) {
        int y = 1 << bit;
        if((x & y) == 0) {
            // bit not set
            continue;
        }
        setBit = bit;
        break;
    }











    // AND Operation, x & y & z
    // All bits are 1, then only 1
    // Even if one bit is 0, then 0












    // Problem ------------------------------
    // Given array of n integers
    // [l, r] = A[l] & A[l + 1]....... & A[r - 1] & A[r]
    // find subarray with maximum AND
    // all numbers are 0 and 1
    // [0, 1, 1, 0, 1, 0, 0, 0]

    // [12, 14, 16, 9, 11, 56]
    // ith bit for a chosen subarray, when would this bit would be 1
    // x & y <= x
    // x & y <= y












    // Problem ------------------------------
    // Given array of n integers
    // find subarray with minimum AND

    // Take whole array









    // OR Operation
    // All bits are 0, then only 0
    // Even if one bit is 1, then 1












    // Problem ------------------------------
    // Given array of n integers
    // find subarray with maximum OR

    // x | y >= x
    // x | y >= y

    // Take whole array







    // Problem ------------------------------
    // Given array of n integers
    // find subarray with minimum OR

    // min element






    // Problem ------------------------------
    // given two numbers X and Y.
    // You can change any bit, find minimum number of bits to change to make them equal.

    int y;
    int cnt = 0;
    for(int bit = 0; bit <= 30; bit++) {
        // cnt ++ if bits are not same in both
    }









    // XOR Operation
    // if both bits are different, then 1
    // if both bits are same, then 0




    // res = x ^ y
    // count set bits in res - use loop






    // Problem ------------------------------
    // Given array of n integers
    // numbers are repeated twice except one number which is repeated only once
    // find that number K which comes only once
    // xor of all numbers










    // x ^ x = 0
    // A[1] ^ A[2] ^ A[3] ^ A[4] ^ A[5] ^ A[6] ^ A[7] = K









    // Given array of n integers
    // numbers are repeated four times except one number which is repeated only once

    // x ^ x ^ x ^ x = 0
    // xor again









    // Given array of n integers
    // numbers are repeated three times except one number which is repeated only once
    // x ^ x ^ x = x

    // ith bit set cnt = 0, 1, 3, 4, 6, 7....
    // x which repeats three times = ith bit is set => adds 3 to cnt, 3, 6, 9, 12
    // number which comes only once = ith bit is set => adds 1 to cnt, 1
    // 3z, 3z + 1
    // % 3
    // 0, 1
    // 4 % 3 = 1


    int ans = 0, n;
    for(int bit = 0; bit <= 30; bit++) {
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            // cnt ++ if bit is set
        }
        if(cnt % 3 == 1) {
            // ans += 1 << bit;
            // ans |= 1 << bit;
        }
    }

    // all comes five times except one which only comes once
    // 5z, 5z + 1


    // all comes five times except one which only comes twice
    // 5z, 5z + 2








    // Problem ------------------------------
    // Given N
    // Choose N elements < 2 ^ 20
    // AND of all elements should be zero and sum of all elements should be maximum

    // one 0
    // n - 1 elements with all set bits (1111111).....

    // one 1
    // n - 2 elements with all set bit       11111
    // one element with only last bit unset  11110














    // Problem ------------------------------
    // Given N elements
    // Q queries, find XOR of elements in range [L, R] for each query


    // [1, R] - [1, L - 1]















    // Calculate Prefix[X] = A[1] ^ A[2] ^ A[3] ^ ... ^ A[X]

    // Prefix[R] = A[1] ^ A[2] ^ A[3] ^ ... A[L - 1]......A[R - 1] ^ A[R]
    // Prefix[L-1] = A[1] ^ A[2] ^ A[3] ^ ... ^ A[L-1]

    // [L, R] = Prefix[R] ^ Prefix[L-1] = A[L] ^ A[L+1] ^ ... ^ A[R]







    // Problem ------------------------------
    // Given N elements
    // Q queries, find OR of elements in range [L, R] for each query

















    // Problem ------------------------------
    // Given N elements
    // Q queries, find AND of elements in range [L, R] for each query











    // Problem ------------------------------
    // Given N elements
    // calculate the number of such pairs (i,j) where i < j and Ai AND Aj >= Ai XOR Aj




    // Problem ------------------------------
    // Idea used in bitmasking dynamic programming (it's okay if you don't understand this at this point)
    // Given N elements
    // iterate over all possible subsets of N








    // Search and read these three C++ functions
    // __builtin_popcount
    // __builtin_ctz
    // __builtin_clz
    
    return 0;
}