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
	exit(53);
}


static void
dumpRegs(struct user_regs_struct* reg)
{
}


static void
inspect_syscall(pid_t child)
{
	static int enteredSyscall = 0;
	struct user_regs_struct reg;

	int err = call_ptrace(PTRACE_GETREGS, child, 0, &reg);

	if (!enteredSyscall) {
		printf("\033[32m------------------------- Inspecting Syscall ------------------------\033[0m\n");
		enteredSyscall = 1;
		dumpRegs(&reg);
	} else {
		printf("---> ---> --> -->\n");
		enteredSyscall = 0;
		dumpRegs(&reg);
	}
}


static void
parent(pid_t child)
{
	while (1) {
		int status;
		int err = call_waitpid(child, &status);
		printf("wait: %d\n", status);

		if (WIFEXITED(status)) {
			printf("\033[31;1mChild exited with status %d\033[0m\n", WEXITSTATUS(status));
			return;
		}

		if (WIFSIGNALED(status)) {
			printf("\033[31;1mChild was killed by signal %d\033[0m\n", WTERMSIG(status));
			return;
		}

		if (WIFSTOPPED(status)) {
			printf("\033[33mChild stopped with signal %d\033[0m\n", WSTOPSIG(status));
			if (WSTOPSIG(status) == SIGTRAP) {
				inspect_syscall(child);
			}
		}

		call_ptrace(PTRACE_SYSCALL, child, 0, 0);
	}
}


int
main()
{
	pid_t pid = fork();

	if (pid == 0) {
		child();
	} else if (pid > 0) {
		parent(pid);
	} else {
		perror("fork");
	}
	return 0;
}
