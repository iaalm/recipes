/**************************************************************
文件名：tm.h
作者：simon
版本：1.0
创建日期：2012/05/25 09:31:32 
修改日期：
备注：
****************************************************************/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>

#ifndef _TURING_MACHIINE_
#define _TURING_MACHIINE_

struct node
{
	unsigned int num;
	node *pre,*ne;
};

class PageTape
{
private:
	node *now;
	int index;
	int bottom,top;
public:
	PageTape(int start,std::vector<unsigned int>& init);
	unsigned int Go(short d);				//d == 3 no move;d==0 left;d==1 right
	void Write(unsigned int n);
	friend std::ostream& operator<<(std::ostream& o,PageTape& t);
};

struct instruction
{
	unsigned int flag,num,ope;
};

class TuringMachine
{
private:
	instruction ***ins;
	unsigned int flag;
	unsigned int MaxNum,MaxFlag;
public:
	TuringMachine(unsigned int NNUm,unsigned int NFlag,const std::vector<unsigned int[5]>& in);		//num,flag,NeWFlag,NewNum,operator
	void Work(PageTape& p);
};

#endif
