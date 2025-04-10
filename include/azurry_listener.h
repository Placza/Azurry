#ifndef AZURRY_LISTENER_H
#define AZURRY_LISTENER_H

#include <gtk/gtk.h>
#include "azurry_canvas.h"
#include "azurry_tools.h"

typedef struct {
    void *child;
    void (*on_event) ();
    Azurry_canvas *canvas;
    Azurry_tool *tool;
} Azurry_listener;

typedef struct {
    Azurry_listener *parent;
    GtkGesture *drag;
    double start_x, start_y;
} Azurry_drag_listener;

Azurry_listener *azurry_listener_create (Azurry_canvas *canvas, Azurry_tool *tool);

void azurry_listener_trigger (Azurry_listener *self);

void azurry_listener_destroy (Azurry_listener *listener);

Azurry_drag_listener *azurry_drag_listener_create (Azurry_listener *parent);

void azurry_drag_listener_drag_begin (GtkGestureDrag *gesture, double x, double y, gpointer data);

void azurry_drag_listener_drag_update (GtkGestureDrag *gesture, double x, double y, gpointer data);

void azurry_drag_listener_drag_end (GtkGestureDrag *gesture, double x, double y, gpointer data);

void azurry_drag_listener_destroy (Azurry_drag_listener *drag_listener);

#endif