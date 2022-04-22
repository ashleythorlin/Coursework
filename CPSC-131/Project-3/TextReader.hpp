#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "sanitize.hpp"

using namespace std;

class TextReader {
private:
    map<string, vector<string>> wordFollowers;
public:
    
    // TO DO

    void readIn(const string & filename);
    bool isEndPunctuation(const char & character);
    vector<string> getValues(const string & key);
    
};