// Biblioteca personalizada para arrays dinamicos, usada no arquivo questao5_v2.cpp
#pragma once
#include<iostream>

// Professor, criei essa biblioteca para criar um array dinamico.

// referencias:
// https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-160
// http://www.cplusplus.com/doc/oldtutorial/templates/
// https://www.hackerrank.com/challenges/c-class-templates/problem

namespace MyDynamicArrayReallocSpace
{
    template<class T>
    class DynamicArray {
        T* array = (T*)calloc(0, sizeof(T));
        // T* t = std::allocator<T>.allocate(size) e T* t = new[T] do C++ também funcionam

        public:
            int length = 0;
            // sizeof(array)/sizeof(*array) não funciona porque não se sabe o tamanho de array
            // em tempo de compilação, como funcionaria com arrays estaticos, entao
            // é preciso manter o estado do tamanho

        void push(T object) {
            // printf("Felipe\n");
            this->array = (T*)realloc(this->array, ((this->length + 1) * sizeof(T)));
            this->length++;
            array[this->length - 1] = object;
        }

        DynamicArray() {}

        // N(3, DynamicArray<bool>(3, false));
        DynamicArray(int tamanho, T element) {
            this->array = (T*)realloc(this->array, ((this->length + tamanho) * sizeof(T)));
            this->length = tamanho;
            for(int i = 0; i < tamanho; i++) 
                this->array[i] = element;
                // preciso de um template specialization para bidimensional
                // porque cada posição de array (que é um array), estaria apontando para o mesmo
                // array, o que seria errado
                // outra alternativa é dar um .push e adicionar um array de cada vez
        }

        T pop() {
            T item = array[this->length - 1];
            this->length -= 1;
            if (length == 0) {
                // delete[] array;, onlyr for "new" keyword
                free(array);
                array = (T*)calloc(0, sizeof(T));
            } 
            return item;
        }

        T& operator[](const int idx) {
            return this->array[idx];
        }
    };

    // template specialization
    template <class T2>
    class DynamicArray <DynamicArray<T2>> {
        DynamicArray<T2>* array = (DynamicArray<T2>*)calloc(0, sizeof(DynamicArray<T2>));
        public:
            int length = 0;

            DynamicArray<T2>& operator[](const int idx) {
                return this->array[idx];
            }

            void push(DynamicArray<T2> ar) {
                // printf("Felipe2\n");
                this->array = (DynamicArray<T2>*)realloc(this->array, ((this->length + 1) * sizeof(DynamicArray<T2>)));
                this->length++;
                array[this->length - 1] = ar;
            }

            DynamicArray() {}

            DynamicArray(int tamanho, DynamicArray<T2> arr) {
                // printf("FELIPEEE\n");
                this->array = (DynamicArray<T2>*)realloc(this->array, ((this->length + tamanho) * sizeof(DynamicArray<T2>)));
                this->length = tamanho;
                for(int i = 0; i < tamanho; i++) {
                    DynamicArray<T2> ar(arr.length, arr[0]);
                    // cria um novo ponteiro a cada posição, dessa maneira cada posição é um ponteiro diferente
                    // se tivesse feito array[i] = arr, diretamente, sem criar uma nova instancia,
                    // ao alterar por exemplo a posição 1 de um array interno, alteraria a posição 1 de todos
                    // os arrays internos
                    array[i] = ar;
                }
            }
    };
}