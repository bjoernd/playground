#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

/*
 * Pretty-printing stuff
 */
static char const *B   = "\033[36m";
static char const *RES = "\033[0m";

/******************************************************************************
                           Simple data serialization
 ******************************************************************************/
struct SimpleData
{
	SimpleData(int number = 0)
		: num(number)
	{ }

	int num;

	/*
	 * In order to serialize a class instance, the class needs to provide
	 * at least a serialize() method that interacts with the serialization
	 * stream.
	 *
	 * Fancy feature: They use the addressof operator, which depending on
	 * the type of the Archive either writes to a serializer or reads from
	 * it. This ensures that you only need _one_ template method for
	 * serialization and automatically all members are read/written in the
	 * same order.
	 */
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & num;
	}
};


void storeSimple()
{
	SimpleData sd1(4); // single data instance

	std::ofstream out("simple.dat");           // standard C++ file stream
	boost::archive::binary_oarchive arch(out); // write binary output to file

	std::cout << "Storing data        (" << sd1.num << ")" << std::endl;

	arch << sd1;
}

void loadSimple()
{
	SimpleData sd2;

	std::cout << "plain SimpleData    (" << sd2.num << ")" << std::endl;

	std::ifstream in("simple.dat");           // input file
	boost::archive::binary_iarchive arch(in); // read binary data
	arch >> sd2;

	std::cout << "restored SimpleData (" << sd2.num << ")" << std::endl;
}


/******************************************************************************
                       Serialize virtual class instances
 ******************************************************************************/

class Base
{
	public:
		Base(int n = 0)
			: _num(n)
		{ }

		int number() { return _num; }
		virtual void print() = 0;

		template <class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & _num;
		}

		virtual ~Base() { }

	private:
		int _num;
};


class Derived1 : public Base
{
	public:
		Derived1(int num = 0)
			: Base(num)
		{ }

		virtual void print()
		{
			std::cout << "DERIVED 1 " << number() << std::endl;
		}

		/*
		 * In a class hierarchy, all classes need a serialize()
		 * template method. Important: you're supposed to never
		 * call the base class' serialize() method directly. Instead,
		 * use boost::serialization::base_object<T>(*this). This
		 * is necessary, because the serializer tries to be clever
		 * about not writing duplicate objects etc.
		 */
		template <class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Base>(*this);
		}
};

class Derived2 : public Base
{
	public:
		Derived2(int num = 0)
			: Base(num)
		{ }

		virtual void print()
		{
			std::cout << "DERIVED 2 " << number() << std::endl;
		}

		template <class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Base>(*this);
		}
};


/*
 * Writing / reading to derived instances has a problem: Usually you want
 * to have a container of BASE objects and iterate over this container
 * serializing all objects regardless of their concrete type. When reading
 * them, you however want the correct subtype object to be created by the
 * serializer. Boost::serialization does this through three mechanisms:
 *
 * 1) You take a pointer to base class and write it to the output archive.
 *    (Writing pointers is handled specially by the library.)
 * 2) You 'register' your derived objects with the serializer, so that it
 *    can assign proper type IDs to each object.
 *    -> BOOST_CLASS_EXPORT_GUID(<type>, "ID");
 * 3) You read data from the input archive into a pointer to BASE. The
 *    object IDs will then be used to properly create the right instance
 *    object.
 *
 * XXX: Of course, after using the deserialized objects, you need to
 *      free them manually (or use some kind of smart_ptr).
 *
 * Detailed info:
 * http://www.boost.org/doc/libs/1_50_0/libs/serialization/doc/special.html
 */
BOOST_CLASS_EXPORT_GUID(Derived1, "Derived1");
BOOST_CLASS_EXPORT_GUID(Derived2, "Derived2");

void storeVirt()
{
	std::ofstream out("virtual.dat");
	boost::archive::binary_oarchive arch(out);

	Derived1 one(2);
	Derived2 two(4);

	/* Writing ptr to base class */
	Base *b1 = &one;
	Base *b2 = &two;

	arch << b1;
	arch << b2;

	b1->print();
	b2->print();
}


void loadVirt()
{
	Base *b1, *b2;
	std::ifstream in("virtual.dat");
	boost::archive::binary_iarchive arch(in);

	arch >> b1;
	arch >> b2;

	b1->print();
	b2->print();

	delete b1;
	delete b2;
}


int main()
{
	std::cout << B << "-------- " << std::setw(30) << std::left
	          << "Simple storage" << " --------"
	          << RES << std::endl;
	storeSimple();
	loadSimple();

	std::cout << B << "-------- " << std::setw(30) << std::left
	          << "Derived object storage" << " --------"
	          << RES << std::endl;
	storeVirt();
	loadVirt();
	return 0;
}
