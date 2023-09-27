#include <stdio.h>

int linearSearch(int arr[], int size, int target) {
    
    for(int i = 0; i < size; i++)
        if (arr[i] == target)
            return i; // target found, position is returned.

    return -1; // Target not found
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 13;

    int index = linearSearch(arr, size, target);

    if (index != -1) {
        printf("Target %d found at index %d\n", target, index);
    } else {
        printf("Target %d not found in the array\n", target);
    }

    return 0;
}
