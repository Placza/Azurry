#include <gtk/gtk.h>
#include "../include/azurry_tools.h"

static void azurry_pointer_tool_apply (void *self, int x, int y);

static void azurry_brush_tool_apply (void *self, int x, int y);

/*constructor for the tool class*/
Azurry_tool* azurry_tool_create (Azurry_canvas *canvas) {
    Azurry_tool *tool = (Azurry_tool*) malloc (sizeof (Azurry_tool));
    tool->canvas = canvas;
    tool->child = NULL;
    tool->apply = NULL;
    return tool;
}

/*
  function to call when we want to use a tool
  after we pick a tool, we can apply it directly ba calling this function
*/
void azurry_tool_use (Azurry_tool *self, int x, int y) {
    self->apply(self->child, x, y);
}

void azurry_tool_destroy (Azurry_tool *tool) {
    free (tool->child);
    free (tool->apply);
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
static void azurry_pointer_tool_apply (void *self, int x, int y) {
    Azurry_pointer_tool *pointer_tool = (Azurry_pointer_tool*) self;
    g_print ("Using pointer %d\n", pointer_tool->size);
}

void azurry_pointer_tool_destroy (Azurry_pointer_tool *pointer_tool) {
    free (pointer_tool->parent);
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
    free (self->parent->child);
    free (self->parent->apply);
    self->parent->child = self;
    self->parent->apply = azurry_brush_tool_apply;
}

static void azurry_brush_tool_apply (void *self, int x, int y) {
    Azurry_brush_tool *brush_tool = (Azurry_brush_tool*) self;

    g_print ("%p\n", brush_tool->parent->canvas->surface);

    cairo_t *cairo = cairo_create (brush_tool->parent->canvas->surface);
    cairo_set_source_rgb (cairo, brush_tool->r, brush_tool->g, brush_tool->b);
    cairo_set_line_width (cairo, brush_tool->size);
    cairo_rectangle (cairo, 100.0, 100.0, 300.0, 300.0);

    cairo_fill (cairo);
    cairo_destroy (cairo);

    gtk_widget_queue_draw (brush_tool->parent->canvas->drawing_area);
}

void azurry_brush_tool_destroy (Azurry_brush_tool *brush_tool) {
    free (brush_tool->parent);
    free (brush_tool);
}

