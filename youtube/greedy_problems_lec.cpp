#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){

    // Problem -------------------
    // Array of n integers
    // Pick Two integers which have the maximum sum

    // greedy_sum = first_max + second_max

    // new_sum = greedy_sum - second_max + 4th_max
    // (4th_max - second_max) <= 0
    // new_sum <= greedy


















    // Problem -------------------
    // Split N into two numbers such that their product is maximum.
    // N is even.
    // As in N = a + b, a * b should be maximum.

    // greedy x = a = b = N / 2
    // c, d
    // c = x + delta, d = x - delta

    // c * d = (x + delta) * (x - delta) = x * x - delta * delta <= x * x














    // Problem -------------------
    // N jobs are given, each job has a start time, end time.
    // Find the maximum number of jobs that can be done without overlapping.














    // Problem -------------------
    // N jobs are given, each job with a deadline and total completion time.
    // Can we complete all the jobs within their deadlines? Yes or No?
    // We start at time 0 and can complete one job at a time.

    // deadline = [2, 1, 5, 2]
    // time =     [2, 1, 1, 3]

    // greedy = sort according to earliert deadline time and start doing









    // Problem
    // N jobs are given. Each job has a deadline and a profit.
    // Each job can be completed in 1 unit of time.
    // Find the maximum profit that can be achieved.
    // Time starts from 0.

    // profit =   [10, 15, 8, 7, 5]
    // deadline = [0, 1, 2, 4, 1]


    // greedy = sort according to highest profit
    // first job? Deadline 10?
    // should I do it time 0?








    // Problem -------------------
    // Knapsack problem
    // You are given n items, each with a weight and a value.
    // We can take any fraction of the item.
    // You are given a knapsack of capacity W.
    // What is the maximum value you can achieve by putting items in the knapsack?
    
    // weight = [2, 3, 4, 5]
    // value =  [3, 4, 5, 6]
    // Knapsack W = 5

    // greedy = sort according to val / weight, take as much as we can
    // Total Val / Total Weight (Knapsack W)
    
    // sroting by value only doesn't work
    // value = 20 w = 10, value = 19 w = 1, value 18 w = 1
    // knapsack = 10


    // what if fractions are not allowed, we can only take whole object
    // give me a counter-example why this greedy won't work










    // Two arrays are given of N elements each.
    // First array is sorted in inreasing order.
    // You can rearrange the elements of the second array.
    // Find the minimum dot product of the two arrays.
    // sum of a[i] * b[i] should be minimum.

    // a = [1, 2, 3, 4, 5]
    // b = [4, 5, 1, 3, 1]
    // dot product = 1*4 + 2*5 + 3*1 + 4*3 + 5*1 = 4 + 10 + 3 + 12 + 5 = 34


    // greedy = sort b in decreasing order

    // a1 <= a2 <= a3 <= a4 <= a5
    // b1 >= b2 >= b3 >= b4 >= b5
    // Exchange Argument


    // new solution
    // exchange bi and bk 
    // i < k
    // bi >= bk
    

    // new_solution = greedy_solution - a[i] * b[i] - a[k] * b[k] + a[i] * b[k] + b[i] * a[k]
    // new_solution = greedy_solution + a[i] * (b[k] - b[i]) - a[k] * (b[k] - b[i])
    // new_solution = greedy_solution + (a[i] - a[k]) * (b[k] - b[i])


















    // sort b in descending order
    // b = [5, 4, 3, 1, 1]
    // dot product = 1*5 + 2*4 + 3*3 + 4*1 + 5*1 = 5 + 8 + 9 + 4 + 5 = 31















    // Kruskal Algorithm
    // Dijkstra Algorithm
    // Many more algorithms

    return 0;
}