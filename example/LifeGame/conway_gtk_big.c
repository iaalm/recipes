#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <gtk/gtk.h>
#define T(x,y) ((x)*Y+(y))
const char setx[8] = { 0, 0,-1,-1,-1, 1, 1, 1},		//方向数组
      sety[8] = { 1,-1,-1, 0, 1,-1, 0, 1};
int X = 1300,Y = 700;
char *a,*b;

static cairo_surface_t *surface = NULL;

	static void
clear_surface (void)					//清理
{
	cairo_t *cr;

	cr = cairo_create (surface);

	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);

	cairo_destroy (cr);
}

	static gboolean
configure_event_cb (GtkWidget         *widget,		//初始化
		GdkEventConfigure *event,
		gpointer           data)
{
	if (surface)
		cairo_surface_destroy (surface);

	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
			CAIRO_CONTENT_COLOR,
			gtk_widget_get_allocated_width (widget),
			gtk_widget_get_allocated_height (widget));

	clear_surface ();

	return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
//系统要求重绘的事件
	static gboolean
draw_cb (GtkWidget *widget,
		cairo_t   *cr,
		gpointer   data)
{
	cairo_set_source_surface (cr, surface, 0, 0);
	cairo_paint (cr);

	return FALSE;
}

gint run(GtkWidget *widget)
{
	static int times = 10000; 
	if (surface == NULL)
		return FALSE;
	char *pc;
	int i,j,k,x,y,c;
	cairo_t *cr = cairo_create (surface);
	if(times == 10000)			//过多次数后，重新开始
	{
		times = 0;
		for(i = 0;i < X;i++)
			for(j = 0;j < Y;j++)
			{
				a[T(i,j)] = rand() % 2;
				cairo_set_source_rgb (cr, 1 - a[T(i,j)], 1 - a[T(i,j)], 1 - a[T(i,j)]);
				cairo_rectangle (cr, i, j, 1, 1);	//格子之间留一像素的空间
				cairo_fill (cr);
			}
	}
	else
	{
		for(i = 0;i < X;i++)
			for(j = 0;j < Y;j++)
			{
				c = 0;
				for(k = 0;k < 8;k++)
				{
					x = setx[k] + i;
					y = sety[k] + j;
					if(x >= 0 && x < X && y >= 0 && y< Y && b[T(x,y)])
						c++;
				}
				if(c < 2 || c > 3)
					a[T(i,j)] = 0;
				else if(c == 3)
					a[T(i,j)] = 1;
				else
					a[T(i,j)] = b[T(i,j)];
				cairo_set_source_rgb (cr, 1 - a[T(i,j)], 1 - a[T(i,j)], 1 - a[T(i,j)]);
				cairo_rectangle (cr, i, j, 1, 1);	//格子之间留一像素的空间
				cairo_fill (cr);
			}	
	}
	gtk_widget_queue_draw (widget);			//要求重绘
	cairo_destroy (cr);


	pc = a;						//交换a b
	a = b;
	b = pc;

	times++;

	return TRUE;
}

//退出
	static void
close_window (void)
{
	if (surface)
		cairo_surface_destroy (surface);
	free(a);
	free(b);

	gtk_main_quit ();
}

	int
main (int   argc,
		char *argv[])
{
	a = (char*) malloc (sizeof(char) * X * Y);
	b = (char*) malloc (sizeof(char) * X * Y);		
	srand((unsigned) time(0));
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *da;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Conway's Lifegame");

	g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

	gtk_container_set_border_width (GTK_CONTAINER (window), 8);

	frame = gtk_frame_new (NULL);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
	gtk_container_add (GTK_CONTAINER (window), frame);

	da = gtk_drawing_area_new ();
	gtk_widget_set_size_request (da, X, Y);

	gtk_container_add (GTK_CONTAINER (frame), da);

	g_signal_connect (da, "draw",
			G_CALLBACK (draw_cb), NULL);
	g_signal_connect (da,"configure-event",
			G_CALLBACK (configure_event_cb), NULL);

	//g_signal_connect (window, "check-resize", G_CALLBACK (run), NULL);	//试图修复调整大小时的空白问题

	run(da);
	g_timeout_add(1000,(GSourceFunc)run,da);

	gtk_widget_set_events (da, gtk_widget_get_events (da)
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
