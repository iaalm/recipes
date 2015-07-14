#include<gtk/gtk.h>
//G_MODULE_EXPORT  并不是必须的
void
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
	GtkWidget *windows;
	windows = gtk_builder_get_object (builder,"window1");
	gtk_builder_connect_signals(builder,NULL);
	gtk_widget_show_all (windows);
	gtk_main();
	return 0;
}
