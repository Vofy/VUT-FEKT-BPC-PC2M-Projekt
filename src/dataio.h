#ifndef DATASETIO_H_INCLUDED
#define DATASETIO_H_INCLUDED

#include "types.h"

void load_file (dataset_t* dataset, char* filename);
void free_all (dataset_t *dataset);
void export_modified_data_to_file(dataset_t* dataset, char* filename);
void export_plots (dataset_t *dataset);
void export_report_latex (dataset_t *dataset);
void export_report_pdf (dataset_t *dataset);

#endif // DATASETIO_H_INCLUDED
