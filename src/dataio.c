#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <glib.h>
#include "types.h"
#include "plots.h"
#include "calculations.h"

#ifdef linux
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif // linux

int count_lines(char* filename)
{
    FILE *file = fopen(filename, "r");

    char buffer[128];
    int counter = 0;

    while (fgets(buffer, sizeof buffer, file))
    {
        if (*buffer == '#' || *buffer == '\n') continue; // Ignorování komentářů a prázdných řádků

        sscanf(buffer, "%*s");
        counter++;
    }

    fclose(file);

    return counter;
}

void on_load_sort (double *arr, double *sorted_arr, int length)
{
    memcpy(sorted_arr, arr, length * sizeof(double));
    sort_array(sorted_arr, length);
}

void free_all (dataset_t *dataset)
{
    free(dataset->relative_time);
    free(dataset->time);
    free(dataset->value1);
    free(dataset->value2);
    free(dataset->value3);
    free(dataset->value3_sorted);
    free(dataset->value1_modified);
    free(dataset->value2_modified);
    free(dataset->value3_modified);
}

void load_file(dataset_t* dataset, char filename[])
{
    dataset->length = count_lines(filename);

    free_all(dataset);

    dataset->relative_time   = malloc(dataset->length * sizeof(double));
    dataset->value1          = malloc(dataset->length * sizeof(int));
    dataset->value2          = malloc(dataset->length * sizeof(int));
    dataset->value3          = malloc(dataset->length * sizeof(double));
    dataset->value3_sorted   = malloc(dataset->length * sizeof(double));

    dataset->value1_modified = NULL;
    dataset->value2_modified = NULL;
    dataset->value3_modified = NULL;

    char buffer[128];
    int index = 0;

    double first_time = 0;
    datetime_t* datetime = malloc(sizeof(datetime_t));

    FILE *file = fopen(filename, "r");

    while (fgets(buffer, sizeof buffer, file))
    {
        if (*buffer == '#' || *buffer == '\n') continue; // Ignorování komentářů a prázdných řádků

        setlocale(LC_NUMERIC, "C"); // Nastaví LC_NUMERIC aby byl použit správný separátor desetinného čísla

        sscanf(buffer, "%d/%d/%d %d:%d:%lf %d %d %lf",
               &datetime->year, &datetime->month, &datetime->day,
               &datetime->hour, &datetime->minute, &datetime->second,
               &dataset->value1[index],
               &dataset->value2[index],
               &dataset->value3[index]);

        if (!first_time)
            first_time = datetime_to_seconds(datetime);

        dataset->relative_time[index++] = datetime_to_seconds(datetime) - first_time;
    }

    fclose(file);

    on_load_sort(dataset->value3, dataset->value3_sorted, dataset->length);
}

void check_output_path (char *path)
{
    struct stat st = {0};

    if (stat(path, &st) == -1)
        mkdir(path, 0755);
}

void export_plots (dataset_t *dataset)
{
    check_output_path("output/plots");
    bool OUTPUT_TO_FILE = true;

    plot_value1 (dataset, true);
    plot_value2 (dataset, true);
    plot_value3 (dataset, true);
    plot_value3_distribution(dataset, true);
}

void export_report_latex (dataset_t *dataset)
{
    check_output_path("output");
    export_plots(dataset);

    FILE *template_file = fopen("src/templates/latex.template", "r");

    if(template_file != NULL)
    {
        fseek(template_file, 0, SEEK_END);
        int fsize = (int)ftell(template_file);
        fseek(template_file, 0, SEEK_SET);

        char *latex_template = malloc((fsize) * sizeof(char));
        fread(latex_template, fsize, 1, template_file);
        latex_template[fsize] = '\0';

        fclose(template_file);

        FILE *output = fopen("output/report.tex", "w");

        if(output != NULL)
        {
            fprintf(output, latex_template,
                    dataset->filename,
                    dataset->length,
                    g_strdup_printf ("%li sekund", dataset->relative_time[dataset->length-1]),
                    mean (dataset->value3, dataset->length),
                    median (dataset->value3_sorted, dataset->length),
                    variance (dataset->value3, dataset->length),
                    standard_deviation (dataset->value3, dataset->length),
                    integral (dataset->value3, dataset->length, 0, dataset->relative_time[dataset->length-1]));

            fclose(output);
        }

        free(latex_template);
    }
}

void export_report_pdf (dataset_t *dataset)
{
    check_output_path("output");
    export_report_latex(dataset);
    system("cd output; pdflatex -interaction=nonstopmode report.tex");
}
