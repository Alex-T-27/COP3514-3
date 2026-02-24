#include <stdio.h>

void compute(int *a1, int n1, int *a2, int n2);

int main(void) {
    int n1, n2;
    printf("Enter the length of the array: ");
    scanf("%d", &n1);
    int a1[n1];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &a1[i]);
    }
    n2 = (n1 + 1) / 2; // Size of second array is half of first array
    int a2[n2]; // Declare second array

    //Call the function to compute the sums of pairs of elements in a1 and store them in a2
    compute(a1, n1, a2, n2);
    //Print the elements of a2
    printf("Output: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", a2[i]);
    }


}

void compute(int *a1, int n1, int *a2, int n2) {
    //Use two pointers to traverse through a1
    int *left = a1; // Left pointer 
    int *right = a1 + n1 - 1; // Right pointer
    int *p = a2; // Pointer for traversing through a2
    while (left < right) { // While left pointer is less than right pointer and p is within bounds of a2
        *p++ = *left + *right; // Calculate sum of elements at left and right pointers and store it in a2, then move p to the next position
        left++; // Move left pointer forward
        right--; // Move right pointer backward
    }
        if (left == right) {
            * p = *left; // If left and right pointers point to the same element, store that element in a2
        }
    }
