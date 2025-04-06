#include <gtk/gtk.h>
#include "../include/drawing_utils.h"
#define APPLICATION_ID "com.github.Placza.Azurry"

static void app_activate (GApplication *app, gpointer *user_data) {
	/*
	* GObject -- GApplication -- GtkApplication
	* <---parent                      child--->
	*/

	GtkWidget *win;
	GtkWidget *drawing_area;
	GtkGesture *drag;

	//creates a GTK window
	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Azurry");
	gtk_window_set_default_size (GTK_WINDOW (win), 1000, 600);

	//creates a drawing area
	drawing_area = gtk_drawing_area_new ();
	gtk_widget_set_size_request (drawing_area, 100, 100);
	gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area),
									draw_callback, NULL, NULL);
	g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_callback), NULL);
	gtk_window_set_child (GTK_WINDOW (win), drawing_area);


	//initializes the drag object
	drag = gtk_gesture_drag_new ();
	gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (drag), GDK_BUTTON_PRIMARY);
	gtk_widget_add_controller (drawing_area, GTK_EVENT_CONTROLLER (drag));
	g_signal_connect (drag, "drag-begin", G_CALLBACK (drag_begin), drawing_area);
	g_signal_connect (drag, "drag-update", G_CALLBACK (drag_update), drawing_area);
	g_signal_connect (drag, "drag-end", G_CALLBACK (drag_end), drawing_area);

	//draws the window
	gtk_window_present (GTK_WINDOW (win));
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
