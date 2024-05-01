#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUANTITY 16

typedef unsigned short Number;


unsigned short lower(const Number a, const Number b){
    return a < b;
}


void swap(Number *a, Number *b){
    Number c;
    c = *a;
    *a = *b;
    *b = c;
}

/*
void heap_sort(Number array[QUANTITY])  
{ 
    unsigned i, j, index;
    Number temp;
    
    
    for (i = 1; i < QUANTITY; i++)  
        if (lower(numbers[(i - 1) / 2], numbers[i]))
        { 
            j = i; 
            while (lower(numbers[(j - 1) / 2], numbers[j]))
            { 
                swap(&numbers[j], &numbers[(j - 1) / 2]); 
                j = (j - 1) / 2; 
            } 
        }
  
    for(i = QUANTITY - 1; i > 0; i--) 
    {
        swap(&numbers[0], &numbers[i]);
        j = 0; 
        do
        { 
            index = (2 * j + 1); 
            if ((index < (i - 1)) && lower(numbers[index], numbers[index + 1])) 
                index++; 
            if ((index < i) && lower(numbers[j], numbers[index])) 
                swap(&numbers[j], &numbers[index]); 
            j = index; 
        } while (index < i); 
    }
    
    for (i = 1; i < QUANTITY; i++) 
    {
        if (array[i] > array[(i - 1) / 2]) 
        { 
            j = i; 
            while (array[j] > array[(j - 1) / 2]) 
            {
                temp = array[j]; 
                array[j] = array[(j-1)/2]; 
                array[(j-1)/2] = temp; 
                j = (j - 1) / 2; 
            } 
        } 
    }
    for (i = QUANTITY - 1; i > 0; i--) 
    {
        temp = array[0]; 
        array[0] = array[i]; 
        array[i] = temp; 
        j = 0; 
        do
        { 
            index = (2 * j + 1); 
            if (array[index] < array[index + 1] && 
                                index < (i - 1)) 
                index++; 
            if (array[j] < array[index] && index < i) 
            { 
                temp = array[j]; 
                array[j] = array[index]; 
                array[index] = temp; 
            } 
            j = index; 
        } while (index < i); 
    } 
}
*/

void heapify(Number array[], int n, int i) 
{ 
    unsigned maximum, left_index, right_index; 
    Number temp;

    maximum = i; 
    right_index = 2 * i + 2; 
    left_index = 2 * i + 1; 
    if (left_index < n && array[left_index] > array[maximum]) 
        maximum = left_index; 
    if (right_index < n && array[right_index] > array[maximum]) 
        maximum = right_index; 
    if (maximum != i) { 
        temp = array[i]; 
        array[i] = array[maximum]; 
        array[maximum] = temp; 
        heapify(array, n, maximum); 
    } 
} 
  
void heap_sort(Number array[QUANTITY]) 
{ 
    unsigned i;
    Number temp;
    for (i = QUANTITY / 2 - 1; i >= 0; i--)
        heapify(array, QUANTITY, i); 
    for (i = QUANTITY - 1; i > 0; i--) { 
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0); 
    } 
} 

void generate_numbers(Number numbers[QUANTITY]){
    unsigned i;
    srand(time(0));
    for(i=0; i<QUANTITY; i++)
        numbers[i] = rand();
}

void print_numbers(Number numbers[QUANTITY]){
    unsigned i;
    for(i=0; i<QUANTITY; i++)
        printf("%hu ", numbers[i]);
}

int main(){
    Number numbers[QUANTITY];
    generate_numbers(numbers);
    printf("\n\n");
    print_numbers(numbers);
    printf("\n\n");
    heap_sort(numbers);
    print_numbers(numbers);
    printf("\n\n");
    return 0;
}