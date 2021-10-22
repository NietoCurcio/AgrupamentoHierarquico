// arquivo de teste dos módulos
#include "MyDynamicArrayLk.h"
// #include "MyDynamicArrayRealloc.h"
#include <iostream>

using namespace std;
using namespace MyDynamicArrayLkSpace;
// using namespace MyDynamicArrayReallocpace;

void create1(int length) {
    DynamicArray<bool> printed;
    for(int i = 0; i < length; i++) {
        printed.push(false);
    }
    cout << printed.length << endl;
}

void create2(int length) {
    DynamicArray<bool> printed(length, false);
    cout << printed.length << endl;
}

void create3(int length) {
    DynamicArray<DynamicArray<bool>> printed;
    for(int i = 0; i < length; i++) {
        DynamicArray<bool> ar(length, false);
        printed.push(ar);
    }
    cout << printed.length << endl;
}

void create4(int length) {
    DynamicArray<DynamicArray<bool>> printed(length, DynamicArray<bool>(length, false));
    cout << printed.length << endl;
}

int main() {
    DynamicArray<int> array(3, 1);
    array.push(1);
    array[0] = 10;
    array.pop();
    array.pop();
    array.pop();
    array.push(5);

    int item = array.pop();
    array.push(4);
    for(int i = 0; i < array.length; i++) {
        cout << array[i] << endl;
    }
    cout << "fim loop" << endl;
    cout << item << endl;

    printf("Teste 1\n");
    DynamicArray<DynamicArray<bool>> N(3, DynamicArray<bool>(2, false));
    N[0][0] = true;
    for(int i = 0; i < N.length; i++) {
        for(int j = 0; j < N[0].length; j++) {
            printf("%d ", N[i][j]);
        }
        printf("\n");
    }

    printf("Teste 2\n");
    DynamicArray<DynamicArray<bool>> M;
    M.push(DynamicArray<bool>(3, false));
    M.push(DynamicArray<bool>(3, false));
    M.push(DynamicArray<bool>(3, false));
    M[2][1] = true;
    for(int i = 0; i < M.length; i++) {
        for(int j = 0; j < M[0].length; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    M.clear();
    M.push(DynamicArray<bool>(3, false));
    array.clear();
    array.push(2);
    array.push(3);
    cout << array[0] << endl;
    cout << array[1] << endl;
    // create1(2000);
    // create2(2000);
    // create3(2000);
    // create4(2000);
    return 0;
}