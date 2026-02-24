#include <stdio.h>

int find_elements(int *a, int n1, int *b, int n2, int *c) {
    int count = 0;
    int *q; // Pointer for traversing through a and b
    int *p; //Pointer for checking if element is already in c

    //1. Traverse through each element in array a and add it to c
    for (q = a; q < a + n1; q++) {
        //c is the address of the first element in c, so we can use pointer arithmetic to add elements to c
        *(c + count++) = *q; // Add element from a to c
    }

    //2. Traverse through each element in array b and add it to c if it's not already in c
    for (q = b; q < b + n2; q++) {
        int found = 0; // Flag to check if element is already in c
        //Check if element from b (*q) is already in c
        for (p = c; p < c + count; p++) {
            if (*p == *q) { // If element from b is found in c, set found flag and break
                found = 1;
                break;
            }
        } 
        if (!found) { // If element from b is not found in c, add it to c
            *(c + count++) = *q; // Add element from b to c
        }
    }
    return count; // Return the number of unique elements in c
    
                
}


int main(void) {
    int n1, n2;
    // Ask user for size of first array
    printf("Enter the length of first array: ");  
    scanf("%d", &n1);
    int a[n1]; // Declare first array   
    // Read elements of first array
    printf("Enter elements in the first array: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &a[i]);
    }
    // Ask user for size of second array
    printf("Enter the length of second array: ");
    scanf("%d", &n2);
    int b[n2]; // Declare second array
    // Read elements of second array
    printf("Enter elements in the second array: ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &b[i]);
    }
    // Call the function to find unique elements
    int c[n1 + n2]; // Declare third array
    int total_elements = find_elements(a, n1, b, n2, c);
    // Print the unique elements
    printf("Output: ");
    for (int i = 0; i < total_elements; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
}