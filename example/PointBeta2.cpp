#include <cmath>
#include "PointBeta2.h"

//unsigned int point::i=0;     //这个地方有待处理 
//float point::dt;
//point* point::pp[127]/**/;



/*vector GetF(point*a)
{
       vector p;
       p.x=0;p.y=0;p.z=0;
//       p.y=-10*((*a).OutM());
       return p;
}*/

/*environment::environment()
{
                          
}

environment::~environment()
{
                           
}

virtual vector environment::GetF(point*a)
{
       vector p;
       p.x=0;p.z=0;
       p.y=-10*((*a).OutM());
       return p;
}
*/
point::point(float tdt,bool ts,vector tp,vector tv,double tm,float tq)
{
	dt=tdt;
	id=i;
	i++;
	pp[id]=this;
	s=ts;
	p=tp;
	v=tv;
	m=tm;
	q=tq;
}

point::~point()
{

}

void point::move()
{
     if(!s)
     {
         vector tp;
         	double force;
          	float tm;
           	f.x=0;f.y=0;f.z=0;
            	for(unsigned int j=0;j<=i;j++)               //引力
             	{
              		if(j!=id&&pp[j]!=0x0)
                		{
                  			tp=(*pp[j]).OutP();
                  			tm=(*pp[j]).OutM();
                  			force=0.00000000000667*tm*m/pow(((tp.x-p.x)*(tp.x-p.x)+(tp.y-p.y)*(tp.y-p.y)+(tp.z-p.z)*(tp.z-p.z)),1.5);
                  			f.x+=force*(tp.x-p.x);
                  			f.y+=force*(tp.y-p.y);
                  			f.z+=force*(tp.z-p.z);
//            out<<"calaulateG"<<"\r\n";
                         }
                	}
                 	for(unsigned int j=0;j<=i;j++)               //电场力
                  	{
                   		if(j!=id&&pp[j]!=0x0)
                     		{
                       			tp=(*pp[j]).OutP();
                       			tm=(*pp[j]).OutQ();
                       			force=(double)(-90000*100000*tm*q/pow(((tp.x-p.x)*(tp.x-p.x)+(tp.y-p.y)*(tp.y-p.y)+(tp.z-p.z)*(tp.z-p.z)),1.5));
                       			f.x+=force*(tp.x-p.x);
                       			f.y+=force*(tp.y-p.y);
                       			f.z+=force*(tp.z-p.z);
//            out<<"calaulateE"<<"\r\n";  
              		}
               	}
	
  	vector B;
   	B.x=0;B.y=0;B.z=0;
    	        f.x+=OutQ()*(v.y*B.z-v.z*B.y)/OutM();
             			f.y+=OutQ()*(v.z*B.x-v.x*B.z)/OutM();
   			f.z+=OutQ()*(v.x*B.y-v.y*B.x)/OutM();
//      	tp=this->GetF(this);                 //外力（重力、电场力、洛仑兹力） 
       	f.x+=tp.x;
        	f.y+=tp.y;
         	f.z+=tp.z;
	
    	v.x+=f.x*dt/m;
     	v.y+=f.y*dt/m;
      	v.z+=f.z*dt/m;
       	p.x+=v.x*dt;
        	p.y+=v.y*dt;
         	p.z+=v.z*dt;
 //         	out<<id<<":("<<p.x<<","<<p.y<<","<<p.z<<")"<<"\r\n";//draw unfinished
           }
}

vector point::OutP()
{
	return p;
}
vector point::OutF()
{
	return f;
}
vector point::OutV()
{
	return v;
}
double point::OutM()
{
	return m;
}
float point::OutQ()
{
	return q;
}


