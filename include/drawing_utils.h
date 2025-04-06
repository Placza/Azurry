#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <gtk/gtk.h>

extern double line_width;
extern double velicoty;
extern cairo_surface_t *surface;
extern double start_x;
extern double start_y;
extern double line_start_x;
extern double line_start_y;
extern double line_middle_x;
extern double line_middle_y;

void drag_begin (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void drag_update (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void drag_end (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void draw_brush (GtkWidget *widget, double x, double y);

void draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data);

void resize_callback (GtkWidget *widget, int width, int height, gpointer data);

#endif