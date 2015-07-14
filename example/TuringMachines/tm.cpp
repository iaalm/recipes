#include "tm.h"
#include<assert.h>

PageTape::PageTape(int start,std::vector<unsigned int>& init)
{
	bottom = start;
	top = start + init.size() - 1;
	node *p;
	now = new node;
	now -> num = init[0];
	now -> pre = NULL;
	now -> ne = NULL;
	for(std::vector<unsigned int>::iterator it = init.begin() + 1;it != init.end();it++)
	{
		p = now;
		now = new node;
		now -> num = *it;
		now -> pre = p;
		now -> ne = NULL;
		p -> ne = now;
	}
	index = top;
	while(index != 0)
	{
		Go(index < 0);
	}
}
unsigned int PageTape::Go(short d)
{
	if(d == 0)
	{
		index--;
		if(now -> pre == NULL)
		{
			bottom--;
			assert(index == bottom);
			now -> pre = new node;
			now -> pre -> num = 0;
			now -> pre -> ne = now;
			now -> pre -> pre =NULL;
		}
		now = now -> pre;
	}
	else
	{
		index++;
		if(now -> ne == NULL)
		{
			top++;
			assert(index == top);
			now -> ne = new node;
			now -> ne -> num = 0;
			now -> ne -> pre = now;
			now -> ne -> ne =NULL;
		}
		now = now -> ne;
	}
	return now -> num;
}

void PageTape::Write(unsigned int n)
{
	now -> num = n;
}

std::ostream& operator<<(std::ostream& o,PageTape& t)
{
	int i;
	node* p;
	for(i = t.bottom;i <= t.top;i++)
		o << std::setw(8) << std::setfill(' ') << i;
	o << std::endl;
	while(t.index != t.bottom)
		t.Go(0);
	for(i = t.bottom,p = t.now;i <= t.top;i++,p = p -> ne)
		o << std::setw(8) << std::setfill(' ') << p -> num;
	o << std::endl;
	return o;
}

TuringMachine::TuringMachine(unsigned int NNum,unsigned int NFlag,const std::vector<unsigned int[5]>& in)
{
	instruction *p;
	MaxNum = NNum;
	MaxFlag = NFlag;
	ins = new instruction*[NNum][NFlag];
	for(int i = 0;i < NNum;i++)
		for(int j = 0;j < NFlag;j++)
			instruction[i][j] = NULL;
	for(std::vector<unsigned int[5]>::iterator it = in.begin() + 1;it != in.end();it++)
	{
		 if(ins[*it[0]][*it[1]] != NULL)
		 {
			 fprintf(stderr,"re-define operator!\n");
			 exit(1);
		 }
		 p = new instruction;
		 p -> flag = *it[2];
		 p -> num = *it[3];
		 p -> ope = *it[4];
		 ins[*it[0]][*it[1]] = p;
	}
}

void TuringMachine::Work(PageTape& p)
{
	flag = 0;
	unsigned int ope = 3,num;
	while(1)
	{
		num = p.Go((short)ope);
		if(ins[num][flag] == NULL)
		{
			fprintf(stderr,"non-defined operator!\n");
			exit(2);
		}
		p.Write(ins[num][flag] -> num);
		flag = ins[num][flag] -> flag;
		ope = ins[num][flag] -> ope;
		if(ope == 4)
			break;
	}
}
