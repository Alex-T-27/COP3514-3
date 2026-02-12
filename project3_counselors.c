#include <stdio.h>
#include <stdlib.h>

/*
 * Comparison function for qsort.
 * Sorts integers in ascending order.
 */
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/*
 * Finds the missing counselor number.
 * The array must be sorted.
 * n = size of the array (which is total counselors - 1).
 */
int search(int counselors[], int n) {

    // If the first counselor number is not 1,
    // then 1 must be the missing number.
    if (counselors[0] != 1)
        return 1;

    // Check for a gap between consecutive numbers.
    // Since one number is missing, there will be
    // a place where the difference is greater than 1.
    for (int i = 0; i < n - 1; i++) {
        if (counselors[i + 1] != counselors[i] + 1) {
            return counselors[i] + 1;  // Return the missing number
        }
    }

    // If no gap was found, then the missing number
    // must be the last number (n + 1).
    return n + 1;
}

int main(void) {
    int n;

    // Ask user for total number of counselors (including the missing one)
    printf("Enter number of counselors: ");
    scanf("%d", &n);

    // Create an array of size n-1 since one counselor is missing
    int assigned_counselors[n - 1];

    // Read the assigned counselor numbers
    printf("Enter counselors assigned: ");
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &assigned_counselors[i]);
    }

    // Sort the array so we can detect the missing gap easily
    qsort(assigned_counselors, n - 1, sizeof(int), compare);

    // Call search function to find missing counselor
    int missing = search(assigned_counselors, n - 1);

    // Print result
    if (missing != -1)
        printf("Counselor has not been assigned: %d\n", missing);
    else
        printf("No missing counselor found.\n");

    return 0;
}
