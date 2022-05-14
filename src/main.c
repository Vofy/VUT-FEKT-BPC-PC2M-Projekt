#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "types.h"
#include "ui/main_window.h"

// gnome-terminal --title=$TITLE -x
// `pkg-config --cflags --libs gtk4`
// `pkg-config --cflags --libs gtk+-3.0`

dataset_t* dataset = NULL;

int main (int argc, char **argv)
{
    dataset = malloc(sizeof(dataset_t));

    gtk_init(&argc, &argv);

    main_window_show();

    gtk_main();

    return 0;
}
