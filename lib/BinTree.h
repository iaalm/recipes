/*****************************************
文件名：BinTree.h
功能：二叉树类
版本：1.0
作者：Simon
创建时间：2012/06/06 10:25:42 
更新时间：2012/06/11 19:26:11 
备注：1、为了实现虚拟的友元函数，只得将其拆为两个函数实现，比较丑陋。原因是编译器不支持virtual friend函数。
     2、采用dis函数而不是默认参数的ostream& displayTree(ostream& o，unsigned int level = 0);形式是为了保证接口的安全性。
******************************************/
#include<iostream>

using namespace std;

class BinTree
{
	private:
		BinTree *up,*left,*right;
		virtual ostream& dis(ostream& o,unsigned int level);	//便于递归的形式
	public:
		BinTree(BinTree* upNode = NULL,BinTree* leftNode = NULL,BinTree* rightNode = NULL);
		virtual ostream& print(ostream& o) = 0;					//输出本节点数据
		inline friend ostream& operator<<(ostream& o,BinTree& b);		//print的运算符形式
		inline ostream& displayTree(ostream& o);						//输出整颗树（用作接口）
};

ostream& BinTree::dis(ostream& o,unsigned int level)
{
	unsigned int i;
	if(level != 0)
	{
		for(i = 0;i < level - 1;i++)
			o << "|";
		o << "+";
	}
	print(o);
	o << endl;
	level++;
	if(left != NULL)
		left -> dis(o,level);
	if(right != NULL)
		right -> dis(o,level);
	return o;
}
BinTree::BinTree(BinTree* upNode,BinTree* leftNode,BinTree* rightNode)
{
	up = upNode;
	left = leftNode;
	if(left != NULL)
		left -> up = this;
	right = rightNode;
	if(right != NULL)
		right -> up = this;
}

ostream& operator<<(ostream& o,BinTree& b)
{
	return b.print(o);
}

ostream& BinTree::displayTree(ostream& o)
{
	return dis(o,0);
}
