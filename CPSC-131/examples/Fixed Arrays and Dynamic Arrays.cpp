
#include <iostream>

using namespace std;



int main()
{
    
    // Arrays
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    arr[5] = 50;

    arr[6] = 7 + arr[5];

    for (int i = 0; i < 10; i++) {

        cout <<"i = " << i;
        cout << " arr[" << i << "] = " << arr[i];
        
        cout << endl;
        

    }

    // arr[10] : segmentation fault

    // You could also run a loop 10 times and have the user enter the array elements.

     
    //int b[] = arr; //Cannot do this



    // Dynamic arrays
    cout << "Enter size of dynamic array ";
    int n;

    cin >> n;

    int* dArr = new int[n];

    cout << endl<<"Enter elements "<<endl;
    

    for (int i = 0; i < n; i++) {

        cout << "i = " << i;
        cout << " dArr[" << i << "] = ";
        cin >> dArr[i]; // can use []
        cout << endl;

    }

    for (int i = 0; i < n; i++) {

        cout << "i = " << i;
        cout << " dArr[" << i << "] = " << *(dArr + i); // also can use this notation

        cout << endl;

    }

    delete[] dArr; // deallocate dynamic array
    
    return 0;
    
    
}