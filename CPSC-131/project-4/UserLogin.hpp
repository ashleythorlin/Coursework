#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

class UserLogin {
private:

    unordered_map< string, string > table;


public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password

};

UserLogin::UserLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS

//This function should open up the given file and read in the data, and use it to fill the table.The file has a userName and corresponding passWord on each line.
//You should store each userName as a key, and the corresponding passWord as its value in the hash table.
void UserLogin::readIn(const string& filename) {
    ifstream file;
    file.open(filename);
    string fileData;

    while (getline(file, fileData)) {
        stringstream sstream(fileData);
        string userName, passWord;
        sstream >> userName >> passWord;
        table[userName] = passWord;
    }
}


//returns the number of users
size_t UserLogin::numberOfUsers() {
    return table.size();
}

//return the passWord of the user with the given userName.If the user does not exist, then return “Non-existent User”.
string UserLogin::passWordCheck(const string& userName) {

    unordered_map<string, string>::iterator it = table.find(userName);

    if (it == table.end()) {
        return "Non-existent User";
    }
    else {
        return table[userName]; //does this even work ??
    }

}

//return the bucket number where the user with the given userName is located
size_t UserLogin::wordBucketIdMethod1(const string& userName) {
    return table.bucket(userName);
}

//There is more than one way to find the bucket number where the user with the given userName is located.This implementation should be another way, different from the previous function.
size_t UserLogin::wordBucketIdMethod2(const string& userName) {
    size_t max = table.bucket_count();
    for (int bucket = 0; bucket < max; bucket++) {
        for (auto it = table.begin(bucket); it != table.end(bucket); ++it)
        {
            if (it->first == userName) {
                return bucket;
            }
        }
    }
    return 0;
}

//return true if the user with the given userName exists in the table, false otherwise
bool UserLogin::validateUser(const string& userName) {
    unordered_map<string, string>::iterator it = table.find(userName);

    if (it == table.end()) {
        return false;
    }
    else {
        return true;
    }
}

//return true if given userName, passWord combination exists in the table, false otherwise
bool UserLogin::authenticateUser(const string& userName, const string& passWord) {
    unordered_map<string, string>::iterator it = table.find(userName);

    if (it == table.end()) {
        return false;
    }
    else {
        if (table[userName] == passWord) {
            return true;
        }
        return false;
    }

}
