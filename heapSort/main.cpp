#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    static int parent(int key) {
        return (key - 1)/2;
    }
    static int leftChild(int key) {
        return key*2 + 1;
    }
    static int rightChild(int key) {
        return key*2 + 2;
    }
    static int cmp(int* a, int* b) {
        if(*a < *b) return *b;
        else return *a;
    }
    static void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    //Helping functions go here
    static void heapSort(T* start, T* end){
        //TODO
        int size = end - start;
        int* heapArr = new int [size];

        int position = 0;
        while(position < size) {
            heapArr[position] = start[position];
            int reHeapPosition = position;
            while(reHeapPosition != 0 && heapArr[reHeapPosition] < heapArr[parent(reHeapPosition)]) {
                swap(&heapArr[reHeapPosition], &heapArr[parent(reHeapPosition)]);
                reHeapPosition = parent(reHeapPosition);
            }
            position++;
        }
        int* sortedArr = new int [size];
        int staticsize = size;
        int upHeapPosition = 0;
        for(int i = 0; i < staticsize; i++) {
            sortedArr[i] = heapArr[0];
            swap(&heapArr[0], &heapArr[size - 1]);
            size--;
            upHeapPosition = 0;
            while(upHeapPosition <= size) {
                if(leftChild(upHeapPosition) >= size) {
                    if(rightChild(upHeapPosition) < size) {
                        if(heapArr[upHeapPosition] > heapArr[rightChild(upHeapPosition)]){
                            int* maxChildAddress = &heapArr[rightChild(upHeapPosition)];
                            swap(maxChildAddress, &heapArr[upHeapPosition]);
                            upHeapPosition = rightChild(upHeapPosition);
                            continue;
                        }
                    }
                    break;
                }
                if(rightChild(upHeapPosition) >= size) {
                    if(leftChild(upHeapPosition) < size) {
                        if(heapArr[upHeapPosition] > heapArr[leftChild(upHeapPosition)]){
                            int* maxChildAddress = &heapArr[leftChild(upHeapPosition)];
                            swap(maxChildAddress, &heapArr[upHeapPosition]);
                            upHeapPosition = leftChild(upHeapPosition);
                            continue;
                        }
                    }
                    break;
                }
                if(heapArr[leftChild(upHeapPosition)] < heapArr[rightChild(upHeapPosition)]) {
                    if(heapArr[upHeapPosition] > heapArr[leftChild(upHeapPosition)]){
                        int* maxChildAddress = &heapArr[leftChild(upHeapPosition)];
                        swap(maxChildAddress, &heapArr[upHeapPosition]);
                        upHeapPosition = leftChild(upHeapPosition);
                        continue;
                    }
                    break;
                }
                else {
                    if(heapArr[upHeapPosition] > heapArr[rightChild(upHeapPosition)]){
                        int* maxChildAddress = &heapArr[rightChild(upHeapPosition)];
                        swap(maxChildAddress, &heapArr[upHeapPosition]);
                        upHeapPosition = rightChild(upHeapPosition);
                        continue;
                    }
                    break;
                }
            }
        }
        start = sortedArr;
        end = &sortedArr[staticsize];
        Sorting<T>::printArray(start,end);
    }
    
};
int main() {
    int arr[] ={-1,0,2,-5, 0, 1, 5, 6};
    Sorting<int>::heapSort(&arr[0], &arr[8]);
    return 0;
}
#endif /* SORTING_H */
