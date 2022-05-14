#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../types.h"
#include "../plots.h"
#include "../dataio.h"
#include "../smoothing.h"
#include "../calculations.h"
#include "smoothing/moving_average_window.h"
#include "smoothing/moving_median_window.h"

extern dataset_t* dataset;
GtkBuilder* main_window_builder;

void main_window_show ()
{
    main_window_builder = gtk_builder_new_from_file ("src/ui/main_window.glade");
    gtk_builder_connect_signals (main_window_builder, NULL); // Napojí obslužné metody jednotlivých událostí na UI

    GObject* window = gtk_builder_get_object(main_window_builder, "main_window");
    gtk_widget_show(GTK_WIDGET(window));
}

void main_window_delete_event (GtkWidget* self, GdkEvent* event, gpointer user_data)
{
    gtk_widget_destroy (self);
    gtk_main_quit();

    close_all_gnuplot_sessions();
    free_all(dataset);
    free(dataset);
}

void set_label (char label[], char str[])
{
    GtkLabel* filename_label = GTK_LABEL(gtk_builder_get_object(main_window_builder, label));
    gtk_label_set_label(filename_label, str);
}

void widget_set_sensitive (char widget[], unsigned short int sensitive)
{
    GtkWidget* display_plot_button = GTK_WIDGET(gtk_builder_get_object(main_window_builder, widget));
    gtk_widget_set_sensitive(display_plot_button, sensitive);
}

void plot1_button_clicked ()
{
    plot_value1 (dataset, 0);
}
void plot2_button_clicked ()
{
    plot_value2 (dataset, 0);
}
void plot3_button_clicked ()
{
    plot_value3 (dataset, 0);
}
void analysis_value_distribution_button_activate ()
{
    plot_value3_distribution(dataset, 0);
}

void filter_moving_average_button_activate()
{
    smoothing_moving_average_window_show();
}

void filter_moving_median_button_activate()
{
    smoothing_moving_median_window_show();
}

void export_plots_button_activate()
{
    export_plots (dataset);
}

void export_generate_latex_button_activate()
{
    export_report_latex (dataset);
}

void export_generate_pdf_button_activate()
{
    export_report_pdf (dataset);
}

void show_open_file_dialog()
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new ("Otevřít soubor",
                        NULL,
                        GTK_FILE_CHOOSER_ACTION_OPEN,
                        "_Cancel", GTK_RESPONSE_CANCEL,
                        "_Open", GTK_RESPONSE_ACCEPT,
                        NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        dataset->filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        load_file(dataset, dataset->filename);

        set_label ("filename_label", dataset->filename);
        set_label ("entry_count_label", g_strdup_printf("%li", dataset->length));
        set_label ("elapsed_time_total_label", g_strdup_printf("%lf sekund", dataset->relative_time[dataset->length-1]));
        set_label ("mean_label", g_strdup_printf("%lf", mean (dataset->value3, dataset->length)));
        set_label ("median_label", g_strdup_printf("%lf", median (dataset->value3_sorted, dataset->length)));
        set_label ("variance_label", g_strdup_printf("%lf", variance (dataset->value3, dataset->length)));
        set_label ("standard_deviation_label", g_strdup_printf("%lf", standard_deviation (dataset->value3, dataset->length)));
        set_label ("integral_label", g_strdup_printf("%lf", integral (dataset->value3, dataset->length, 0, dataset->relative_time[dataset->length-1])));

        widget_set_sensitive ("plot1_button", 1);
        widget_set_sensitive ("plot2_button", 1);
        widget_set_sensitive ("plot3_button", 1);
        widget_set_sensitive ("toolbar_smooth_menuitem", 1);
        widget_set_sensitive ("toolbar_analysis_menuitem", 1);
        widget_set_sensitive ("toolbar_export_menuitem", 1);
    }

    gtk_widget_destroy (dialog);
}
