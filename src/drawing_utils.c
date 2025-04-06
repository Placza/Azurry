#include <gtk/gtk.h>
#include <math.h>
#include "../include/drawing_utils.h"
#include <gtk-4.0/gtk/gtknative.h>
#include <gtk-4.0/gtk/gtkwidget.h>

cairo_surface_t *surface = NULL;
double start_x = 0.0, start_y = 0.0;
double line_start_x, line_start_y;
double line_middle_x, line_middle_y;
double line_width = 1.0;
double velocity;

//manages window resizing - happens at the start of the application
void resize_callback (GtkWidget *widget, int width, int height, gpointer data) {
	//if a surface exists, destroy it
	if (surface) {
		cairo_surface_destroy (surface);
		surface = NULL;
	}
	//if a surface doesn't exist, then create a new one
	if (gtk_native_get_surface (gtk_widget_get_native (widget))) {
		surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
											  gtk_widget_get_width (widget), 
											  gtk_widget_get_height (widget));
		
		//create a new cairo object and color it white
		cairo_t *cairo;
		cairo = cairo_create (surface);

		cairo_set_source_rgb (cairo, 255, 255, 255);
		cairo_paint (cairo);
		cairo_destroy (cairo); 
	}
}

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
	cairo_set_line_width (drawing_surface, line_width + velocity * 0.2);
	cairo_curve_to (drawing_surface, line_start_x, line_start_y, line_middle_x, line_middle_y, x, y);
	cairo_stroke (drawing_surface);

	//reset line position
	velocity = sqrt (pow ((x - line_start_x), 2) + pow ((y - line_start_y), 2));
	g_print ("%f\n", velocity);
    
	line_start_x = line_middle_x;
	line_start_y = line_middle_y;
    
    line_middle_x = x;
    line_middle_y = y;

	cairo_move_to (drawing_surface, x, y);

	cairo_destroy (drawing_surface);

	gtk_widget_queue_draw (widget);
}

//function for handling begining of a draging motion
void drag_begin (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	start_x = x;
	start_y = y;
    line_middle_x = x;
    line_middle_y = y;
	line_start_x = x;
	line_start_y = y;
	velocity = 0;
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
