#include <iostream>

class FooObj
{
	public:
		FooObj()
		{
			std::cout << "FOO Obj\n";
		}
};


int main(int argc, char *argv[])
{
	FooObj o;
	std::cout << "foo!\n";
	return 0;
}
