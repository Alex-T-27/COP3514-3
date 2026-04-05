//Thien An Tran - U85205230

#include <stdio.h>
#include <string.h>
 
struct customer {
    char email[101];
    int purchases;
    char name[101];
};
 
int search(struct customer list[], int n, int num, struct customer result[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (list[i].purchases > num) {
            result[count] = list[i];
            count++;
        }
    }
    return count;
}
 
int main() {
    struct customer list[1000];
    struct customer result[1000];
    int n = 0;
    int num;
 
    FILE *infile = fopen("customers.csv", "r");
    if (infile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
 
    while (fscanf(infile, "%[^,],%d,%[^\n]\n", list[n].email, &list[n].purchases, list[n].name) == 3) {
        n++;
    }
    fclose(infile);
 
    printf("Enter number of purchases: ");
    scanf("%d", &num);
 
    int resultCount = search(list, n, num, result);
 
    FILE *outfile = fopen("result.csv", "w");
    if (outfile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }
 
    for (int i = 0; i < resultCount; i++) {
        fprintf(outfile, "%s,%d,%s\n", result[i].email, result[i].purchases, result[i].name);
    }
    fclose(outfile);
 
    printf("Output file name: result.csv\n");
 
    return 0;
}