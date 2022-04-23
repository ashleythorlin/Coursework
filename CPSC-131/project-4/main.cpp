#include <iostream>
#include <string>
#include <cmath>    // abs()
#include <algorithm>

#include "UserLogin.hpp"

using namespace std;


// Global static variables
static int testCount = 0;
static const int testTotal = 14;
static const string GREEN = "\033[32m";
static const string RED = "\033[31m";
static const string RESET = "\033[0m";

// Prototypes

template <typename T, typename U>
bool assertEquals(const string & nameOfTest, const T & expected, const U & actual);


// Main
int main() {

    UserLogin user;
    user.readIn("userDetails.txt");
    
    assertEquals("numberOfUsers", 4, user.numberOfUsers());

    assertEquals("validateUser: jack", true, user.validateUser("jack"));
    assertEquals("validateUser: bopeep", true, user.validateUser("bopeep"));
    assertEquals("validateUser: alice", false, user.validateUser("alice"));

    assertEquals("passWord check for user: mary", "contrary", user.passWordCheck("mary"));
    assertEquals("passWord check for user: jill", "tumblin'down", user.passWordCheck("jill"));
    assertEquals("passWord check for user: alice", "Non-existent User", user.passWordCheck("alice"));
    
    
    assertEquals("wordBucket: jack", user.wordBucketIdMethod1("jack"), user.wordBucketIdMethod2("jack"));
    assertEquals("wordBucket: jill", user.wordBucketIdMethod1("jill"), user.wordBucketIdMethod2("jill"));

    assertEquals("authenticate user: jack", true, user.authenticateUser("jack","broken.crown"));
    assertEquals("authenticate user: bopeep", true, user.authenticateUser("bopeep", "sheep!lost"));
    assertEquals("authenticate user: alice", false, user.authenticateUser("alice", "***"));
    assertEquals("authenticate user: mary", false, user.authenticateUser("mary", "contraryy"));
    assertEquals("authenticate user: jilll", false, user.authenticateUser("jilll", "tumblin'down"));
    
    cout << endl << RESET << GREEN << "Total tests passed = " << testCount << RESET << "/" << testTotal << endl;

    return 0;
}

template <typename T, typename U>
bool assertEquals(const string& nameOfTest, const T& expected, const U& actual) {
    if (expected == actual) {
        // Green colored text
        cout << RESET << GREEN << "PASSED "
             << RESET << nameOfTest << GREEN << ": expected and actual '" << RESET << actual << GREEN << "'" << RESET << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RESET << RED << "FAILED "
         << RESET << nameOfTest << RED << ": expected '" << RESET << expected << RED << "' but actually '" << RESET << actual << RED << "'" << RESET << endl;
    return false;
}

