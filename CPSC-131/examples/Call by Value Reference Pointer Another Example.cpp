#include <iostream>
#include <string>
using namespace std;

// A. Panangadan
/////////////////////////////////////////////
//// Call by value
//// elegant code but not fast (copy of large parameters); safe: function cannot change parameters
/////////////////////////////////////////////
string getNickname(string x) {
	string nickname = x + "ito";
	x = "World"; // // changing input parameter has no effect
	cout << "Inside getNickname function " << x << endl;
	return nickname;
}

/////////////////////////////////////////////
//// Call by reference with references
//// Fast code, elegant code, but function can change parameters
/////////////////////////////////////////////
string getNicknameReference(string& x) {
	string nickname = x + "ito";
	x = "World"; // changing input parameter!
	cout << "Inside getNicknameReference function " << x << endl;
	return nickname;
}

/////////////////////////////////////////////
//// Call by reference with pointers
//// Fast code, but messy code and function can change parameters
/////////////////////////////////////////////
string getNicknamePointer(string *x) {
	string nickname = *x + "ito";
	*x = "World"; // changing input parameter!
	cout << "Inside getNicknamePointer function " << *x << endl;
	return nickname;
}

///////////////////////////////////////////
// Call by const reference
// Fast code, elegant code, does not allow function to change parameters
///////////////////////////////////////////
string getNicknameConstReference(const string &x) {
	string nickname = x + "ito";
	// x = "World"; // will give a build error
	return nickname;
}



int main() {
	
	string name ="testing";
	cout << "Hello " << getNickname(name) << endl;
	cout << "Hello " << name << endl;

	name = "testing";
	cout << "Hello " << getNicknameReference(name) << endl;
	cout << "Hello " << name << endl;

	name = "testing";
	cout << "Hello " << getNicknamePointer(&name) << endl;
	cout << "Hello " << name << endl;
}


