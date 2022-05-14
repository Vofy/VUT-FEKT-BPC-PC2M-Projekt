#include <stdlib.h>
#include <stdbool.h>
#include "calculations.h"

void simple_moving_avg (double *arr, double *result, int length, int width, bool center)
{
    if( !(arr && length && width) ) return;

    // Tyto podmínky jsou důležité v případě vystředěného klouzavého průměru
    // v případě že se bude hledat střed v sudů šířce filtru
    const int before = center ? (width%2 ? (width-1)/2 : width/2  ) : width;
    const int after  = center ? (width%2 ? (width-1)/2 : width/2-1) : 0;

    // Doplnění neprůměrovaných hodnot
    for (int i = 0; i < before; i++)
        result[i] = arr[i];

    for (int i = 0; i < after; i++)
        result[length-i] = arr[length-i];


    for (int i = before; i < length-after; i++)
    {
        double sum = 0;
        for (int n = 0; n < width; n++)
            // Jednoduše odečtu počet čísel před indexem a postupně přičtu všechna čísla
            sum += arr[i+after-n];

        result[i] = sum / width;
    }
}

void weighted_moving_avg (double *arr, double *result, int length, int width, bool center)
{
    if( !(arr && length && width) ) return;

    const int before = center ? (width%2 ? (width-1)/2 : width/2  ) : width;
    const int after  = center ? (width%2 ? (width-1)/2 : width/2-1) : 0;

    for (int i = 0; i < before; i++)
        result[i] = arr[i];

    for (int i = 0; i < after; i++)
        result[length-i] = arr[length-i];

    const int weight_sum = triangular_number(width);

    for (int i = before; i < length-after; i++)
    {
        double sum = 0;
        for (int n = 0; n < width; n++)
            sum += arr[i+after-n] * (width-n);

        result[i] = sum / weight_sum;
    }
}

void exponencial_moving_avg (double *arr, double *result, int length, int width, bool center)
{
    if( !(arr && length && width) ) return;

    double *sma = malloc(length * sizeof(double));

    simple_moving_avg (arr, sma, length, width, center);

    const int before = center ? (width%2 ? (width-1)/2 : width/2  ) : width;
    const int after  = center ? (width%2 ? (width-1)/2 : width/2-1) : 0;

    for (int i = 0; i < before; i++)
        result[i] = arr[i];

    for (int i = 0; i < after; i++)
        result[length-i] = arr[length-i];

    for (int i = before; i < length-after; i++)
    {
        double sum = 0;
        for (int n = 0; n < width; n++)
        {
            int index = i+after-n;
            double k = 2 / (width+1);

            sum += arr[index] * k + sma[index] * (1-k);
        }

        result[i] = sum / width;
    }

    free(sma);
}

void moving_median (double *arr, double *result, int length, int width, bool center)
{
    if( !(arr && length && width) ) return;

    const int before = center ? (width%2 ? (width+1)/2 : width/2  ) : width;
    const int after  = center ? (width%2 ? (width+1)/2 : width/2-1) : 0;

    for (int i = 0; i < before; i++)
        result[i] = arr[i];

    for (int i = 0; i < after; i++)
        result[length-i] = arr[length-i];

    double *temp_arr = malloc(width * sizeof(double));

    for (int i = before; i < length-after; i++)
    {
        for (int n = 0; n < width; n++)
            temp_arr[n] = arr[i+after-n];

        result[i] = median(temp_arr, width);
    }
}
