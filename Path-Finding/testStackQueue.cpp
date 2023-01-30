#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"

//using namespace cs221util;
using namespace std;

TEST_CASE("deque:: isEmpty") {

    cout << "Testing isEmpty: ";
    Deque<int> d;
    REQUIRE(d.isEmpty() == true);
    d.pushR(1);
    REQUIRE(d.isEmpty() == false);
}

TEST_CASE("deque:: pushR & peekR ") {
    cout << "Testing pushR & peekR: "; 
    Deque<int> d; 
    REQUIRE(d.isEmpty() == true); 
    d.pushR(1); 
    REQUIRE(d.isEmpty() == false);
    REQUIRE(d.peekR() == 1);
    d.pushR(2); 
    REQUIRE(d.peekR() == 2);
}

TEST_CASE("deque:: popR") {
    cout << "Testing popR: "; 
    Deque<int> d;
    REQUIRE(d.isEmpty() == true); 
    d.pushR(1); 
    REQUIRE(d.isEmpty() == false);
    d.pushR(2); 
    REQUIRE(d.popR() == 2);
    REQUIRE(d.popR() == 1);
    REQUIRE(d.isEmpty() == true);
}

TEST_CASE("deque:: peekL & popL ") {
    cout << "Testing peekL & popL: "; 
    Deque<int> d; 
    REQUIRE(d.isEmpty() == true); 
    d.pushR(1); 
    d.pushR(2);
    REQUIRE(d.peekL() == 1); 
    REQUIRE(d.popL() == 1);
    REQUIRE(d.isEmpty() == false);
    REQUIRE(d.peekL() == 2); 
    REQUIRE(d.popL() == 2);
    REQUIRE(d.isEmpty() == true);

}

TEST_CASE("deque: popL & popR") {
    cout << "Testing popL & popR"; 
    Deque<int> d; 
    REQUIRE(d.isEmpty() == true); 
    d.pushR(1); 
    d.pushR(2);
    d.pushR(3);
    REQUIRE(d.isEmpty() == false); 
    REQUIRE(d.peekL() == 1); 
    REQUIRE(d.peekR() == 3); 
    REQUIRE(d.popR() == 3);
    REQUIRE(d.peekR() == 2);
    REQUIRE(d.peekL() == 1);
    REQUIRE(d.popR() == 2);
    REQUIRE(d.peekR() == 1);
    REQUIRE(d.peekL() == 1);
    REQUIRE(d.popR() == 1);
    REQUIRE(d.isEmpty() == true); 
}

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}


TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}

