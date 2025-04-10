#include <gtk/gtk.h>
#include "../include/azurry_tools.h"

/*constructor for the tool class*/
Azurry_tool* azurry_tool_create () {
    Azurry_tool *tool = (Azurry_tool*) malloc (sizeof (Azurry_tool));
    tool->appy = NULL;
    return tool;
}

/*constructor for the pointer tool class*/
Azurry_pointer_tool *azurry_pointer_tool_create (Azurry_tool *parent, int size) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) malloc (sizeof (Azurry_pointer_tool));
    pointer_tool->parent = parent;
    pointer_tool->size = size;
    return pointer_tool;
}

/*
  initializes the pointer tool's parent's function to its usage function
  used for when we want to switch between tools
*/
void azurry_pointer_tool_use (Azurry_pointer_tool *self) {
    self->parent->appy = azurry_pointer_tool_apply;
}

/*pointer tool's usage function - what to perfomr when active*/
void azurry_pointer_tool_apply (void *self, cairo_surface_t *cairo, int x, int y) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) self;
    g_print ("Using pointer %d\n", pointer_tool->size);
}

/*
  function to call when we want to use a tool
  after we pick a tool, we can apply it directly ba calling this function
*/
void azurry_tool_use (Azurry_tool *self, void *tool, cairo_surface_t *cairo, int x, int y) {
    self->appy(tool, cairo, x, y);
}