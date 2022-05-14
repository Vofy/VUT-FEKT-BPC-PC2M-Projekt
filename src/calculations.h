#ifndef CALCULATIONS_H_INCLUDED
#define CALCULATIONS_H_INCLUDED

#include "types.h"

void   sort_array         (double *arr, int length);
double datetime_to_seconds(datetime_t* relative_time);
int    triangular_number  (int number);
double mean               (double* arr, int length);
double median             (double* arr, int length);
double variance           (double* arr, int length);
double standard_deviation (double* arr, int length);
double integral           (double* arr, int length, double a, double b);

#endif // CALCULATIONS_H_INCLUDED
