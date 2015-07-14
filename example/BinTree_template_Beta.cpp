#include<iostream>
#include"binTree_template.h"

using namespace std;

int main()
{
	binTree<int>* leaf = new binTree<int>(21);
	binTree<int>* lleaf = new binTree<int>(2,NULL,leaf),*rleaf = new binTree<int>(3);
	binTree<int>* root = new binTree<int>(1,NULL,lleaf,rleaf);
	root -> displayTree(cout);
	return 0;
}
