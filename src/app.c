#include <gtk/gtk.h>
#include "../include/azurry_tools.h"
#include "../include/azurry_canvas.h"
#include "../include/azurry_listener.h"

void switch_to_brush (GtkButton *btn, gpointer *tool) {
    Azurry_brush_tool *brush_tool = (Azurry_brush_tool*) tool;
    azurry_brush_tool_use (brush_tool);
}

void switch_to_eraser (GtkButton *btn, gpointer *tool) {
    Azurry_brush_tool *eraser_tool = (Azurry_brush_tool*) tool;
    azurry_brush_tool_use (eraser_tool);
}

void app_activate (GApplication *app, gpointer *user_data) {
    GtkBuilder *builder;
    GtkWidget *win;
    GtkWidget *drawing_area;
    GtkWidget *brush_button;
    GtkWidget *eraser_button;
    GtkWidget *clear_button;

    Azurry_tool *tool = azurry_tool_create ();
	Azurry_brush_tool *brush_tool = azurry_brush_tool_create (tool, 10.0, 0, 0, 0);
    Azurry_brush_tool *erase_tool = azurry_brush_tool_create (tool, 20.0, 255, 255, 255);

    builder = gtk_builder_new_from_file ("../data/ui/main_menu.ui");
    win = GTK_WIDGET (gtk_builder_get_object (builder, "win"));
    gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
    drawing_area = GTK_WIDGET (gtk_builder_get_object (builder, "drawing_area"));
    brush_button = GTK_WIDGET (gtk_builder_get_object (builder, "brush_button"));
    eraser_button = GTK_WIDGET (gtk_builder_get_object (builder, "eraser_button"));
    clear_button = GTK_WIDGET (gtk_builder_get_object (builder, "clear_button"));

    g_signal_connect (brush_button, "clicked", G_CALLBACK (switch_to_brush), brush_tool);
    g_signal_connect (eraser_button, "clicked", G_CALLBACK (switch_to_eraser), erase_tool);

	azurry_brush_tool_use (brush_tool);

	Azurry_canvas *canvas = azurry_canvas_create (drawing_area, tool);

	Azurry_listener *listener = azurry_listener_create (canvas, tool);
	Azurry_drag_listener *drag_listener = azurry_drag_listener_create (listener);
	azurry_drag_listener_use (drag_listener);
	azurry_listener_use(listener);

	gtk_window_set_child (GTK_WINDOW (win), drawing_area);
    gtk_window_present (GTK_WINDOW (win));
}