#include <stdio.h>

int fact(int x, int arr[], int arr_size){
    int c = 0;
    for (int i=0; i < arr_size; i++){
        int p = arr[i] * x + c;
        arr[i] = p % 10;
        c = p/10;
    }
    while (c){
        arr[arr_size] = c%10;
        c = c/10;
        arr_size++;
    }
    return arr_size;
}

char* factorial(int n){
    int *arr = (int *) malloc(1000000 * sizeof(int));
    char *result = (char *) malloc(1000000 * sizeof(char));
    arr[0] = 1;
    int arr_size = 1;
    for (int x=2; x<=n; x++)
        arr_size = fact(x, arr, arr_size);
    int j = 0;
    for (int i=arr_size-1; i>=0; i--){
        result[j] = arr[i] + '0';
        j++;
    }
    return result;
}
