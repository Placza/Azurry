#ifndef CANVAS_H
#define CANVAS_H

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

void canvas_drag_begin (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void canvas_drag_update (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void canvas_drag_end (GtkGestureDrag *gesture, double x, double y, GtkWidget *area);

void canvas_draw_brush (GtkWidget *widget, double x, double y);

void canvas_draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data);

void canvas_resize_callback (GtkWidget *widget, int width, int height, gpointer data);

void canvas_set_brush_tool (GtkButton *button, gpointer user_data);

void canvas_set_eraser_tool(GtkButton *button, gpointer user_data);

void canvas_clear_surface(GtkButton *button, gpointer user_data);

#endif