#include <udis86.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/foreach.hpp>

/*
 * libudis86 provides information about decoded data through a C struct. In
 * order to serialize this struct using boost::serialization, we need to extend
 * it with a serialize() method. This is achieved below by deriving a new
 * struct from the C struct that solely adds this function.
 */

/*
 * Some 64bit sample input to work on
 */
unsigned char input [] = { 0x31, 0xed, 0x49, 0x89, 0xd1, 0x5e,
                           0x48, 0x89, 0xe2, 0x48, 0x83, 0xe4,
                           0xf0, 0x50, 0x54 };

/*
 * ud_t contains ud_operand members that need to have dedicated
 * serialization routine as well.
 */
struct udop : public ud_operand
{
	udop(ud_operand& op)
	{
		*this = op;
	}

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & type;
		ar & size;
		ar & lval.uqword;
		ar & base;
		ar & index;
		ar & offset;
		ar & scale;
	}
};


/*
 * Wrapper struct for ud_t
 */
struct udt : public ud_t
{
	udt()
	{
		ud_init(this);
		ud_set_mode(this, 64);
		ud_set_syntax(this, UD_SYN_INTEL);
		ud_set_pc(this, 0);
	}

	udt(unsigned char *buffer, unsigned bytes)
		: udt()
	{
		ud_set_input_buffer(this, buffer, bytes);
	}

	/*
	 * Serialization.
	 *
	 * This method does _not_ serialize all members of ud_t. This would not be
	 * possible, because ud_t also stores pointers to the local input buffer
	 * that was used for decoding the byte stream. This means, we'd have to
	 *    a) serialize all those buffers as well, or
	 *    b) live with the fact that our restored data will contain
	 *       invalid pointers.
	 * Instead of doing so, we only serialize the important non-pointer data
	 * so we can work with the ud_t, but can't continue decoding after
	 * deserialization.
	 */
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & insn_offset;
		ar & insn_hexcode;
		ar & insn_buffer;
		ar & insn_fill;
		ar & dis_mode;
		ar & pc;
		ar & vendor;

		ar & mnemonic;
		ar & static_cast<udop&>(operand[0]);
		ar & static_cast<udop&>(operand[1]);
		ar & static_cast<udop&>(operand[2]);

		ar & error;
		ar & pfx_rex;
		ar & pfx_seg;
		ar & pfx_opr;
		ar & pfx_adr;
		ar & pfx_lock;
		ar & pfx_rep;
		ar & pfx_repe;
		ar & pfx_repne;
		ar & pfx_insn;
		ar & default64;
		ar & opr_mode;
		ar & adr_mode;
		ar & br_far;
		ar & br_near;
		ar & implicit_addr;
		ar & c1;
		ar & c2;
		ar & c3;
		ar & have_modrm;
		ar & modrm;
	}
};


void storeData(std::vector<udt>& vec, char const *file)
{
	std::cout << "Serializing into " << file << "..." << std::endl;
	std::ofstream ofs(file);
	if (ofs.is_open()) {
		boost::archive::binary_oarchive arch(ofs);
		arch << vec;
	}
	ofs.close();
}


void loadData(std::vector<udt>& vec, char const *file)
{
	std::cout << "Reading from " << file << "..." << std::endl;
	std::ifstream ifs(file);
	boost::archive::binary_iarchive arch(ifs);
	if (ifs.is_open()) {
		arch >> vec;
	}
}


void print_vector(std::vector<udt>& vec)
{
	BOOST_FOREACH(udt x, vec) {
		std::cout << std::setw(10) << std::hex << "0x" << x.pc << " "
		          << std::setw(16) << ud_insn_hex(&x) << " : " << ud_insn_asm(&x) << std::endl;
	}
}


int main()
{
	std::vector<udt> vec;
	std::vector<udt> vec_read;
	udt x(input, sizeof(input));

	while (ud_disassemble(&x) != 0) {
		vec.push_back(x);
	}
	print_vector(vec);

	storeData(vec,     "vector.dat");
	loadData(vec_read, "vector.dat");
	print_vector(vec_read);
}
