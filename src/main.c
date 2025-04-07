#include <gtk/gtk.h>
#include "../include/drawing_utils.h"
#define APPLICATION_ID "com.github.Placza.Azurry"

static void app_activate (GApplication *app, gpointer *user_data) {
	/*
	* GObject -- GApplication -- GtkApplication
	* <---parent                      child--->
	*/

	GtkBuilder *build;
	GtkWidget *win;
	GtkWidget *drawing_area;
	GtkGesture *drag;

	build = gtk_builder_new_from_file ("../data/ui/main_menu.ui");

	win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
	gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
	
	//creates a drawing area
	drawing_area = GTK_WIDGET (gtk_builder_get_object (build, "drawing_area"));
	gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area),
									draw_callback, NULL, NULL);
	g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_callback), NULL);

	
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
