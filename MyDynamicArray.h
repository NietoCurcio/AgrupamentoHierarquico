// Biblioteca personalizada para arrays dinamicos, usada no arquivo questao5_v2.cpp
#pragma once
#include<iostream>

// Professor, criei essa biblioteca para criar um array dinamico. O C++ possui a biblioteca "vector"
// que faz isso, mas como não podia usar bibliotecas prontas, implementei essa p/ me ajudar
// na minha logica.

// referencias:
// https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-160
// http://www.cplusplus.com/doc/oldtutorial/templates/
// https://www.hackerrank.com/challenges/c-class-templates/problem

namespace MyDynamicArraySpace
{
    template<class T>
    class DynamicArray {
        private:
            T data;
            DynamicArray *prev;
            DynamicArray *next;
            DynamicArray *head;
            DynamicArray *tail;

            void insertNode(T object) {
                DynamicArray* node = new DynamicArray;
                node->data = object;
                node->next = nullptr;

                if(length == 1) {
                    head = node;
                    head->prev = nullptr;
                    tail = head;
                    return;
                }

                tail->next = node;
                node->prev = tail;
                tail = node;
            }

        public:
            int length = 0;

        void push(T object) {
            this->length++;
            insertNode(object);
        }

        DynamicArray() {
        }

        DynamicArray(int tamanho, T element) {
            for(int i = 0; i < tamanho; i++) 
                push(element);
                // preciso de um template specialization para bidimensional
                // porque cada posição de array (que é um array), estaria apontando para o mesmo
                // array, o que seria errado
                // outra alternativa é dar um .push e adicionar um array de cada vez
        }

        T pop() {
            T data = tail->data;
            DynamicArray* tmp = tail->prev;
            if(tmp) tmp->next = nullptr;
            delete tail;
            tail = tmp;
            length--;
            return data;
        }

        T& operator[](const int idx) {
            int i = 0;
            DynamicArray* tmp = head;
            for(tmp; tmp != nullptr && i < length; tmp = tmp->next) {
                if(idx == i) break;
                i++;
            }
            return tmp->data;
        }
    };

    // template specialization
    template <class T2>
    class DynamicArray<DynamicArray<T2>> {
        DynamicArray<T2> data;
        DynamicArray<DynamicArray<T2>> *prev;
        DynamicArray<DynamicArray<T2>> *next;
        DynamicArray<DynamicArray<T2>> *head;
        DynamicArray<DynamicArray<T2>> *tail;

        public:
            int length = 0;

            DynamicArray<T2>& operator[](const int idx) {
                int i = 0;
                DynamicArray* tmp = head;
                for(tmp; tmp != nullptr && i < length; tmp = tmp->next) {
                    if(idx == i) break;
                    i++;
                }
                return tmp->data;
            }

            void insertNode(DynamicArray<T2> arr) {
                DynamicArray<DynamicArray<T2>>* node = new DynamicArray<DynamicArray<T2>>;
                node->data = arr;
                node->next = nullptr;

                if(length == 1) {
                    head = node;
                    head->prev = nullptr;
                    tail = head;
                    return;
                }

                tail->next = node;
                node->prev = tail;
                tail = node;
            }

            void push(DynamicArray<T2> arr) {
                this->length++;
                insertNode(arr);
            }

            DynamicArray() {}

            DynamicArray(int tamanho, DynamicArray<T2> arr) {
                for(int i = 0; i < tamanho; i++) {
                    DynamicArray<T2> ar(arr.length, arr[0]);
                    push(ar);
                }
            }
    };
}