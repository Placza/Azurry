#include <gtk/gtk.h>
#include "../include/azurry_tools.h"
#include "../include/azurry_canvas.h"
#include "../include/azurry_listener.h"

void app_activate (GApplication *app, gpointer *user_data) {
	/*
	* GObject -- GApplication -- GtkApplication
	* <---parent                      child--->
	*/

	GtkWidget *win;
	GtkWidget *drawing_area;

	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_default_size (GTK_WINDOW (win), 1000, 800);
	gtk_window_present (GTK_WINDOW (win));

	drawing_area = gtk_drawing_area_new ();

	Azurry_tool *tool = azurry_tool_create ();
	Azurry_brush_tool *brush_tool = azurry_brush_tool_create (tool, 10.0, 0, 0, 0);
	azurry_brush_tool_use (brush_tool);

	Azurry_canvas *canvas = azurry_canvas_create (drawing_area, tool);

	Azurry_listener *listener = azurry_listener_create (canvas, tool);
	Azurry_drag_listener *drag_listener = azurry_drag_listener_create (listener);
	azurry_drag_listener_use (drag_listener);
	azurry_listener_use(listener);

	gtk_window_set_child (GTK_WINDOW (win), drawing_area);
}