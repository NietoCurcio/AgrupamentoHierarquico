// MathLibrary.cpp
// compile with: cl /c /EHsc MathLibrary.cpp
// post-build command: lib MathLibrary.obj

#include "MyDynamicArray.h"
#include <iostream>

using namespace std;
using namespace MyDynamicArraySpace;

int main() {
    DynamicArray<int> array(3, 10);
    array.pop();
    array.pop();
    array.pop();

    array.push(1);
    array.push(2);
    array.push(3);

    // int item = array.pop();
    // int item2 = array.pop();
    // array.push(4);
    for(int i = 0; i < array.length; i++) {
        cout << array[i] << endl;
    }
    // cout << "fim loop" << endl;
    // cout << item << endl;
    // cout << item2 << endl;

    // DynamicArray<DynamicArray<bool>> N(3, DynamicArray<bool>(2, false));
    // DynamicArray<DynamicArray<bool>> M;
    // M.push(DynamicArray<bool>(3, false));
    // M.push(DynamicArray<bool>(3, false));
    // M.push(DynamicArray<bool>(3, false));
    // N[0][0] = true;
    // for(int i = 0; i < N.length; i++) {
    //     for(int j = 0; j < N[0].length; j++) {
    //         printf("%d ", N[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("Teste 2\n");
    // M[2][1] = true;
    // for(int i = 0; i < M.length; i++) {
    //     for(int j = 0; j < M[0].length; j++) {
    //         printf("%d ", M[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}