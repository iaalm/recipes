template <typename T>
class number
{
	public:
		const unsigned int NumberLength,DegreeLength;
		number(unsigned int NumL);
		number(unsigned int NumL,unsigned int DegL);
		~number();
		number operator +(const T& n); 
		number operator -(const T& n); 
		number operator *(const T& n); 
		number operator /(const T& n); 
	private:
		void* /*或许int*更好？*/ Num;
};
//以上作为.h文件

number::number(unsigned int NumL)
{
	Num = malloc(NumL);
	NumberLength = NumL;
}

number::number(unsigned int NumL,unsigned int DegL)
{
	Num = malloc(NumL + DegL);
	NumberLength = NumL;
	DegreeLength = DegL;
}

number::~number()
{
	free(Num);
}

int main (int argc, char const* argv[])
{
	number(1);
	return 0;
}
