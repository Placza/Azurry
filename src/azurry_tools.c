#include <gtk/gtk.h>
#include "../include/azurry_tools.h"

static void azurry_pointer_tool_apply (void *self, cairo_surface_t *surface, double x, double y);

static void azurry_brush_tool_apply (void *self, cairo_surface_t *surface, double x, double y);

/*constructor for the tool class*/
Azurry_tool* azurry_tool_create () {
    Azurry_tool *tool = (Azurry_tool*) malloc (sizeof (Azurry_tool));
    tool->child = NULL;
    tool->apply = NULL;
    return tool;
}

/*
  function to call when we want to use a tool
  after we pick a tool, we can apply it directly ba calling this function
*/
void azurry_tool_use (Azurry_tool *self, cairo_surface_t *surface, double x, double y) {
    if (self->apply != NULL)
        self->apply(self->child, surface, x, y);
    else g_printerr ("Specific tool function not defined.");
}

void azurry_tool_destroy (Azurry_tool *tool) {
    free (tool->child);
    free (tool);
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
    free (self->parent->child);
    free (self->parent->apply);
    self->parent->child = self;
    self->parent->apply = azurry_pointer_tool_apply;
}

/*pointer tool's usage function - what to perfomr when active*/
static void azurry_pointer_tool_apply (void *self, cairo_surface_t *surface, double x, double y) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) self;
    g_print ("Using pointer %d\n", pointer_tool->size);
}

void azurry_pointer_tool_destroy (Azurry_pointer_tool *pointer_tool) {
    free (pointer_tool);
}

Azurry_brush_tool *azurry_brush_tool_create (Azurry_tool *parent, double size, int r, int g, int b) {
    Azurry_brush_tool *brush_tool = (Azurry_brush_tool*) malloc (sizeof (Azurry_brush_tool));
    brush_tool->parent = parent;
    brush_tool->size = size;
    brush_tool->r = r;
    brush_tool->g = g;
    brush_tool->b = b;
    return brush_tool;
}

void azurry_brush_tool_use (Azurry_brush_tool *self) {
    self->parent->child = self;
    self->parent->apply = azurry_brush_tool_apply;
}

static void azurry_brush_tool_apply (void *self, cairo_surface_t *surface, double x, double y) {
    Azurry_brush_tool *brush_tool = (Azurry_brush_tool*) self;

    cairo_t *cairo = cairo_create (surface);
    cairo_set_source_rgb (cairo, brush_tool->r, brush_tool->g, brush_tool->g);
    cairo_rectangle (cairo, x, y, brush_tool->size, brush_tool->size);
    cairo_fill (cairo);

    cairo_destroy (cairo);
}

void azurry_brush_tool_destroy (Azurry_brush_tool *brush_tool) {
    free (brush_tool);
}

