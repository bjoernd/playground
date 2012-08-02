#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>
#include <iostream>

struct SimpleData
{
	SimpleData(int number = 0)
		: num(number)
	{ }

	int num;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & num;
	}
};


void storeSimple()
{
	std::ofstream out("simple.dat");
	SimpleData sd1(4);

	std::cout << "Storing data        (" << sd1.num << ")" << std::endl;
	boost::archive::binary_oarchive arch(out);
	arch << sd1;
}


void loadSimple()
{
	std::ifstream in("simple.dat");
	SimpleData sd2;

	std::cout << "plain SimpleData    (" << sd2.num << ")" << std::endl;
	boost::archive::binary_iarchive arch(in);
	arch >> sd2;
	std::cout << "restored SimpleData (" << sd2.num << ")" << std::endl;
}


int main()
{
	storeSimple();
	loadSimple();
	return 0;
}
