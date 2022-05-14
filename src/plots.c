#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "../lib/gnuplot_i/src/gnuplot_i.h"

struct gnuplot_session_node *STACK_TOP = NULL;

struct gnuplot_session_node
{
    gnuplot_ctrl* h;
    struct gnuplot_session_node* prev;
};

gnuplot_ctrl *get_gnuplot_session ()
{
    struct gnuplot_session_node *session = malloc(sizeof(struct gnuplot_session_node));

    session->prev = STACK_TOP;
    session->h = gnuplot_init();

    STACK_TOP = session;

    return session->h;
}

int close_top_gnuplot_session ()
{
    gnuplot_close(STACK_TOP->h);
    struct gnuplot_session_node *STACK_TOP_PREV = STACK_TOP->prev;

    free(STACK_TOP);
    STACK_TOP = STACK_TOP_PREV;

    return STACK_TOP_PREV != NULL ? 1 : 0;
}

void close_all_gnuplot_sessions ()
{
    while(close_top_gnuplot_session());
}

void plot_value1 (dataset_t *dataset, bool output_to_file)
{
    gnuplot_ctrl* h = get_gnuplot_session ();

    if(output_to_file)
    {
        gnuplot_cmd(h, "set terminal eps");
        gnuplot_cmd(h, "set output \"output/plots/plot1.eps\"") ;
    }

    gnuplot_set_xlabel(h, "Čas [s]");
    gnuplot_set_ylabel(h, "Hodnota 1 [j]");

    gnuplot_setstyle(h, "lines");

    gnuplot_plot_xy(h, dataset->relative_time, dataset->value1, dataset->length, "Skutečná hodnota 1");

    if(dataset->value2_modified != NULL)
        gnuplot_plot_xy(h, dataset->relative_time, dataset->value1_modified, dataset->length, "Filtrovaná hodnota 1");

    if(output_to_file)
    {
        gnuplot_cmd(h, "unset output");
        close_top_gnuplot_session ();
    }
}

void plot_value2 (dataset_t *dataset, bool output_to_file)
{
    gnuplot_ctrl* h = get_gnuplot_session ();

    if(output_to_file)
    {
        gnuplot_cmd(h, "set terminal eps");
        gnuplot_cmd(h, "set output \"output/plots/plot2.eps\"") ;
    }

    gnuplot_set_xlabel(h, "Čas [s]");
    gnuplot_set_ylabel(h, "Hodnota 2 [j]");

    gnuplot_setstyle(h, "dots");

    gnuplot_plot_xy(h, dataset->relative_time, dataset->value2, dataset->length, "Skutečná hodnota 2");

    if(dataset->value2_modified != NULL)
        gnuplot_plot_xy(h, dataset->relative_time, dataset->value2_modified, dataset->length, "Filtrovaná hodnota 2");

    if(output_to_file)
    {
        gnuplot_cmd(h, "unset output");
        close_top_gnuplot_session ();
    }
}

void plot_value3 (dataset_t *dataset, bool output_to_file)
{
    gnuplot_ctrl* h = get_gnuplot_session ();

    if(output_to_file)
    {
        gnuplot_cmd(h, "set terminal eps");
        gnuplot_cmd(h, "set output \"output/plots/plot3.eps\"") ;
    }

    gnuplot_set_xlabel(h, "Čas [s]");
    gnuplot_set_ylabel(h, "Hodnota 3 [j]");

    gnuplot_setstyle(h, "lines");

    gnuplot_plot_xy(h, dataset->relative_time, dataset->value3, dataset->length, "Skutečná hodnota 3");

    if(dataset->value3_modified != NULL)
        gnuplot_plot_xy(h, dataset->relative_time, dataset->value3_modified, dataset->length, "Filtrovaná hodnota 3");

    if(output_to_file)
    {
        gnuplot_cmd(h, "unset output");
        close_top_gnuplot_session ();
    }
}

void plot_value3_distribution(dataset_t *dataset, bool output_to_file)
{
    gnuplot_ctrl* h = get_gnuplot_session ();

    if(output_to_file)
    {
        gnuplot_cmd(h, "set terminal eps");
        gnuplot_cmd(h, "set output \"output/plots/plot3_value_distribution.eps\"") ;
    }

    gnuplot_set_xlabel(h, "Výskyt");
    gnuplot_set_ylabel(h, "Hodnota");

    gnuplot_setstyle(h, "lines");

    if(dataset->value3_sorted != NULL)
        gnuplot_plot_x(h, dataset->value3_sorted, dataset->length, "Distribuce hodnoty 3");

    if(output_to_file)
    {
        gnuplot_cmd(h, "unset output");
        close_top_gnuplot_session ();
    }
}
