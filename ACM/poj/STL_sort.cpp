#include<iostream>
#include<algorithm>

int main()
{
	int a[10] = {1,5,6,9,4,10,2,3,7,8};
	sort(a,a + 9,std::greater<int> ());
	for(int i = 0;i < 9;i++)
		std::cout << a[i] << " ";
	return 0;
}
