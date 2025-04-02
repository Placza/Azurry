#include <gtk/gtk.h>
#define APPLICATION_ID "com.github.Placza.Azurry"

//A surface to store current drawings
static cairo_surface_t *surface = NULL;
static double start_x;
static double start_y;
static double line_start_x;
static double line_start_y;

//manages window resizing - happens at the start of the application
static void resize_callback (GtkWidget *widget, int width, int height, gpointer data) {
	//if a surface exists, destroy it
	if (surface) {
		cairo_surface_destroy (surface);
		surface = NULL;
	}
	//if a surface doesn't exist, then create a new one
	if (gtk_native_get_surface (gtk_widget_get_native (widget))) {
		surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
											  gtk_widget_get_width (widget), 
											  gtk_widget_get_height (widget));
		
		//create a new cairo object and color it white
		cairo_t *cairo;
		cairo = cairo_create (surface);

		cairo_set_source_rgb (cairo, 255, 255, 255);
		cairo_paint (cairo);
		cairo_destroy (cairo); 
	}
}

static void draw_callback (GtkDrawingArea *area, cairo_t *cairo, int width, int height, gpointer data) {
	/*
	* Sets the public surface variable as the main surface to draw on in the
	* Gtk drawing area
	*/
	cairo_set_source_surface (cairo, surface, 0, 0);
	cairo_paint (cairo);
}

//defines how drawing on the surface should work
//currently the standard way is to draw lines when the mouse is moving
static void draw_brush (GtkWidget *widget, double x, double y) {
	cairo_t *drawing_surface;
	drawing_surface = cairo_create (surface);

	cairo_move_to (drawing_surface, line_start_x, line_start_y);
	cairo_line_to (drawing_surface, x, y);
	cairo_stroke (drawing_surface);

	//reset line position
	line_start_x = x;
	line_start_y = y;

	cairo_move_to (drawing_surface, x, y);

	cairo_destroy (drawing_surface);

	gtk_widget_queue_draw (widget);
}

//function for handling begining of a draging motion
static void drag_begin (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	start_x = x;
	start_y = y;
	line_start_x = x;
	line_start_y = y;
	draw_brush (area, x, y);
} 

//handles the ongoing draging motion
static void drag_update (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	draw_brush (area, start_x + x, start_y + y);
}

//handles when the draging has stopped
static void drag_end (GtkGestureDrag *gesture, double x, double y, GtkWidget *area) {
	draw_brush (area, start_x + x, start_y + y);
}

static void app_activate (GApplication *app, gpointer *user_data) {
	/*
	* GObject -- GApplication -- GtkApplication
	* <---parent                      child--->
	*/

	GtkWidget *win;
	GtkWidget *drawing_area;
	GtkGesture *drag;

	//creates a GTK window
	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Azurry");
	gtk_window_set_default_size (GTK_WINDOW (win), 1000, 600);

	//creates a drawing area
	drawing_area = gtk_drawing_area_new ();
	gtk_widget_set_size_request (drawing_area, 100, 100);
	gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area),
									draw_callback, NULL, NULL);
	g_signal_connect_after (drawing_area, "resize", G_CALLBACK (resize_callback), NULL);
	gtk_window_set_child (GTK_WINDOW (win), drawing_area);


	//initializes the drag object
	drag = gtk_gesture_drag_new ();
	gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (drag), GDK_BUTTON_PRIMARY);
	gtk_widget_add_controller (drawing_area, GTK_EVENT_CONTROLLER (drag));
	g_signal_connect (drag, "drag-begin", G_CALLBACK (drag_begin), drawing_area);
	g_signal_connect (drag, "drag-update", G_CALLBACK (drag_update), drawing_area);
	g_signal_connect (drag, "drag-end", G_CALLBACK (drag_end), drawing_area);

	//draws the window
	gtk_window_present (GTK_WINDOW (win));
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int stat;

	//creates a GTK application
	app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
	//maps the signal sent when application is created to the app_activate function
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	//runs the application
	stat = g_application_run (G_APPLICATION (app), argc, argv);
	//kills the application
	g_object_unref (app);

	return stat;
}