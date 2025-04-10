#include <gtk/gtk.h>
#include "../include/azurry_canvas.h"

/*initializes the canvas*/
Azurry_canvas* azurry_canvas_create (GtkWidget *drawing_area, Azurry_tool *tool) {
    Azurry_canvas *canvas = (Azurry_canvas*) g_malloc (sizeof (Azurry_canvas));
    canvas->tool = tool;
    canvas->drawing_area = drawing_area;
    canvas->surface = NULL;
    canvas->current_tool = 0;
    gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (canvas->drawing_area), 
                                    azurry_canvas_draw_callback, canvas, NULL); //link a draw callback function
    g_signal_connect_after (canvas->drawing_area, "realize", G_CALLBACK (azurry_canvas_realize_callback), canvas); //link a realize callback function
    g_signal_connect_after (canvas->drawing_area, "resize", G_CALLBACK (azurry_canvas_resize_callback), canvas); //link a resize callback function
    return canvas;
}

/*
  function that is being called after the GtkDrawingArea gets initialized for the canvas class
  used to fill in the surface
*/
void azurry_canvas_draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data) {
    Azurry_canvas *canvas = (Azurry_canvas*) data;

    cairo_set_source_surface (cairo, canvas->surface, 0, 0);
    cairo_paint (cairo);
}

/*resize handling function that creates a new surface if one isn't created and destroys one if it already exists*/
void azurry_canvas_resize_callback (GtkWidget *widget, int width, int height, gpointer data) {
    Azurry_canvas *canvas = (Azurry_canvas*) data; //link the canvas surface

    //if a surface exists, destroy it
	if (canvas->surface) {
		cairo_surface_destroy (canvas->surface);
		canvas->surface = NULL;
	}
    //if a sruface doesn't exist, create a new one
	if (gtk_native_get_surface (gtk_widget_get_native (widget))) {
		canvas->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, gtk_widget_get_width (widget), gtk_widget_get_height (widget));
        cairo_t *cairo;
		cairo = cairo_create (canvas->surface);
        
        //paints the surface white
		cairo_set_source_rgb (cairo, 255, 255, 255);
		cairo_paint (cairo);
		cairo_destroy (cairo); 
	}
}

void azurry_canvas_realize_callback (GtkWidget *widget, gpointer data) {
    Azurry_canvas *canvas = (Azurry_canvas*) data;

    if (!canvas->surface) {
        canvas->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, gtk_widget_get_width (widget), gtk_widget_get_height (widget));
        cairo_t *cairo;
        cairo = cairo_create (canvas->surface);

        //paints the surface white
        cairo_set_source_rgb (cairo, 255, 255, 255);
        cairo_paint (cairo);
        cairo_destroy (cairo); 
    }
}

void azurry_canvas_destroy (Azurry_canvas *canvas) {
    if (canvas->surface) {
        cairo_surface_destroy (canvas->surface);
    }
    free (canvas);
}