#ifndef AZURRY_TOOLS_H
#define AZURRY_TOOLS_H

#include <gtk/gtk.h>
#include "azurry_canvas.h"

typedef struct {
    Azurry_canvas *canvas;
    void *child;
    void (*apply) (void *child, int x, int y);
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

/*Azurry  tool*/
Azurry_tool* azurry_tool_create (Azurry_canvas *canvas);

void azurry_tool_use (Azurry_tool *self, int x, int y);

void azurry_tool_destroy (Azurry_tool *tool);

/*Azurry pointer tool*/
Azurry_pointer_tool* azurry_pointer_tool_create (Azurry_tool *parent, int size);

void azurry_pointer_tool_use (Azurry_pointer_tool *self);

void azurry_pointer_tool_destroy (Azurry_pointer_tool *pointer_tool);

/*Azurry brush tool*/
Azurry_brush_tool* azurry_brush_tool_create (Azurry_tool *parent, double size, int r, int g, int b);

void azurry_brush_tool_use (Azurry_brush_tool *self);

void azurry_brush_tool_destroy (Azurry_brush_tool *brush_tool);

/*Azurry eraser tool*/
Azurry_pointer_tool* azurry_eraser_tool_create (Azurry_tool *parent, double size);

#endif

