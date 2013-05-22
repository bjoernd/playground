#include <stdio.h>
#include <stdint.h>

extern char** environ;

extern void vdso_init_from_auxv(void *auxv);
extern void vdso_init_from_sysinfo_ehdr(uintptr_t base);
extern void *vdso_sym(const char *version, const char *name);
extern void vdso_iterate();

int main(int argc, char **argv, char **envp)
{
	/* First we need to get to the aux pointer, which
	 * is the one after the final NULL terminating the
	 * environment variables.
	 */
	while (*envp)
		envp++;

	// init vdso parser
	vdso_init_from_auxv(envp);
	// print symbols
	vdso_iterate();
	
	return 0;
}
