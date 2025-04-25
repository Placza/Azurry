#include <gtk/gtk.h>
#include "../include/app.h"
#define APPLICATION_ID "com.github.Placza.Azurry"

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
