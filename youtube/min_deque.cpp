#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;

template <typename ElementType>
struct MinStack{
    stack<ElementType> elements, trackMin;
    void push(ElementType x) {
        elements.push(x);
        ElementType minElement = trackMin.empty() ? x : min(x, trackMin.top());
        trackMin.push(minElement);
    }
    void pop() {
        elements.pop();
        trackMin.pop();
    }
    ElementType top() {
        return elements.top();
    }
    ElementType getMin() {
        return trackMin.top();
    }
    int size() {
        return elements.size();
    }
    bool empty() {
        return elements.empty();
    }
};

template <typename ElementType>
struct MinDeque {
    MinStack<ElementType> frontMS, backMS;
    void push_back(ElementType x) {
        backMS.push(x);
    }
    void push_front(ElementType x) {
        frontMS.push(x);
    }
    void pop_back() {
        if (backMS.empty()) {
            moveFromTo(frontMS, backMS);
        }
        backMS.pop();
    }
    void pop_front() {
        if (frontMS.empty()) {
            moveFromTo(backMS, frontMS);
        }
        frontMS.pop();
    }
    ElementType getMin() {
        if (frontMS.empty()) {
            return backMS.getMin();
        }
        if (backMS.empty()) {
            return frontMS.getMin();
        }
        return min(frontMS.getMin(), backMS.getMin());
    }
    int size() {
        return frontMS.size() + backMS.size();
    }
    bool empty() {
        return frontMS.empty() && backMS.empty();
    }
    ElementType front() {
        if (frontMS.empty()) {
            moveFromTo(backMS, frontMS);
        }
        return frontMS.top();
    }
    ElementType back() {
        if (backMS.empty()) {
            moveFromTo(frontMS, backMS);
        }
        return backMS.top();
    }
    // Method to move half of the elements from one stack to another
    // This is what makes the whole idea work in O(1) amortized time
    void moveFromTo(MinStack<ElementType> &from, MinStack<ElementType> &to) {
        MinStack<ElementType> temp;
        int half = (from.size() + 1) / 2;
        while (from.size() > half) {
            temp.push(from.top());
            from.pop();
        }
        while (!from.empty()) {
            to.push(from.top());
            from.pop();
        }
        while (!temp.empty()) {
            from.push(temp.top());
            temp.pop();
        }
    }
};


int main(){
    MinDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_back(40);
    cout << dq.getMin() << endl;
    dq.pop_front();
    cout << dq.getMin() << endl;
    dq.push_back(5);
    cout << dq.getMin() << endl;
    return 0;
}
