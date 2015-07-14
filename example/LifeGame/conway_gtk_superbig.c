#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <gtk/gtk.h>
#define T(x,y) ((x)*Y+(y))
const char setx[8] = { 0, 0,-1,-1,-1, 1, 1, 1},		//方向数组
      sety[8] = { 1,-1,-1, 0, 1,-1, 0, 1};
int X = 1300 * 16,Y = 700 * 16,px = 1300,py = 700;
unsigned char *a,*b,*screen;

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

	g_print("surface\n");
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
	g_print("start1\n");
	g_print("%d\n",surface);
	if (surface == NULL)
		return FALSE;
	g_print("start2\n");
	unsigned char *pc;
	unsigned int i,j,k,x,y,c;
	double t;
	cairo_t *cr = cairo_create (surface);
	bzero(screen,px * py * sizeof(unsigned char));
	if(times == 10000)			//过多次数后，重新开始
	{
		times = 0;
		for(i = 0;i < X;i++)
			for(j = 0;j < Y;j+=32)
			{
				c = rand() % 2;
				for(k = 0;k < 32;k++)
				{
					a[T(i,j + k)] = c & 1;
					screen[(i >> 4) * py + ((j + k)>> 4)] += c & 1;
					c >>= 1;
				}
			}
	}
	else
	{
		for(i = 0;i < X;i++)
		{
			//g_print("\r%d",i);
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
				screen[(i >> 4) * py + (j >> 4)] += a[T(i,j)];
			}	
		}
	}
	for(i = 0;i < px;i++)
		for(j = 0;j < py;j++)
		{
			t = 1 - screen[i * py + j] / 512.0;
			cairo_set_source_rgb (cr,t,t,t);
			cairo_rectangle (cr, i, j, 1, 1);	//格子之间留一像素的空间
			cairo_fill (cr);
		}
	gtk_widget_queue_draw (widget);			//要求重绘
	cairo_destroy (cr);


	pc = a;						//交换a b
	a = b;
	b = pc;

	times++;

	g_print("end\n");
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
	free(screen);

	gtk_main_quit ();
}

	int
main (int   argc,
		char *argv[])
{
	a = (unsigned char*) malloc (sizeof(unsigned char) * X * Y);
	b = (unsigned char*) malloc (sizeof(unsigned char) * X * Y);		
	screen = (unsigned char*) malloc (sizeof(unsigned char) * px * py);		
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
	gtk_widget_set_size_request (da, px, py);

	gtk_container_add (GTK_CONTAINER (frame), da);

	g_signal_connect (da, "draw",
			G_CALLBACK (draw_cb), NULL);
	g_signal_connect (da,"configure-event",
			G_CALLBACK (configure_event_cb), NULL);

	//g_signal_connect (window, "check-resize", G_CALLBACK (run), NULL);	//试图修复调整大小时的空白问题

	run(da);
	g_timeout_add(30000,(GSourceFunc)run,da);

	gtk_widget_set_events (da, gtk_widget_get_events (da)
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
