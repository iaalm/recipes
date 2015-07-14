#include "vector.h"

/*class environment
{
      public:
            virtual vector GetF(point*a);
            environment();
            virtual ~environment();
};
*/
class point//:public environment
{
public:
	float OutQ();
	double OutM();
	vector OutP();
	vector OutF();
	vector OutV();
	void move();
	point(float tdt,bool ts,vector tp,vector tv,double tm,float tq);
	virtual ~point();
private:
	static unsigned int i; //成员计数器 
	static float dt;
	static point *pp[127];  //成员指针  
	unsigned int id;
	bool s;                //是否静止
	vector p;              //坐标 
	vector f;              //力 
	vector v;              //速度 
	float q;               //所带电荷
	double m;               //质量

}
