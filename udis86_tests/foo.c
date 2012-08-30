#include <udis86.h>

char *buf = "\xb0\x0b\x00";

int main()
{
	ud_t u;

	ud_init(&u);
	ud_set_mode(&u, 32);
	ud_set_syntax(&u, UD_SYN_INTEL);
	ud_set_input_buffer(&u, buf, 3);

	ud_disassemble(&u);
	printf("%s\n", ud_insn_asm(&u));
	printf("op0.size = %d\n", u.operand[0].size);

	return 0;
}
