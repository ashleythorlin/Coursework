#include <iostream>
using namespace std;
void swap_call_by_value(int x, int y){
   int temp; 
  temp = x; 
  x = y; 
  y = temp;
   return;
}

void swap_call_by_reference(int& x, int& y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
    return;
}

void swap_call_by_pointer(int* x, int* y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return;
}


int main() {

    int a = 7;
    int b = 10;
    cout << "Before call_by_value Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    swap_call_by_value(a, b);
    cout << endl << "After call_by_value Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    a = 7;
    b = 10;
    cout << endl << "Before call_by_reference Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    swap_call_by_reference(a, b);
    cout << endl << "After call_by_reference Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    a = 7;
    b = 10;
    cout << endl << "Before call_by_pointer Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    swap_call_by_pointer(&a, &b);
    cout << endl << "After call_by_pointer Swap " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}
