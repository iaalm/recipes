#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PI 3.1415926


void Turn(double*cx,double*cy,double x0,double y0,double z0,double x,double y,double z,double a,double b,int i);
double deal(double a,double b);
double XY_3_2(double x,double y,double x0,double y0,double a);
double Display(double cx[],double cy[],int *count);
double coordx[100];
double coordy[100];

static gboolean on_expose_event(GtkWidget *widget,GdkEventExpose *event,gpointer data)
{
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width (cr, 5);
	int i, j,count;
	count = *((int *)data);
	printf("%d\n",count);

	for(i=0;i<count;i=i+2)
	{
		cairo_move_to(cr, coordx[i], coordy[i]);
		cairo_line_to(cr, coordx[i+1], coordy[i+1]);
	}
	
	cairo_stroke(cr);

	return FALSE;
}

/*gboolean clicked(GtkWidget *widget, GdkEventButton *event,
		gpointer user_data)
{
	double  right,up;

	if (event->button == 1) {
		coordx[count] = event->x;

		coordy[count] = event->y;

		printf("%lf,%lf\n",coordx[count],coordy[count]);
		count++;
		if(count>=2)
		{
			right = coordx[count-1]-coordx[count-2];
			up = coordy[count-1]-coordy[count-2];
			printf("left and right %lf\n",right);
			printf("up and down  %lf\n",up);
		}
	}
	if (event->button == 3) {
	  gtk_widget_queue_draw(widget);
	  }
±	return TRUE;
}*/



	int
main (int argc, char *argv[])
{
	int i;
	int count;
	GtkWidget *window;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);


	Display(coordx,coordy,&count);
	for(i= 0 ;i<8;i++)
	{
		printf("%lf %lf\n",coordx[i],coordy[i]);
	}
	g_signal_connect(window, "expose-event",
			G_CALLBACK(on_expose_event), &count);
	g_signal_connect(window, "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
//	g_signal_connect(window, "button-press-event",
//			G_CALLBACK(clicked), NULL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "lines");
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);

	gtk_widget_set_app_paintable(window, TRUE);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

double Display(double cx[],double cy[],int *count)
{
	double x0=0,y0=0,z0=0;
	double x,y,z;
	double a=180,b=0;
	int i;
	FILE*fp;
	if((fp=fopen("1","r"))==NULL)
	{
		exit (0);
	}
	for(i = 0;fscanf(fp,"%lf%lf%lf",&x,&y,&z) != EOF;i++)
	{
		printf("%d\n",*count);
		fprintf(stderr,"%lf %lf %lf \n",x,y,z);
		Turn(cx,cy,x0,y0,z0,x,y,z,a,b,i);
	}
	*count = i;
	fclose(fp);
}
void Turn(double*cx,double*cy,double x0,double y0,double z0,double x,double y,double z,double a,double b,int i)
{
	b=deal(a,b);
	*(cx+i)=XY_3_2(x,y,x0,y0,a);
	*(cy+i)=XY_3_2(x,z,x0,z0,b);
}
double XY_3_2(double x,double y,double x0,double y0,double a)
{
	double m;
	if(y==y0)
	{
		m=PI/2.0;
	}
	else
	{
		m=0-(x-x0)/(y-y0);
		m=atan(m);
	}
	if(m<0.0)
	{
		m=m+PI;
	}

	a=(a/360.0)*2.0*PI;
	if(a>=PI)
	{
		a=a-PI;
		if(a==0)
		{
			if(x<x0)
			{
				printf("Wrong! 1 \n");
				exit(0);
				return (-1);
			}
		}
		else
		{
			if(abs(a-PI/2)<(0.000001))
			{
				if(y<y0)
				{
					printf("Wrong! 2 \n");
					exit(0);
					return (-1);
				}
			}
			else
			{
				if(tan(a-PI/2)*(x-x0)+y0-y>0)
				{
					printf("Wrong! 3 \n");
					exit(0);
					return (-1);
				}
			}
		}
	}
	else
	{
		if(a==0)
		{
			if(x>x0)
			{
				printf("Wrong! 4 \n");
				exit(0);
				return (-1);
			}
		}
		else 
		{
			if(abs(a-PI/2)<(0.000001))
			{
				if(y>y0)
				{
					printf("Wrong! 5 \n");
					exit(0);
					return (-1);
				}
			}
			else
			{
				if(tan(a-PI/2)*(x-x0)+y0-y<0)
				{
					printf("Wrong! 6 \n");
					exit(0);
					return (-1);
				}
			}
		}
	}

	m=(PI/2.0)-(m-a);
	m=(350/sqrt(3.0))*tan(m);
	m=350+m;
	return(m);

}

double deal(double a,double b)
{
	if(a>90&&a<270)
	{
		b=180+b;
	}
	else
	{
		b=360-b;
		if(b>=360)
		{
			b=b-360;
		}
	}
	return (b);
}
