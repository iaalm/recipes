#define N 100

class field
{
	public:
		void field(/*未完成，主要时设定全局常量*/);
		void ~field();
		const float weight,height,MaxSpeed,Damage,tick;    //全局常量
		bool run();                           //动力系统
		unsigned int GetTankNum();            //坦克总数
		struct TankInfor GetTankInfor(unsigned int num);//其他坦克的信息
		unsigned int GetMyNum();              //获得自身的代号
		unsigned int GetBulletNum();          //获得场上的子弹总数
		struct TankInfor GetBulletInfor(unsigned int num);//获得子弹信息
		void move(float x,float y);  //运动
		void fire(float degree);              //开火
	private:
		unsigned int TankNum,BulletNum;       //坦克总数，子弹总数
		struct TankInfor                      //坦克信息
		{
			Tank* PTank;
			float live;
			double x,y; 
		} ti[N];
		struct BulletInfor                     //子弹信息
		{
			float degree,x,y;
		} bl[N];
};
