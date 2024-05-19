#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

int main(){
    // #include <bits/stdc++.h> to include everything in the standard library
    // STL - Standard Template Library
    // faster, shorter, easier code
    // how to find methods of a container - we will dicuss best place to do this in the end

    // Vectors - dynamic arrays with the ability to insert elements or pop elements from the back
    // no need to specify the size in the beginning
    vector<int> v; // list of elements of type int
    // empty
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout << v[0] << " " << v[1] << " " << v[2] << "\n"; // 1 2 3

    v.pop_back(); // remove the last element
    cout << v.size() << "\n"; // 2
    cout << v[0] << " " << v[1] << "\n"; // 1 2

    v.clear(); // clear the vector
    cout << v.size() << "\n"; // 0

    v.assign(5, 100); // assign 5 elements with value 100
    cout << v.size() << "\n"; // 5
    cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << "\n"; // 100 100 100 100 100

    v.resize(12);
    cout << v.size() << "\n"; // 12

    // vector is implemented?
    // array in memory
    // 7, [10]
    // v.size() = 7
    // 11 th element - size allocated is less
    // [20] [40] [80] -- what's the time complexity?
    // O(n)

    vector<int> newVec(5);
    newVec.push_back(12); // 12 is 0th element or 5th element by index ?
    cout << newVec[0]; // 0

    // [1, 4, 5, 10, 12, [500] 15....]
    newVec[0] = 12;
    // [12, 4, 5........]




    // Queue - FIFO
    // first in first out
    queue<int> q;
    q.push(1);
    // push -> [1] -> out
    q.push(2);
    // -> [2 1] 
    q.push(3);
    // -> [3 2 1]

    cout << q.front() << "\n"; // 1
    q.pop(); // remove the first element
    // [3 2] - 2
    cout << q.front() << "\n"; // 2
    q.pop();
    cout << q.front() << "\n"; // 3

    // useful for something like BFS




    // Pairs - used to store pairs of elements
    pair<int, int> intPair;

    intPair.first = 12;
    intPair.second = 20;
    cout << intPair.first << " " << intPair.second << "\n"; // 12 20


    // Person's name and marks
    // cost of a food item and calories
    // cost of an item and value of an item
    // color of a ball and price of that ball
    
    // data types can be different as well
    pair<string, int> strIntPair;
    strIntPair.first = "Hello";
    strIntPair.second = 10;

    // pair can be used to return multiple values from a function
    // pair<int, int> dsd(int x) {
    //     int y, z;
    //     // do something
    //     make_pair(y, z);
    // }
    pair<string, vector<pair<int, int>>> personAndThings;

    // vector<Type> stringIntVector;
    // Type = pair<Type2, Type3>
    // Type2 = string, Type3 = int;

    // pair can be used to associate two values together - Eg. Cost and Weight of an item







    // Sorting
    // sort() - sort the elements in the container

    // sort(starting address, ending address) 1, n = ending_address [n + 1]
    // ending address - address of the element after the last element


    // sort(v.begin(), v.end()) - sort the vector v - default is ascending order
    // sort(v.begin(), v.end(), greater<int>()) - sort in descending order
    vector<int> vectorForSort;

    // [4, 6, 1]
    sort(vectorForSort.begin(), vectorForSort.end()); // less<int>
    // [1, 4, 6] = correct one
    // [6, 4, 1]

    // sort(starting, whenToStop)
    // starting
    // starting++
    // starting == whenToStop

    // v.begin() [4, 6, 10......] v.end() -> 
    // it
    // it++
    // What happens if we write sort(v.end(), v.begin())

    


    sort(vectorForSort.begin(), vectorForSort.end(), greater<int>());
    // [6, 4, 1]

    // When we have in decreasing if write greater<int> will we get in ascending order ?
    // [6, 4, 1]
    sort(vectorForSort.begin(), vectorForSort.end(), greater<int>());
    // [6, 4, 1]





    // sort(v.begin(), v.end(), compare) - sort using a custom compare function
    vector<pair<int, int>> pairVectorForSort;
    // compare function
    // FOCUS on this - return true if a (firstEle) should come before b (secondEle)
    // custome compare function - advanced topic - but very useful

    // pair of int, sort according to second value
    // []() {}
    sort(pairVectorForSort.begin(), pairVectorForSort.end(), [](pair<int, int>& a, pair<int, int>& b){
        if(a.second < b.second) {
            return true;
        }
        else {
            return false;
        }
    });
    // [{12, 1}, {15, -5}, {20, 4}]
    // sort
    // [15,-5} , (12, 1} , {20, 4}]

    // comp(a = {12, 1}, b = {15, -5})
    // (1 < -5) false
    // a shouldn't come before b
    // comp(a = {15, -5}, b = {20, 4})
    // true

    sort(pairVectorForSort.begin(), pairVectorForSort.end(), [](pair<int, int>& a, pair<int, int>& b){
        if(a.second > b.second) {
            return true;
        }
        else {
            return false;
        }
    });
    // [{12, 1}, {15, -5}, {20, 4}]
    // sort

    // x, y, z
    // sort
    // custom_sort(x, y)





    // Let's solve a problem using all of these together
    // vector, pairs of different types and sorting
    
    // N student are there. You know their name and marks.
    // Roll Numbers are assigned in the lexograohical order of their names
    // Print the marks in the order of roll numbers


    vector<pair<string, int>> studentMarks;
    studentMarks.push_back({"Rohan", 90});
    studentMarks.push_back({"Puneet", 80});
    studentMarks.push_back({"Neha", 44});
    studentMarks.push_back({"Raj", 33});
    studentMarks.push_back({"Kavya", 75});

    sort(studentMarks.begin(), studentMarks.end());
    // Kavya




    
    // auto - automatically deduces the data type of the variable
    // range based for loop - iterate over each element in the container

    for(auto student : studentMarks){
        cout << student.second << " "; 
    }
    
    // Vector = (Kavya, 75) (Neha, 44) (Puneet, 80) (Raj, 33) (Rohan, 90)
    // 75 44 80 33 90



    // what if we want to print the names in the decreasing order of marks
    sort(studentMarks.begin(), studentMarks.end(), [](pair<string, int>& firstEle, pair<string, int>& secondEle){
        // return (firstEle.second > secondEle.second); // which one is correct?
        if(firstEle.second > secondEle.second ||
        (firstEle.second == secondEle.second && firstEle.first < secondEle.first));

    });





    for(auto student : studentMarks){
        cout << student.first << " ";
    }    
    // Vector = (Rohan, 90) (Puneet, 80) (Kavya, 75) (Neha, 44) (Raj, 33)
    // Rohan Puneet Kavya Neha Raj





    // set = store unique elements in sorted order
    // set<data_type> set_name;

    // implemented using self balancing binary search tree
    // often Red Black tree

    // insertion, deletion, search - O(logn)
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    for(auto i : s){
        cout << i << " ";
    } // 1 2 3

    s.insert(2); // 2 is already present so this will be ignored
    for(auto i : s){
        cout << i << " ";
    } // 1 2 3

    s.insert(4);
    for(auto i : s){
        cout << i << " ";
    } // 1 2 3 4



    s.erase(2); // erase element 2
    cout << s.size() << "\n"; // 3
    for(auto i : s){
        cout << i << " ";
    } // 1 3 4

    

    cout << s.count(3) << "\n"; // 1 - 3 is present
    // count() will make more sense when we discuss multisets

    s.clear(); // clear the set






    // iterators - begin(), end()
    // begin() - returns an iterator to the first element
    // end() - returns an iterator to the element after the last element
    // iterator is a pointer to the element in the container

    // *iterator - returns the value at the iterator
    // iterator++ - move to the next element
    // iterator-- - move to the previous element

    s.insert(1);
    s.insert(5);
    s.insert(3);
    s.insert(4);
    for(auto i : s){
        cout << i << " ";
    } // 1 3 4 5

    // Answer Time
    auto it = s.begin();
    cout << *it << "\n"; // 1
    it++;
    cout << *it << "\n"; // 3
    it--;
    cout << *it << "\n"; // 1

    auto it2 = s.end(); // points to the element after the last element



    // another way to iterate containers
    for(auto it = s.begin(); it != s.end(); it++){
        cout << *it << " ";
    } // 1 3 4 5


    // lower_bound() - returns an iterator to the first element >= x
    // upper_bound() - returns an iterator to the first element > x
    // both functions return end() if the element is not present
    // O(logn) time complexity
    auto it = s.lower_bound(3);
    cout << *it << "\n"; // 3

    auto it = s.upper_bound(3);
    cout << *it << "\n"; // 4

    auto it = s.lower_bound(10);
    cout << *it << "\n"; // error









    // when not sure if the element is present
    if(it != s.end()){ // s.find() != s.end()
        // dereference *it
        cout << *it << "\n";
    }


    auto it = s.find(3); // returns an iterator to the element if it is present
    s.erase(it); // erase the element at the iterator
    



    // Multisets - can multiple copies of the same element
    // multiset<data_type> set_name;
    // insertion, deletion, search - O(logn)
    // deleting all k copies of the element will take (logn + k) time
    
    multiset<int> ms;
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    for(auto i : ms){
        cout << i << " ";
    } // 1 2 3

    ms.insert(2); // 2 is already there but still it will be inserted
    for(auto i : ms){
        cout << i << " ";
    } // 1 2 2 3

    cout << ms.count(2) << "\n"; // 2 
    // count will find first element
    // iterate to count k copies
    // log(n) + k
    // 100 times, 100


    ms.erase(2); // what's the output after this?

    for(auto i : ms){
        cout << i << " ";
    } // 1 3




    // count() - returns the number of copies of the element
    // more useful in multisets
    // in sets, it will return 0 or 1
    cout << ms.count(2) << "\n"; // 0 - 2 is not present



    // same functions as sets here
    ms.lower_bound(2); // returns an iterator to the first element >= 2
    ms.upper_bound(2); // returns an iterator to the first element > 2
    
    ms.insert(2);
    ms.insert(2);
    for(auto i : ms){
        cout << i << " ";
    } // 1 2 2 3

    auto it = ms.lower_bound(2);
    ms.erase(it); // erase only one copy of 2s

    for(auto i : ms){
        cout << i << " ";
    } // 1 2 3


    // Maps - store key value pairs
    // map<key_type, value_type> map_name;
    // often implemented using self balancing binary search tree

    // insertion, deletion, search - O(logn)
    map<string, int> mp;

    // we have a list of colors
    // count the number of times each color appears

    vector<string> colors = {"red", "blue", "red", "green", "blue", "red"};

    for(auto color : colors){
        mp[color]++;
    }


    for(auto entry : mp){
        // entry is a pair<key, value>
        // first - key, second - value
        // first - color, second - count
        cout << entry.first << " " << entry.second << "\n";
    } // blue 2 green 1 (red 3)

    // find() - returns an iterator to the element if it is present
    // otherwise returns end()
    auto mapIt = mp.find("red");
    // mapIt->second = (*mapIt).second

    cout << mapIt->first << "\n"; // red
    cout << mapIt->second << "\n"; // 3

    mapIt = mp.find("yellow");
    cout << mapIt->second << "\n"; // error


    // can access using [] operator
    cout << mp["red"] << "\n"; // 3
    // mp.size() = 3
    cout << mp["yellow"] << "\n"; // 0
    // mp.size() = 4












    if(mp.find("yellow") == mp.end()){
        cout << "Yellow is not present\n";
    }



    // so that we don't insert yellow in the map

    // erase() - erase the element at the iterator
    mp.erase("red");
    for(auto entry : mp){
        cout << entry.first << " " << entry.second << "\n";
    } // blue 2 green 1

    // clear the map
    mp.clear();
    // size() - returns the number of elements in the map
    cout << mp.size() << "\n"; // 0




    // Problem
    // We get three type of queries
    // 1. New number x is added 
    // 2. Find the number <= x
    // 3. Find the number >= x
    // Which data structure to use?

    // set 
    // multiset ?
    // vector ?

    // logN

    // SetNum
    // first type - SetNum.insert(x)
    set<int> SetNum;
    // 1
    int x;
    SetNum.insert(x);

    // 1 4 10 12 15
    // lower_bound(11) = 12
    // upper_bound(11) = 12
    // 10
    // lower_bound(10) = 10
    // upper_bound(10) = 12
    // it--;
    // 10
    // 2
    // auto it = SetNum.lower_bound(x);
    // always check when not sure if 'it' can be derefenced
    // cout << *it; // okay when it gives equal value
    // but it greater doesn't work
    auto it = SetNum.upper_bound(x);
    it--;
    cout << *it;

    // 1 4 10 12 15
    // lower_bound(10) = 10
    // lower_bound(11) = 12
    // 3
    auto it = SetNum.lower_bound(x);
    // check
    cout << *it;











    // We said that we will discuss something in the end?
    // What was it?
    // cppreference
    // time complexity of
    // count multisets cppreference

    return 0;
}