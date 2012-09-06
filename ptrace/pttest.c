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
	assert(ret == child);
	return ret;
}


static void
child()
{
}


static void
parent(pid_t child)
{
	int status;
	call_waitpid(child, &status);
	printf("wait: %d\n", status);
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
