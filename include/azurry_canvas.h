#ifndef AZURRY_CANVAS_H
#define AZURRY_CANVAS_H

#include <gtk/gtk.h>
#include "azurry_tools.h"

typedef struct {
    Azurry_tool *tool;
    GtkWidget *drawing_area;
    cairo_surface_t *surface;
    int current_tool;
} Azurry_canvas;

Azurry_canvas* azurry_canvas_create (GtkWidget *drawing_area, Azurry_tool *tool);

void azurry_canvas_draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data);

void azurry_canvas_resize_callback (GtkWidget *widget, int width, int height, gpointer data);

void azurry_canvas_realize_callback (GtkWidget *widget, gpointer data);

void azurry_canvas_destroy (Azurry_canvas *canvas);

#endif