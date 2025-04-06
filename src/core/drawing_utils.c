#include <gtk/gtk.h>
#include "drawing_utils.h"

cairo_surface_t *surface = NULL;
double start_x = 0.0, start_y = 0.0;
double line_start_x = 0.0, line_start_y = 0.0;
double line_width = 1.0;

void draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data) {
	/*
	* Sets the public surface variable as the main surface to draw on in the
	* Gtk drawing area
	*/
	cairo_set_source_surface (cairo, surface, 0, 0);
	cairo_paint (cairo);
}

//defines how drawing on the surface should work
//currently the standard way is to draw lines when the mouse is moving
void draw_brush (GtkWidget *widget, double x, double y) {
	cairo_t *drawing_surface;
	drawing_surface = cairo_create (surface);

	cairo_move_to (drawing_surface, line_start_x, line_start_y);
	//cairo_line_to (drawing_surface, x, y);
	cairo_set_line_width (drawing_surface, line_width);
	cairo_curve_to (drawing_surface, line_start_x, line_start_y, (line_start_x + x) / 2, (line_start_y + y) / 2, x, y);
	cairo_stroke (drawing_surface);

	//reset line position
	line_start_x = x;
	line_start_y = y;

	cairo_move_to (drawing_surface, x, y);

	cairo_destroy (drawing_surface);

	gtk_widget_queue_draw (widget);
}

//function for handling begining of a draging motion
void drag_begin (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	start_x = x;
	start_y = y;
	line_start_x = x;
	line_start_y = y;
	draw_brush (area, x, y);
} 

//handles the ongoing draging motion
void drag_update (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	draw_brush (area, start_x + x, start_y + y);
}

//handles when the draging has stopped
void drag_end (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	draw_brush (area, start_x + x, start_y + y);
}
