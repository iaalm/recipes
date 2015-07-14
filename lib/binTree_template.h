/*****************************************
文件名：binTree_template.h
功能：二叉树类(模板实现方式)
版本：1.0
作者：Simon
创建时间：2012-06-14 14:46:26 
更新时间：
备注：
******************************************/
#include<iostream>

using namespace std;

template<typename T>
class binTree
{
	private:
		T t;
		binTree *up,*left,*right;
		ostream& dis(ostream& o,unsigned level);
	public:
		binTree(T tt,binTree *upNode = NULL,binTree *leftNode = NULL,binTree *rightNode = NULL);
		friend ostream& operator<<(ostream& o,binTree<T>& b);
		T outT();
		ostream& displayTree(ostream& o);
};

template<typename T>
binTree<T>::binTree(T tt,binTree *upNode,binTree *leftNode,binTree *rightNode):t(tt),up(upNode)
{
	left = leftNode;
	if(left != NULL)
		left -> up = this;
	right = rightNode;
	if(right != NULL)
		right -> up = this;
}

template<typename T>
ostream& binTree<T>::dis(ostream& o,unsigned level)
{
	unsigned int i;
	if(level != 0)
	{
		for(i = 0;i < level - 1;i++)
			o << "|";
		o << "+";
	}
	o << t;;
	o << endl;
	level++;
	if(left != NULL)
		left -> dis(o,level);
	if(right != NULL)
		right -> dis(o,level);
	return o;
}

template<typename T>
ostream& operator<<(ostream& o,binTree<T>& b)
{
	return o << b.t;
}

template<typename T>
ostream& binTree<T>::displayTree(ostream& o)
{
	return dis(o,0);
}
