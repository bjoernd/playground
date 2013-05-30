#include <fcntl.h>
#include <linux/kvm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ERROUT(cond, msg) do { \
	if (cond) { \
		perror(msg); \
		exit(1); \
	}} while (0)

static int kvm_fd = 0;
static int  vm_fd = 0;

void cleanup()
{
	if (kvm_fd) close(vm_fd);
	if  (vm_fd) close(kvm_fd);
}

int main()
{
	printf("-------- KVM Example --------\n");
	int err = atexit(cleanup);
	ERROUT(err < 0, "atexit");

	kvm_fd = open("/dev/kvm", O_RDWR);
	printf("Opened KVM device: %d\n", kvm_fd);
	ERROUT(kvm_fd < 0, "Open KVM dev");

	err = ioctl(kvm_fd, KVM_GET_API_VERSION, 0);
	printf("KVM_GET_API_VERSION: %d\n", err);
	ERROUT(err < 0, "GET_API_VERSION");

	vm_fd = ioctl(kvm_fd, KVM_CREATE_VM, 0);
	printf("KVM_CREATE_VM: %d\n", vm_fd);
	ERROUT(vm_fd < 0, "create vm");

	return 0;
}
