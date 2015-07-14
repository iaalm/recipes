#include <gtk/gtk.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#define PORT 9399
#define REMOVE_IP "127.0.0.1"

static cairo_surface_t *surface = NULL;

static void
clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static gboolean
configure_event_cb (GtkWidget         *widget,
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

static gboolean
draw_cb (GtkWidget *widget,
 cairo_t   *cr,
 gpointer   data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}

static void
draw_brush (GtkWidget *widget,
    gdouble    x,
    gdouble    y)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_rectangle (cr, x - 3, y - 3, 6, 6);
  cairo_fill (cr);

  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, x - 3, y - 3, 6, 6);
  //g_print("%lf,%lf\n",x,y);
	int sockfd;
	struct sockaddr_in addr;
	char buffer[100];
	int addr_len = sizeof(struct sockaddr_in);
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket created error!");
		exit(1);
	}
	else
	{
		printf("socket created sucessfully!\n");
		printf("socket id:%d\n",sockfd);
	}bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(REMOVE_IP);
	
	if(connect(sockfd,(struct sockaddr *)(&addr),sizeof(struct sockaddr)) == -1)
	{
		perror("connect error!");
		exit(1);
	}
  	sprintf(buffer,"%lf,%lf",x,y);
	if(write(sockfd,buffer,strlen(buffer)) == -1)
	{
		perror("write error!");
		exit(1);
	}
	close(sockfd);
	
	
}

static gboolean
button_press_event_cb (GtkWidget      *widget,
               GdkEventButton *event,
               gpointer        data)
{
  if (surface == NULL)
    return FALSE;

  if (event->button == GDK_BUTTON_PRIMARY)
    {
      draw_brush (widget, event->x, event->y);
    }
  else if (event->button == GDK_BUTTON_SECONDARY)
    {
      clear_surface ();
      gtk_widget_queue_draw (widget);
    }

  return TRUE;
}

static gboolean
motion_notify_event_cb (GtkWidget      *widget,
                GdkEventMotion *event,
                gpointer        data)
{
  if (surface == NULL)
    return FALSE;

  if (event->state & GDK_BUTTON1_MASK)
    draw_brush (widget, event->x, event->y);

  return TRUE;
}

static void
close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);

  gtk_main_quit ();
}

int
main (int   argc,
      char *argv[])
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *da;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

  g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 8);

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
  gtk_container_add (GTK_CONTAINER (window), frame);

  da = gtk_drawing_area_new ();
  gtk_widget_set_size_request (da, 100, 100);

  gtk_container_add (GTK_CONTAINER (frame), da);

  g_signal_connect (da, "draw",
            G_CALLBACK (draw_cb), NULL);
  g_signal_connect (da,"configure-event",
            G_CALLBACK (configure_event_cb), NULL);

  g_signal_connect (da, "motion-notify-event",
            G_CALLBACK (motion_notify_event_cb), NULL);
  g_signal_connect (da, "button-press-event",
            G_CALLBACK (button_press_event_cb), NULL);

  gtk_widget_set_events (da, gtk_widget_get_events (da)
                     | GDK_BUTTON_PRESS_MASK
                     | GDK_POINTER_MOTION_MASK);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
