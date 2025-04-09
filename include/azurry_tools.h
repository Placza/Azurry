#ifndef AZURRY_TOOLS_H
#define AZURRY_TOOLS_H

#include <gtk/gtk.h>

typedef struct {
    void (*appy) (void *self, cairo_surface_t *cairo, int x, int y);
} Azurry_tool;

typedef struct {
    int size;
    Azurry_tool *parent;
} Azurry_pointer_tool;

typedef struct {
    Azurry_tool *parent;
    double size;
    int r, g, b;
} Azurry_brush_tool;

typedef struct {
    Azurry_tool *parent;
    double size;
} Azurry_eraser_tool;

Azurry_tool* azurry_tool_create ();

Azurry_pointer_tool* azurry_pointer_tool_create (Azurry_tool *parent, int size);

void azurry_pointer_tool_apply (void *self, cairo_surface_t *cairo, int x, int y);

void azurry_pointer_tool_use (Azurry_pointer_tool *self);

Azurry_pointer_tool* azurry_brush_tool_create (Azurry_tool *parent, double size, int r, int g, int b);

Azurry_pointer_tool* azurry_eraser_tool_create (Azurry_tool *parent, double size);

void azurry_tool_use (Azurry_tool *self, void *tool, cairo_surface_t *cairo, int x, int y);

#endif

