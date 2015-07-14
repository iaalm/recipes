#include<gtk/gtk.h>
	static void
print_hello(GtkWidget *widget,
		cairo_t *cr,
		gpointer   data)
{
	g_print ("Hello World\n");
}


int
main (int   argc,
      char *argv[])
{
	gtk_init (&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,"ctrl.ui",NULL);
	GObject *windows,*box[5],*drawarea,*entry[6];
	windows = gtk_builder_get_object (builder,"window1");
	drawarea = gtk_builder_get_object (builder,"drawingarea1");
	box[0] = gtk_builder_get_object (builder,"box1");
	box[1] = gtk_builder_get_object (builder,"box2");
	box[2] = gtk_builder_get_object (builder,"box3");
	box[3] = gtk_builder_get_object (builder,"box4");
	box[4] = gtk_builder_get_object (builder,"box5");
	entry[0] = gtk_builder_get_object (builder,"entry1");
	entry[1] = gtk_builder_get_object (builder,"entry2");
	entry[2] = gtk_builder_get_object (builder,"entry3");
	entry[3] = gtk_builder_get_object (builder,"entry4");
	entry[4] = gtk_builder_get_object (builder,"entry5");
	entry[5] = gtk_builder_get_object (builder,"entry6");
	g_signal_connect (windows, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (drawarea, "draw", G_CALLBACK (print_hello), NULL);

	gtk_widget_show_all (windows);
	gtk_main();
	return 0;
}
