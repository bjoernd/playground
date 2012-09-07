#include <assert.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/ptrace.h>
#include <sys/personality.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mypt.h"

#define DEBUG 0

static long
call_ptrace(int op, pid_t child, void *addr, void *data)
{
	int ret = ptrace(op, child, addr, data);

	if (ret == -1 && errno)
		perror("ptrace");

	if ((op != PTRACE_PEEKTEXT) &&
		(op != PTRACE_PEEKDATA) &&
		(op != PTRACE_PEEKUSER))
		assert(ret == 0);

	return ret;
}


static pid_t 
call_waitpid(pid_t child, int *status)
{
	pid_t ret = waitpid(child, status, __WALL);
	if (ret == -1) {
		perror("wait");
	}
	return ret;
}


static void
child()
{
	call_ptrace(PTRACE_TRACEME, 0, 0, 0);
	raise(SIGSTOP);
	static char const *hello = "\033[36;1mhello world\033[0m";
	printf("%s\n", hello);
	exit(53);
}


static void
dumpRegs(struct user_regs_struct* regs, pid_t child)
{
#if DEBUG
#if __WORDSIZE == 32
	printf("EAX %08lx EBX %08lx ECX %08lx EDX %08lx\n",
		   regs->eax, regs->ebx, regs->ecx, regs->edx);
	printf("ESI %08lx EDI %08lx ESP %08lx EBP %08lx\n",
		   regs->esi, regs->edi, regs->esp, regs->ebp);
	printf("EIP %08lx ORA %08lx FLG %08lx ............\n",
		   regs->eip, regs->orig_eax, regs->eflags);
#else
	printf("R15 %016lx R14 %016lx R13 %016lx R12 %016lx\n",
		   regs->r15, regs->r14, regs->r13, regs->r12);
	printf("R11 %016lx R10 %016lx R09 %016lx R08 %016lx\n",
		   regs->r11, regs->r12, regs->r9, regs->r8);
	printf("RAX %016lx RBX %016lx RCX %016lx RDX %016lx\n",
		   regs->rax, regs->rbx, regs->rcx, regs->rdx);
	printf("RSI %016lx RDI %016lx RSP %016lx RBP %016lx\n",
		   regs->rsi, regs->rdi, regs->rsp, regs->rbp);
	printf("EIP %016lx ORA %016lx FLG %016lx ............\n",
		   regs->rip, regs->orig_rax, regs->eflags);
#endif // __WORDSIZE
#endif // DEBUG
}


static void
inspect_syscall(pid_t child)
{
	static int enteredSyscall = 0;
	struct user_regs_struct reg; // always the right type (chosen in sys/user.h)

	call_ptrace(PTRACE_GETREGS, child, 0, &reg);

	if (!enteredSyscall) {
		//printf("\033[32m------------------------- Inspecting Syscall ------------------------\033[0m\n");
		enteredSyscall = 1;
		long sysno;
#if __WORDSIZE == 32
		sysno = reg.orig_eax;
#else
		sysno = reg.orig_rax & 0xFFFFFFFF;
#endif
		printf("Syscall: %ld (%s) = ", sysno,
#if __WORDSIZE == 32
			   sysno32(sysno)
#else
			   sysno64(sysno)
#endif
			   );
	} else {
		//printf("---> ---> --> -->\n");
		enteredSyscall = 0;
#if __WORDSIZE == 32
		printf(" return: %ld (0x%lx)\n", reg.eax, reg.eax);
#else
		printf(" return: %ld (0x%lx)\n", reg.rax, reg.rax);
#endif
	}

	dumpRegs(&reg, child);
}


static void
parent(pid_t child)
{
	while (1) {
		int status;
		call_waitpid(child, &status);
		//printf("wait: %d\n", status);

		if (WIFEXITED(status)) {
			printf("\033[31;1mChild exited with status %d\033[0m\n", WEXITSTATUS(status));
			return;
		}

		if (WIFSIGNALED(status)) {
			printf("\033[31;1mChild was killed by signal %d\033[0m\n", WTERMSIG(status));
			return;
		}

		if (WIFSTOPPED(status)) {
			//printf("\033[33mChild stopped with signal %d\033[0m\n", WSTOPSIG(status));
			if (WSTOPSIG(status) == (0x80 | SIGTRAP)) {
				inspect_syscall(child);
			}
			if (WSTOPSIG(status) == SIGSTOP) {
				ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
			}
		}

		call_ptrace(PTRACE_SYSCALL, child, 0, 0);
	}
}


int
main()
{
	pid_t pid = fork();
	init32();
#if __WORDSIZE == 64
	init64();
#endif

	if (pid == 0) {
		child();
	} else if (pid > 0) {
		parent(pid);
	} else {
		perror("fork");
	}
	return 0;
}
