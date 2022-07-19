#include <iostream>

void print_array(const std::string& msg, int* array, int n) {
    std::cout << msg;
    for (int i = 0; i < n; ++i) { 
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

int* shift_row(int* row, int size, int shift) { 
    shift %= size;

    int* copy = new int[size];
    memcpy(copy, row, size * sizeof(int));
    if (shift == 0) { return copy; }    

    for (int i = 0; i < size; ++i) { 
        int src = (i + shift) % size;
        copy[i] = row[src];
    }
    return copy;
}

// 3 SHIFT 1 == 0
// 3 SHIFT 2 == 1
// 3 SHIFT 3 == 2
// 3 SHIFT 4 == 3
// 3 SHIFT 5 == 4

// 1 2 3 4  <-- 1 ===    2 3 4 1
// 1 2 3 4  <-- 2 ===    3 4 1 2
// 1 2 3 4  <-- 3 ===    4 1 2 3
// 1 2 3 4  <-- 4 ===    1 2 3 4 
// ...

int main(int argc, const char* argv[]) { 
    int array[] = { 1, 2, 3, 4, 5, 6, 7 };
    int n = sizeof(array) / sizeof(int);

    print_array("before: ", array, n); 

    for (int shift = 0; shift < 100; ++shift) { 
        int* shifted = shift_row(array, n, shift);
        std::cout << "shifted by: " << shift << " ";
        print_array("AFTER:  ", shifted, n);
        delete[] shifted;
    }

    return 0;
} 