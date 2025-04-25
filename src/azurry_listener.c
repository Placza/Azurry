#include <gtk/gtk.h>
#include "../include/azurry_listener.h"
#include "../include/azurry_canvas.h"

/*
  Works the same way the tool class works - refer the azurry_tools.c file.
  
  Has the same patern:
  - azurry_<listener_type>_listener_apply(): defines the functionalities of all the different listeners.
  - azurry_<listener_type>_use(): sets the Azurry_listener object's child as the object that called that method
  - azurry_listener_use(): applies the Azurry_listener object's child's apply method
  - Azurry_listener class has the void (*apply) field that is the placeholder for its child's apply method
*/

static void azurry_drag_listener_apply (void *self);

/*
-----------------------------------------------------LISTENER----------------------------------------------------------
*/

/*listener constructor*/
Azurry_listener *azurry_listener_create (Azurry_canvas *canvas, Azurry_tool *tool) {
    Azurry_listener *listener = (Azurry_listener*) malloc (sizeof (Azurry_listener));
    listener->child = NULL;
    listener->apply = NULL;
    listener->canvas = canvas;
    listener->tool = tool;
    return listener;
}

/*sets up the child listener's gesture functions*/
void azurry_listener_use (Azurry_listener *self) {
    if (self->apply != NULL)
        self->apply (self->child);
    else g_printerr ("Specific listener function not defined.");
}

/*listener destructor*/
void azurry_listener_destroy (Azurry_listener *listener) {
    free (listener->child);
    free (listener);
}

/*
--------------------------------------------DRAG LISTENER--------------------------------------------------------------
*/

Azurry_drag_listener *azurry_drag_listener_create (Azurry_listener *parent) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) malloc (sizeof (Azurry_drag_listener));
    drag_listener->parent = parent;
    drag_listener->start_x = 0;
    drag_listener->start_y = 0;
    drag_listener->drag = gtk_gesture_drag_new ();
    return drag_listener;
}

void azurry_drag_listener_use (Azurry_drag_listener *self) {
    self->parent->child = self;
    self->parent->apply = azurry_drag_listener_apply;
}

void azurry_drag_listener_apply (void *self) {
    Azurry_drag_listener *drag_listener = (Azurry_drag_listener*) self;

    gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (drag_listener->drag), GDK_BUTTON_PRIMARY);
	gtk_widget_add_controller (drag_listener->parent->canvas->drawing_area, GTK_EVENT_CONTROLLER (drag_listener->drag));
    g_signal_connect (drag_listener->drag, "drag-begin", G_CALLBACK (azurry_drag_listener_drag_begin), drag_listener);
	g_signal_connect (drag_listener->drag, "drag-update", G_CALLBACK (azurry_drag_listener_drag_update), drag_listener);
	g_signal_connect (drag_listener->drag, "drag-end", G_CALLBACK (azurry_drag_listener_drag_end), drag_listener);
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
