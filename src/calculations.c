#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "types.h"

int cmpfunc (const void * a, const void * b)
{
    // Dereferencování přetypovaného ukazatele :-D (pěkné, že)
    return (*(double*)a - *(double*)b);
}

void sort_array(double *arr, int length)
{
    qsort(arr, length, sizeof(double), cmpfunc);
}

double datetime_to_seconds(datetime_t* relative_time)
{
    return
        relative_time->year   * 31556952 +
        relative_time->month  * 2629746 +
        relative_time->day    * 86400 +
        relative_time->hour   * 3600 +
        relative_time->minute * 60 +
        relative_time->second;
}

int triangular_number(int number)
{
    int result = 0;

    for (int i = 1; i <= number; i++)
        result += i;

    return result;
}

// Průměr
double mean (double* arr, int length)
{
    double sum = 0;

    for (int i = 0; i < length; i++)
        sum += arr[i];

    return sum / length;
}

// Střední hodnota
double median(double* arr, int length)
{
    double median_value;

    if(length%2) // Počet je lichý
        median_value = arr[(length-1)/2 + 1];
    else         // Počet je sudý
        median_value = (arr[length/2] + arr[length/2+1]) / 2;

    return median_value;
}

// Rozptyl
double variance (double* arr, int length)
{
    double mean_value = mean(arr, length);

    double sum = 0;
    for (int i = 0; i < length; i++)
        sum += pow(arr[i] - mean_value, 2);

    return sum / (double)length;
}

// Směrodatná odchylka
double standard_deviation (double* arr, int length)
{
    return sqrt(variance(arr, length));
}

double integral (double* arr, int length, double a, double b)
{
    double sum = 0;

    for (int i = 1; i < length - 1; i++)
        sum += arr[i];

    sum *= 2, sum += arr[0] + arr[length-1];

    return 0.5 * ((b-a)/(double)length) * sum;
}
