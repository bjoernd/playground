#include <udis86.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/foreach.hpp>

unsigned char input [] = { 0x31, 0xed, 0x49, 0x89, 0xd1, 0x5e,
                           0x48, 0x89, 0xe2, 0x48, 0x83, 0xe4,
                           0xf0, 0x50, 0x54 };

struct udt : public ud_t
{
	udt()
	{
		ud_init(this);
		ud_set_mode(this, 64);
		ud_set_syntax(this, UD_SYN_INTEL);
		ud_set_pc(this, 0);
		ud_set_input_buffer(this, input, sizeof(input));
	}

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & pc;
	}
};

int main()
{
	std::vector<udt> vec;
	udt x;

	while (ud_disassemble(&x) != 0) {
		vec.push_back(x);
	}

	std::cout << "Serializing into vector.dat..." << std::endl;
	std::ofstream ofs("vector.dat");
	if (ofs.is_open()) {
		boost::archive::binary_oarchive arch(ofs);
		BOOST_FOREACH(udt x, vec) {
			std::cout << std::setw(16) << ud_insn_hex(&x) << " : " << ud_insn_asm(&x) << std::endl;
			arch << x;
		}
	}
	ofs.close();

	std::cout << "Reading from vector.dat..." << std::endl;
	std::vector<udt> vec_read;
	std::ifstream ifs("vector.dat");
	boost::archive::binary_iarchive arch(ifs);
	if (ifs.is_open()) {
		while (1) {
			try {
			udt x;
			arch >> x;
			vec_read.push_back(x);
			} catch (boost::archive::archive_exception) {
				break;
			}
		}
	}

	BOOST_FOREACH(udt x, vec_read) {
		std::cout << std::setw(16) << ud_insn_hex(&x) << " : " << ud_insn_asm(&x) << std::endl;
	}
}
