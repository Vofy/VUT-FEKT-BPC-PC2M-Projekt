#ifndef ANALYSIS_H_INCLUDED
#define ANALYSIS_H_INCLUDED

#include <stdbool.h>

void simple_moving_avg      (double *arr, double *result, int length, int width, bool center);
void weighted_moving_avg    (double *arr, double *result, int length, int width, bool center);
void exponencial_moving_avg (double *arr, double *result, int length, int width, bool center);
void moving_median          (double *arr, double *result, int length, int width, bool center);

#endif // ANALYSIS_H_INCLUDED
