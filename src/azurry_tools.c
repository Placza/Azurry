#include <gtk/gtk.h>
#include "../include/azurry_tools.h"

Azurry_tool* azurry_tool_create () {
    Azurry_tool *tool = (Azurry_tool*) malloc (sizeof (Azurry_tool));
    tool->appy = NULL;
    return tool;
}

Azurry_pointer_tool *azurry_pointer_tool_create (Azurry_tool *parent, int size) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) malloc (sizeof (Azurry_pointer_tool));
    pointer_tool->parent = parent;
    pointer_tool->size = size;
    return pointer_tool;
}

void azurry_pointer_tool_use (Azurry_pointer_tool *self) {
    self->parent->appy = azurry_pointer_tool_apply;
}

void azurry_pointer_tool_apply (void *self, cairo_surface_t *cairo, int x, int y) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) self;
    g_print ("Using pointer %d\n", pointer_tool->size);
}

void azurry_tool_use (Azurry_tool *self, void *tool, cairo_surface_t *cairo, int x, int y) {
    self->appy(tool, cairo, x, y);
}