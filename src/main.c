#include <gtk/gtk.h>
#include "../include/canvas.h"
#include "../include/azurry_canvas.h"
#include "../include/azurry_tools.h"
#define APPLICATION_ID "com.github.Placza.Azurry"

static void app_activate (GApplication *app, gpointer *user_data) {
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

	Azurry_canvas *canvas = azurry_canvas_create (drawing_area);

	Azurry_tool *tool = azurry_tool_create (canvas);

	Azurry_pointer_tool *pointer_tool = azurry_pointer_tool_create (tool, 20);

	Azurry_brush_tool *brush_tool = azurry_brush_tool_create (tool, 10.0, 0, 0, 0);

	azurry_brush_tool_use (brush_tool);

	azurry_tool_use (tool, 0, 0);

	gtk_window_set_child (GTK_WINDOW (win), drawing_area);

	/*GtkBuilder *build;
	GtkWidget *win;
	GtkWidget *drawing_area;
	GtkWidget *brush_button;
	GtkWidget *eraser_button;
	GtkWidget *clear_button;
	GtkGesture *drag;

	build = gtk_builder_new_from_file ("../data/ui/main_menu.ui");

	win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
	gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
	
	//creates a drawing area
	drawing_area = GTK_WIDGET (gtk_builder_get_object (build, "drawing_area"));
	gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area),
									canvas_draw_callback, NULL, NULL);
	g_signal_connect_after (drawing_area, "resize", G_CALLBACK (canvas_resize_callback), NULL);

	//initializes the drag object
	drag = gtk_gesture_drag_new ();
	gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (drag), GDK_BUTTON_PRIMARY);
	gtk_widget_add_controller (drawing_area, GTK_EVENT_CONTROLLER (drag));
	g_signal_connect (drag, "drag-begin", G_CALLBACK (canvas_drag_begin), drawing_area);
	g_signal_connect (drag, "drag-update", G_CALLBACK (canvas_drag_update), drawing_area);
	g_signal_connect (drag, "drag-end", G_CALLBACK (canvas_drag_end), drawing_area);

	brush_button = GTK_WIDGET (gtk_builder_get_object (build, "brush_tool"));
	g_signal_connect (brush_button, "clicked", G_CALLBACK (canvas_set_brush_tool), NULL);

	eraser_button = GTK_WIDGET (gtk_builder_get_object (build, "eraser_tool"));
	g_signal_connect (eraser_button, "clicked", G_CALLBACK (canvas_set_eraser_tool), NULL);

	clear_button = GTK_WIDGET (gtk_builder_get_object (build, "clear_tool"));
	g_signal_connect (clear_button, "clicked", G_CALLBACK (canvas_clear_surface), drawing_area);


	//draws the window
	gtk_window_present (GTK_WINDOW (win));*/
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int stat;

	//creates a GTK application
	app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
	//maps the signal sent when application is created to the app_activate function
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	//runs the application
	stat = g_application_run (G_APPLICATION (app), argc, argv);
	//kills the application
	g_object_unref (app);

	return stat;
}
