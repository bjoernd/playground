#include <stdio.h>
#include <stdint.h>

extern char** environ;

extern void vdso_init_from_auxv(void *auxv);
extern void vdso_init_from_sysinfo_ehdr(uintptr_t base);
extern void *vdso_sym(const char *version, const char *name);
extern void vdso_iterate();

int main(int argc, char **argv, char **envp)
{
	while (*envp)
		envp++;

	printf("auxp: %p\n", ++envp);
	vdso_init_from_auxv(envp);

	vdso_iterate();
	
	return 0;
}
