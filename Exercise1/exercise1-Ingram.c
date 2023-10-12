#include <stdio.h>
#include <stdlib.h>

double average(double sales[], int length) {
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += sales[i];
    }
    double average = sum / length;
    return average;
}

double findmax(double sales[], int length) {
    double max = sales[0];
    for (int i = 1; i < length; i++) {
        if (sales[i] > max) {
            max = sales[i];
        }
    }
    return max;
}

double findmin(double sales[], int length) {
    double min = sales[0];
    for (int i = 1; i < length; i++) {
        if (sales[i] < min) {
            min = sales[i];
        }
    }
    return min;
}

double* slicedarray(double array[], int start, int end) {
    int length = end - start + 1;
    double* subarray = (double*)malloc(length * sizeof(double));

    if (subarray == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        subarray[i] = array[start + i];
    }

    return subarray;
}

struct MonthValue {
    char* month;
    double value;
};

int compareDescending(const void *a, const void *b) {
    return (*(struct MonthValue*)b).value - (*(struct MonthValue*)a).value;
}

int main() {
    int width = 12;
    double sales[] = {23458.01, 40112.00, 56011.85, 37820.88, 37904.67, 60200.22, 72400.31, 56210.89, 67230.84, 68233.12, 80950.34, 95225.22};
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    printf("Monthly Sales Report for 2022: \n\n");
    printf("Month          Sales\n\n");

    for (int i = 0; i < 12; i++) {
        double n = sales[i];
        char *j = months[i];
        printf("%-*s $%*.2lf\n", width, j, width, n);
    }

    printf("\nSales Summary: \n\n");
    double n_min = findmin(sales, 12);
    double j_max = findmax(sales, 12);
    double k_avg = average(sales, 12);
    printf("Minimum Sales: %.2f\n", n_min);
    printf("Maximum Sales: .2f\n", j_max);
    printf("Average Sales: %.2f\n\n");

    double* firstlist = slicedarray(sales, 0, 5);
    double n_firstlist = average(firstlist, 6);
    double* secondlist = slicedarray(sales, 1, 6);
    double n_secondlist = average(secondlist, 6);
    double* thirdlist = slicedarray(sales, 2, 7);
    double n_thirdlist = average(thirdlist, 6);
    double* fourthlist = slicedarray(sales, 3, 8);
    double n_fourthlist = average(fourthlist, 6);
    double* fifthlist = slicedarray(sales, 4, 9);
    double n_fifthlist = average(fifthlist, 6);
    double* sixthlist = slicedarray(sales, 5, 10);
    double n_sixthlist = average(sixthlist, 6);
    double* seventhlist = slicedarray(sales, 6, 11);
    double n_seventhlist = average(seventhlist, 6);

    printf("Six-Month Moving Average Report: \n\n");
    printf("%-12s -   %-12s $%20.2f\n", "January", "June", n_firstlist);
    printf("%-12s -   %-12s $%20.2f\n", "February", "July", n_secondlist);
    printf("%-12s -   %-12s $%20.2f\n", "March", "August", n_thirdlist);
    printf("%-12s -   %-12s $%20.2f\n", "April", "September", n_fourthlist);
    printf("%-12s -   %-12s $%20.2f\n", "May", "October", n_fifthlist);
    printf("%-12s -   %-12s $%20.2f\n", "June", "November", n_sixthlist);
    printf("%-12s -   %-12s $%20.2f\n", "July", "December", n_seventhlist);

    printf("\nSales Report (Highest to Lowest):\n\n");
    printf("Month          Sales\n\n");

    int length = sizeof(months) / sizeof(months[0]);

    // Create an array of MonthValue structs to map months to values
    struct MonthValue monthValueMap[length];

    for (int i = 0; i < length; i++) {
        monthValueMap[i].month = months[i];
        monthValueMap[i].value = sales[i];
    }

    // Sort the mapping based on values in descending order
    qsort(monthValueMap, length, sizeof(struct MonthValue), compareDescending);

    // Print the sorted values and their associated months
    for (int i = 0; i < length; i++) {
        printf("%-12s $%.2f\n", monthValueMap[i].month, monthValueMap[i].value);
    }
    
    return 0;
}

