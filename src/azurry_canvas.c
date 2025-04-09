#include <gtk/gtk.h>
#include "../include/azurry_canvas.h"

Azurry_canvas* azurry_canvas_create (GtkWidget *drawing_area) {
    Azurry_canvas *canvas = (Azurry_canvas*) g_malloc (sizeof (Azurry_canvas));
    canvas->drawing_area = drawing_area;
    gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area), 
                                    azurry_canvas_draw_callback, canvas, NULL);
    g_signal_connect_after (drawing_area, "resize", G_CALLBACK (azurry_canvas_resize_callback), canvas);
    canvas->surface = NULL;
    canvas->current_tool = 0;
    return canvas;
}

void azurry_canvas_draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data) {
    Azurry_canvas *canvas = (Azurry_canvas*) data;
    g_print("Drawing with current tool: %d\n", canvas->current_tool);

    cairo_set_source_surface (cairo, canvas->surface, 0, 0);
	cairo_paint (cairo);
}

void azurry_canvas_resize_callback (GtkWidget *widget, int width, int height, gpointer data) {
    Azurry_canvas *canvas = (Azurry_canvas*) data; 

	if (canvas->surface) {
		cairo_surface_destroy (canvas->surface);
		canvas->surface = NULL;
	}
	if (gtk_native_get_surface (gtk_widget_get_native (widget))) {
		canvas->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
											  gtk_widget_get_width (widget), 
											  gtk_widget_get_height (widget));
		
		cairo_t *cairo;
		cairo = cairo_create (canvas->surface);

		cairo_set_source_rgb (cairo, 255, 255, 255);
		cairo_paint (cairo);
		cairo_destroy (cairo); 
	}
}