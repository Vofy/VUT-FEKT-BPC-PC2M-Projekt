#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../../smoothing.h"
#include "../../types.h"

extern dataset_t* dataset;
GtkBuilder* smoothing_builder;

void smoothing_moving_average_window_show()
{
    smoothing_builder = gtk_builder_new_from_file ("src/ui/smoothing/moving_average_window.glade");
    gtk_builder_connect_signals (smoothing_builder, NULL); // Napojí obslužné metody jednotlivých událostí na UI

    GObject* window = gtk_builder_get_object(smoothing_builder, "moving_average_window");
    gtk_widget_show(GTK_WIDGET(window));
}

void mooving_average_window_smooth_button_activate(GtkWidget *widget, gpointer user_data)
{
    GtkEntry *filter_width_spinbutton = GTK_ENTRY(gtk_builder_get_object(smoothing_builder, "filter_width_spinbutton"));
    double filter_width = atof (gtk_entry_get_text(filter_width_spinbutton));

    GtkComboBox *value_combobox = GTK_COMBO_BOX(gtk_builder_get_object(smoothing_builder, "value_combobox"));
    int value_combobox_index = (int)gtk_combo_box_get_active (GTK_COMBO_BOX(value_combobox));

    GtkComboBox *moving_avg_type_combobox = GTK_COMBO_BOX(gtk_builder_get_object(smoothing_builder, "moving_avg_type_combobox"));
    int moving_avg_type_combobox_index = (int)gtk_combo_box_get_active (GTK_COMBO_BOX(moving_avg_type_combobox));

    GtkComboBox *moving_avg_align_combobox = GTK_COMBO_BOX(gtk_builder_get_object(smoothing_builder, "moving_avg_align_combobox"));
    int moving_avg_align_combobox_index = (int)gtk_combo_box_get_active (GTK_COMBO_BOX(moving_avg_align_combobox));

    double *src, *dest;

    switch(value_combobox_index)
    {
        case 0:
            // Funkce moving_avg nejsou implementovany pro int
            /*if(dataset->value1_modified == NULL)
                dataset->value1_modified = malloc(dataset->length * sizeof(int));

            src = dataset->value1, dest = dataset->value1_modified;*/
            break;
        case 1:
            // Funkce moving_avg nejsou implementovany pro int
            /*(dataset->value2_modified == NULL)
                dataset->value2_modified = malloc(dataset->length * sizeof(int));

            src = dataset->value2, dest = dataset->value2_modified;*/
            break;
        case 2:
            // Alokace paměti, pokud není alokovaná
            if(dataset->value3_modified == NULL)
                dataset->value3_modified = malloc(dataset->length * sizeof(double));

            src = dataset->value3, dest = dataset->value3_modified;
            break;
    }

    bool center = moving_avg_align_combobox_index;

    switch(moving_avg_type_combobox_index)
    {
        case 0: simple_moving_avg      (src, dest, dataset->length, filter_width, center); break;
        case 1: weighted_moving_avg    (src, dest, dataset->length, filter_width, center); break;
        case 2: exponencial_moving_avg (src, dest, dataset->length, filter_width, center); break;
    }

    gtk_window_close(widget);
}
