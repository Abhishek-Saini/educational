#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){
    // Problem -------------------
    // You are given the arrival and leaving times of n customers in a restaurant.
    // What was the maximum number of customers in the restaurant at any time?
    // arrival = [1, 2, 10, 5, 5]
    // leaving = [4, 5, 12, 9, 12]


    vector<pair<int, int>> times;
    // first value is current time
    // second value is 1 if someone enters and -1 if someone leaves
    int n;
    vector<int> leaving(n), arrival(n); // these are 

    for(int i = 0; i < n; i++) {
        times.push_back({arrival[i], -1});
        times.push_back({leaving[i], 1});
    }
    // {5, 1} - a
    // {5, -1} - b

    sort(times.begin(), times.end());

    int curr = 0;
    int mxCustomers = 0;

    // {0, 1} // 1
    // {0, 1} // 2

    for(auto& pa : times) {
        auto& time = pa.first;
        auto& type = pa.second;
        if(type == -1) {
            curr++;
            mxCustomers = max(mxCustomers, curr);            
        }
        else {
            curr--;
        }
    }











    // Problem -------------------
    // Given an array of n integers.
    // find for each array position the nearest position to its left having
    // a smaller or equal value.
    // [1, 5, 2, 10]

    // monotonic stack can be used to find this in O(n)
    // but we will use sorting and searching to solve this problem in O(n logn)

    
    vector<pair<int, int>> values(n);
    // first is element value
    // second is index
    vector<int> A(n);
    for(int i = 0; i < n; i++) {
        values[i].first = A[i];
        values[i].second = i;
    }
    sort(values.begin(), values.end());

    set<int> indexesCoveredTillNow;

    for(int i = 0; i < n; i++) {
        int current_ind = values[i].second;
        // all the indexes that came before this has element smaller or equal to current

        // out of all indexes covered till now
        // find the max index which is less than current_ind

        auto it = indexesCoveredTillNow.lower_bound(current_ind);
        // [2, 4, 7, 9]
        // lower_bound(5) = 7
        // go to element before it, that's why it--
        // from 7, we reach 4 after it--
        if(it != indexesCoveredTillNow.begin()) {
            it--;
            // *it is the answer
        }
        else {
            // -1 or no answer
        }
        indexesCoveredTillNow.insert(current_ind);
    }
    // [{15, 0}, {20, 4}, {25, 1}]

    // new problem
    // two type of queries
    // add an element x
    // find max element less than <= x





    









    // Problem -------------------
    // You are given a playlist of a radio station.
    // The playlist has a total of n songs.
    // What is the longest sequence of successive songs where each song is unique?
    // [1, 4, 5, 1, 10, 12, 10, 5]

    // [4, 5, 1, 10, 12] -> next is 10
    // [12, 10] -> next is 5
    // [12, 10, 5]

    // iterate
    // right index is at 0th position, longest left = 0
    // r = 1st, 0?
    // r = 2nd, 0?
    // r = 3rd, ?
    // r = last element, ?

    int left = 0;
    int mxLength = 0;
    map<int, int> lastOccurence;
    for(int right = 0; right < n; right++) {
        // A[right] is the current song
        auto it = lastOccurence.find(A[right]);
        if(it != lastOccurence.end()) {
            left = max(left, lastOccurence[A[right]] + 1); //     lastOccurence[A[right]] + 1;
        }
        lastOccurence[A[right]] = right;
        mxLength = max(mxLength, right - left + 1);
    }












    // Problem -------------------
    // You have n coins with positive integer values.
    // What is the smallest sum you cannot create using a subset of the coins?










    // Problem -------------------
    // There is a street of length n whose positions are numbered 0,1,2.....n.
    // Initially there are no traffic light
    // but n sets of traffic lights are added to the street one after another.
    // Your task is to calculate the length of the longest passage
    // without traffic lights after each addition.














    // Problem -------------------
    // N jobs are given, each job has a start time, end time.
    // Find the maximum number of jobs that can be done without overlapping.

    vector<pair<int, int>> jobs;
    // first is start
    // second is end time
    sort(jobs.begin(), jobs.end(), [](pair<int,int> a, pair<int, int> b) {
        return a.second < b.second;
    });

    int jobs_done = 0;
    int finish_time = 0; // time of last finished job

    for(auto& job : jobs) {
        auto& start = job.first;
        auto& end = job.second;

        if(start > finish_time) {
            jobs_done++;
            finish_time = end;
        }
    }

    // cses have all of these problems
    // try to code them yourself and submit it





    
    

    return 0;
}