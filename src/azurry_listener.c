#include <gtk/gtk.h>
#include "../include/azurry_listener.h"
#include "../include/azurry_canvas.h"

Azurry_listener *azurry_listener_create (Azurry_canvas *canvas, Azurry_tool *tool) {
    Azurry_listener *listener = (Azurry_listener*) malloc (sizeof (Azurry_listener));
    listener->child = NULL;
    listener->on_event = NULL;
    listener->canvas = canvas;
    listener->tool = tool;
    return listener;
}

void azurry_listener_trigger (Azurry_listener *self) {
    if (self->on_event != NULL)
        self->on_event ();
    else g_printerr ("Specific listener function not defined.");
}

void azurry_listener_delete (Azurry_listener *listener) {
    free (listener->child);
    free (listener);
}

Azurry_drag_listener *azurry_drag_listener_create (Azurry_listener *parent) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) malloc (sizeof (Azurry_drag_listener));
    drag_listener->parent = parent;
    drag_listener->start_x = 0;
    drag_listener->start_y = 0;
    drag_listener->drag = gtk_gesture_drag_new ();
    gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (drag_listener->drag), GDK_BUTTON_PRIMARY);
	gtk_widget_add_controller (parent->canvas->drawing_area, GTK_EVENT_CONTROLLER (drag_listener->drag));
    g_signal_connect (drag_listener->drag, "drag-begin", G_CALLBACK (azurry_drag_listener_drag_begin), drag_listener);
	g_signal_connect (drag_listener->drag, "drag-update", G_CALLBACK (azurry_drag_listener_drag_update), drag_listener);
	g_signal_connect (drag_listener->drag, "drag-end", G_CALLBACK (azurry_drag_listener_drag_end), drag_listener);
    return drag_listener;
}

void azurry_drag_listener_drag_begin (GtkGestureDrag *gesture, double x, double y, gpointer data) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) data;
    drag_listener->start_x = x;
    drag_listener->start_y = y;
    azurry_tool_use (drag_listener->parent->tool, drag_listener->parent->canvas->surface, x, y);
    gtk_widget_queue_draw(drag_listener->parent->canvas->drawing_area);
}

void azurry_drag_listener_drag_update (GtkGestureDrag *gesture, double x, double y, gpointer data) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) data;
    azurry_tool_use (drag_listener->parent->tool, drag_listener->parent->canvas->surface, drag_listener->start_x + x, drag_listener->start_y + y);
    gtk_widget_queue_draw(drag_listener->parent->canvas->drawing_area);
}

void azurry_drag_listener_drag_end (GtkGestureDrag *gesture, double x, double y, gpointer data) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) data;
    azurry_tool_use (drag_listener->parent->tool, drag_listener->parent->canvas->surface, drag_listener->start_x + x, drag_listener->start_y + y);
    gtk_widget_queue_draw(drag_listener->parent->canvas->drawing_area);
}

void azurry_drag_listener_destroy (Azurry_drag_listener *drag_listener) {
    free (drag_listener);
}
