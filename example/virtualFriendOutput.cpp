/*****************************************
文件名：virtualFriendOutput.cpp
功能：若直接声明一个virtual friend 函数，编译器会报错，此为折衷方案
版本：1.0
作者：Simon
创建时间：2012-06-11 19:47:10 
更新时间：
备注：
******************************************/
#include<iostream>

using namespace std;

class number
{
	private:
		int num;
	public:
		ostream& display(ostream& o)
		{
			o << num << endl;
			return o;
		}
		number(int n = 0)
		{
			num = n;
		}
		friend ostream& operator<<(ostream &o,number n)
		{
			n.display(o);
			return o;
		}
};

int main()
{
	number n;
	cout << n;
	return 0;
}
