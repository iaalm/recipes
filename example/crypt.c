#include<stdio.h>
#include<unistd.h>

int main()
{
	puts(crypt("lighting","$6$7kuDbVvljoH2boDb$"));
	//lighting is the string
	//6 means SHA512
	//7kuDbVvljoH2boDb is the salt
	//that is the way shadow used
}
