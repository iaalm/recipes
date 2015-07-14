/*****************************************
文件名：BinTreeBeta.cpp
功能：二叉树类BinTree的测试示例
版本：1.0
作者：Simon
创建时间：2012/06/06 10:25:42 
更新时间：
备注：
******************************************/

#include<iostream>
#include"BinTree.h"

using namespace std;

class intBinTree : public BinTree		//简单的继承出一个只含一个整型变量的二叉树，测试输出
{
	private:
		int num;
	public:
		intBinTree(int n = 0,intBinTree* up = NULL,intBinTree* left = NULL,intBinTree* right = NULL):BinTree(up,left,right)
	{
		num = n;
	}
		ostream& print(ostream &o);
};

ostream& intBinTree::print(ostream &o)
{
	return o << num;
}

int main()
{
	intBinTree* leaf = new intBinTree(21);
	intBinTree* lleaf = new intBinTree(2,NULL,leaf),*rleaf = new intBinTree(3);
	intBinTree* root = new intBinTree(1,NULL,lleaf,rleaf);
	root -> displayTree(cout);
	return 0;
}
