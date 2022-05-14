#ifndef PLOTS_H_INCLUDED
#define PLOTS_H_INCLUDED

#include <stdbool.h>

void plot_value1 (dataset_t *dataset, bool output_to_file);
void plot_value2 (dataset_t *dataset, bool output_to_file);
void plot_value3 (dataset_t *dataset, bool output_to_file);
void plot_value3_distribution(dataset_t *dataset, bool output_to_file);

#endif // PLOTS_H_INCLUDED
