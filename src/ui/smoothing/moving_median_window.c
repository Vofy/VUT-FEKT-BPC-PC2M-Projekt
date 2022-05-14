#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../../smoothing.h"
#include "../../types.h"

extern dataset_t* dataset;
GtkBuilder* mooving_median_window_builder;

void smoothing_moving_median_window_show()
{
    mooving_median_window_builder = gtk_builder_new_from_file ("src/ui/smoothing/moving_median_window.glade");
    gtk_builder_connect_signals (mooving_median_window_builder, NULL); // Napojí obslužné metody jednotlivých událostí na UI

    GObject* window = gtk_builder_get_object(mooving_median_window_builder, "moving_median_window");
    gtk_widget_show(GTK_WIDGET(window));
}

void moving_median_window_smooth_button_activate(GtkWidget *widget, gpointer user_data)
{
    GtkComboBox *value_combobox = GTK_COMBO_BOX(gtk_builder_get_object(mooving_median_window_builder, "value_combobox"));
    int value_combobox_index = (int)gtk_combo_box_get_active (GTK_COMBO_BOX(value_combobox));

    GtkEntry *width_spinbutton = GTK_ENTRY(gtk_builder_get_object(mooving_median_window_builder, "width_spinbutton"));
    double filter_width = atof (gtk_entry_get_text(width_spinbutton));

    GtkComboBox *align_combobox = GTK_COMBO_BOX(gtk_builder_get_object(mooving_median_window_builder, "align_combobox"));
    int moving_avg_align_combobox_index = (int)gtk_combo_box_get_active (GTK_COMBO_BOX(align_combobox));

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

    moving_median(src, dest, dataset->length, filter_width, center);

    gtk_window_close(widget);
}
