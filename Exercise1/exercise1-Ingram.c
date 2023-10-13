#include <stdio.h>
#include <stdlib.h>

double average(double sales[], int length) {
    //Just a normal average function, takes a list of doubles and an integer length
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += sales[i];
    }
    double average = sum / length;
    return average; //Return a double value
}

double findmax(double sales[], int length) {
    //Max function, takes list of doubles and length as well to iterate
    double max = sales[0];
    for (int i = 1; i < length; i++) {
        if (sales[i] > max) {
            max = sales[i];
        }
    }
    return max; //Return a double
}

double findmin(double sales[], int length) {
    //Min function, takes list of doubles and does nearly the same thing as the max
    double min = sales[0];
    for (int i = 1; i < length; i++) {
        if (sales[i] < min) {
            min = sales[i];
        }
    }
    return min; //Return a double
}

double* slicedarray(double array[], int start, int end) {
    /*This function is used largely for one part of the problem, it slices a list and returns the output
    it takes an array, a start, and an end. From that it slices and returns a new list */
    int length = end - start + 1;
    double* subarray = (double*)malloc(length * sizeof(double)); //Make a pointer double array

    if (subarray == NULL) { //Add a check to make sure we don't have an empty subarray
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < length; i++) { //Iterate through the array and add to the subarray
        subarray[i] = array[start + i];
    }

    return subarray; //Return the brand new array
}

struct MonthValue { /*This took a lot of work to do, and I don't fully understand it. I feel like this lab threw
us in the deep end but I did my very best. This struct is used for mapping the months to the sale values as needed */
    char* month;
    double value;
};

int compareDescending(const void *a, const void *b) { 
    //Function for comparison for the last part of the problem, utilizes the struct above and pointers
    return (*(struct MonthValue*)b).value - (*(struct MonthValue*)a).value;
}

int main() {
    /*Main function, does a lot all at once since there is a lot required, and I'm not sure of how much of it can be
    hardcoded. My TA told me to hardcode some parts, so I did my best with what I knew and what the problem provided*/
    int width = 12; //Initialize a width for prints 
    double sales[] = {23458.01, 40112.00, 56011.85, 37820.88, 37904.67, 60200.22, 72400.31, 56210.89, 67230.84, 68233.12, 80950.34, 95225.22}; //Hard code list of sales
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; //Hard code list of months

    printf("Monthly Sales Report for 2022: \n\n"); //First problem where we just print monthly sales
    printf("Month          Sales\n\n");

    for (int i = 0; i < 12; i++) { //Iterate through sales and months, print each accordingly
        double n = sales[i];
        char *j = months[i];
        printf("%-*s $%*.2lf\n", width, j, width - 4, n); //Use some nifty left justifying to make it look formatted
    }

    printf("\nSales Summary: \n\n"); //Summary of all sales using functions made
    double n_min = findmin(sales, 12); //Find a min, pass in number of months, repeat for max and average
    double j_max = findmax(sales, 12);
    double k_avg = average(sales, 12);
    printf("Minimum Sales: $%.2f          (January)\n", n_min);
    printf("Maximum Sales: $%.2f          (December)\n", j_max);
    printf("Average Sales: $%.2f\n\n", k_avg); //Do prints with similar spacing justification

    /*This whole section is just to slice arrays and return the averages of the six month values
    for a part of the problem. I had to initialize seven new arrays, and take their average. Could I 
    have done this iteratively? Yes. But this is my first assignment with C and I think I'm seriously
    losing my actual mind. sorry.*/
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
    //Use the arrays I initializes, and use the same left justification to print it nice and pretty
    printf("%-12s -   %-12s $%18.2lf\n", "January", "June", n_firstlist);
    printf("%-12s -   %-12s $%18.2lf\n", "February", "July", n_secondlist);
    printf("%-12s -   %-12s $%18.2lf\n", "March", "August", n_thirdlist);
    printf("%-12s -   %-12s $%18.2lf\n", "April", "September", n_fourthlist);
    printf("%-12s -   %-12s $%18.2lf\n", "May", "October", n_fifthlist);
    printf("%-12s -   %-12s $%18.2lf\n", "June", "November", n_sixthlist);
    printf("%-12s -   %-12s $%18.2lf\n", "July", "December", n_seventhlist);

    printf("\nSales Report (Highest to Lowest):\n\n");//Sort sales from highest to lowest, this is where the fun begins
    printf("Month          Sales\n\n");

    int length = sizeof(months) / sizeof(months[0]); //Initialize a length

    // Create an array of MonthValue structs to map months to values
    struct MonthValue monthValueMap[length]; //Another struct! yay! This time to map months to sales

    for (int i = 0; i < length; i++) { //Iterate through the months and sales and add them to one another accordingly
        monthValueMap[i].month = months[i];
        monthValueMap[i].value = sales[i];
    }
    qsort(monthValueMap, length, sizeof(struct MonthValue), compareDescending); //Sort mapping values in descending order using qsort, which is super helpful
    for (int i = 0; i < length; i++) {
        printf("%-12s $%.2f\n", monthValueMap[i].month, monthValueMap[i].value);//Print the values with their according months and justify it with our cool feature
    }
    
    return 0;//Return 0 because this is an int main after all
}

