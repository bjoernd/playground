#include <string.h>

char *sys64[320];

void init64()
{
	memset(sys64, 0, sizeof(sys64));
	sys64[0]="read";
	sys64[1]="write";
	sys64[2]="open";
	sys64[3]="close";
	sys64[4]="stat";
	sys64[5]="fstat";
	sys64[6]="lstat";
	sys64[7]="poll";
	sys64[8]="lseek";
	sys64[9]="mmap";
	sys64[10]="mprotect";
	sys64[11]="munmap";
	sys64[12]="brk";
	sys64[13]="rt_sigaction";
	sys64[14]="rt_sigprocmask";
	sys64[15]="rt_sigreturn";
	sys64[16]="ioctl";
	sys64[17]="pread64";
	sys64[18]="pwrite64";
	sys64[19]="readv";
	sys64[20]="writev";
	sys64[21]="access";
	sys64[22]="pipe";
	sys64[23]="select";
	sys64[24]="sched_yield";
	sys64[25]="mremap";
	sys64[26]="msync";
	sys64[27]="mincore";
	sys64[28]="madvise";
	sys64[29]="shmget";
	sys64[30]="shmat";
	sys64[31]="shmctl";
	sys64[32]="dup";
	sys64[33]="dup2";
	sys64[34]="pause";
	sys64[35]="nanosleep";
	sys64[36]="getitimer";
	sys64[37]="alarm";
	sys64[38]="setitimer";
	sys64[39]="getpid";
	sys64[40]="sendfile";
	sys64[41]="socket";
	sys64[42]="connect";
	sys64[43]="accept";
	sys64[44]="sendto";
	sys64[45]="recvfrom";
	sys64[46]="sendmsg";
	sys64[47]="recvmsg";
	sys64[48]="shutdown";
	sys64[49]="bind";
	sys64[50]="listen";
	sys64[51]="getsockname";
	sys64[52]="getpeername";
	sys64[53]="socketpair";
	sys64[54]="setsockopt";
	sys64[55]="getsockopt";
	sys64[56]="clone";
	sys64[57]="fork";
	sys64[58]="vfork";
	sys64[59]="execve";
	sys64[60]="exit";
	sys64[61]="wait4";
	sys64[62]="kill";
	sys64[63]="uname";
	sys64[64]="semget";
	sys64[65]="semop";
	sys64[66]="semctl";
	sys64[67]="shmdt";
	sys64[68]="msgget";
	sys64[69]="msgsnd";
	sys64[70]="msgrcv";
	sys64[71]="msgctl";
	sys64[72]="fcntl";
	sys64[73]="flock";
	sys64[74]="fsync";
	sys64[75]="fdatasync";
	sys64[76]="truncate";
	sys64[77]="ftruncate";
	sys64[78]="getdents";
	sys64[79]="getcwd";
	sys64[80]="chdir";
	sys64[81]="fchdir";
	sys64[82]="rename";
	sys64[83]="mkdir";
	sys64[84]="rmdir";
	sys64[85]="creat";
	sys64[86]="link";
	sys64[87]="unlink";
	sys64[88]="symlink";
	sys64[89]="readlink";
	sys64[90]="chmod";
	sys64[91]="fchmod";
	sys64[92]="chown";
	sys64[93]="fchown";
	sys64[94]="lchown";
	sys64[95]="umask";
	sys64[96]="gettimeofday";
	sys64[97]="getrlimit";
	sys64[98]="getrusage";
	sys64[99]="sysinfo";
	sys64[100]="times";
	sys64[101]="ptrace";
	sys64[102]="getuid";
	sys64[103]="syslog";
	sys64[104]="getgid";
	sys64[105]="setuid";
	sys64[106]="setgid";
	sys64[107]="geteuid";
	sys64[108]="getegid";
	sys64[109]="setpgid";
	sys64[110]="getppid";
	sys64[111]="getpgrp";
	sys64[112]="setsid";
	sys64[113]="setreuid";
	sys64[114]="setregid";
	sys64[115]="getgroups";
	sys64[116]="setgroups";
	sys64[117]="setresuid";
	sys64[118]="getresuid";
	sys64[119]="setresgid";
	sys64[120]="getresgid";
	sys64[121]="getpgid";
	sys64[122]="setfsuid";
	sys64[123]="setfsgid";
	sys64[124]="getsid";
	sys64[125]="capget";
	sys64[126]="capset";
	sys64[127]="rt_sigpending";
	sys64[128]="rt_sigtimedwait";
	sys64[129]="rt_sigqueueinfo";
	sys64[130]="rt_sigsuspend";
	sys64[131]="sigaltstack";
	sys64[132]="utime";
	sys64[133]="mknod";
	sys64[134]="uselib";
	sys64[135]="personality";
	sys64[136]="ustat";
	sys64[137]="statfs";
	sys64[138]="fstatfs";
	sys64[139]="sysfs";
	sys64[140]="getpriority";
	sys64[141]="setpriority";
	sys64[142]="sched_setparam";
	sys64[143]="sched_getparam";
	sys64[144]="sched_setscheduler";
	sys64[145]="sched_getscheduler";
	sys64[146]="sched_get_priority_max";
	sys64[147]="sched_get_priority_min";
	sys64[148]="sched_rr_get_interval";
	sys64[149]="mlock";
	sys64[150]="munlock";
	sys64[151]="mlockall";
	sys64[152]="munlockall";
	sys64[153]="vhangup";
	sys64[154]="modify_ldt";
	sys64[155]="pivot_root";
	sys64[156]="_sysctl";
	sys64[157]="prctl";
	sys64[158]="arch_prctl";
	sys64[159]="adjtimex";
	sys64[160]="setrlimit";
	sys64[161]="chroot";
	sys64[162]="sync";
	sys64[163]="acct";
	sys64[164]="settimeofday";
	sys64[165]="mount";
	sys64[166]="umount2";
	sys64[167]="swapon";
	sys64[168]="swapoff";
	sys64[169]="reboot";
	sys64[170]="sethostname";
	sys64[171]="setdomainname";
	sys64[172]="iopl";
	sys64[173]="ioperm";
	sys64[174]="create_module";
	sys64[175]="init_module";
	sys64[176]="delete_module";
	sys64[177]="get_kernel_syms";
	sys64[178]="query_module";
	sys64[179]="quotactl";
	sys64[180]="nfsservctl";
	sys64[181]="getpmsg";
	sys64[182]="putpmsg";
	sys64[183]="afs_syscall";
	sys64[184]="tuxcall";
	sys64[185]="security";
	sys64[186]="gettid";
	sys64[187]="readahead";
	sys64[188]="setxattr";
	sys64[189]="lsetxattr";
	sys64[190]="fsetxattr";
	sys64[191]="getxattr";
	sys64[192]="lgetxattr";
	sys64[193]="fgetxattr";
	sys64[194]="listxattr";
	sys64[195]="llistxattr";
	sys64[196]="flistxattr";
	sys64[197]="removexattr";
	sys64[198]="lremovexattr";
	sys64[199]="fremovexattr";
	sys64[200]="tkill";
	sys64[201]="time";
	sys64[202]="futex";
	sys64[203]="sched_setaffinity";
	sys64[204]="sched_getaffinity";
	sys64[205]="set_thread_area";
	sys64[206]="io_setup";
	sys64[207]="io_destroy";
	sys64[208]="io_getevents";
	sys64[209]="io_submit";
	sys64[210]="io_cancel";
	sys64[211]="get_thread_area";
	sys64[212]="lookup_dcookie";
	sys64[213]="epoll_create";
	sys64[214]="epoll_ctl_old";
	sys64[215]="epoll_wait_old";
	sys64[216]="remap_file_pages";
	sys64[217]="getdents64";
	sys64[218]="set_tid_address";
	sys64[219]="restart_syscall";
	sys64[220]="semtimedop";
	sys64[221]="fadvise64";
	sys64[222]="timer_create";
	sys64[223]="timer_settime";
	sys64[224]="timer_gettime";
	sys64[225]="timer_getoverrun";
	sys64[226]="timer_delete";
	sys64[227]="clock_settime";
	sys64[228]="clock_gettime";
	sys64[229]="clock_getres";
	sys64[230]="clock_nanosleep";
	sys64[231]="exit_group";
	sys64[232]="epoll_wait";
	sys64[233]="epoll_ctl";
	sys64[234]="tgkill";
	sys64[235]="utimes";
	sys64[236]="vserver";
	sys64[237]="mbind";
	sys64[238]="set_mempolicy";
	sys64[239]="get_mempolicy";
	sys64[240]="mq_open";
	sys64[241]="mq_unlink";
	sys64[242]="mq_timedsend";
	sys64[243]="mq_timedreceive";
	sys64[244]="mq_notify";
	sys64[245]="mq_getsetattr";
	sys64[246]="kexec_load";
	sys64[247]="waitid";
	sys64[248]="add_key";
	sys64[249]="request_key";
	sys64[250]="keyctl";
	sys64[251]="ioprio_set";
	sys64[252]="ioprio_get";
	sys64[253]="inotify_init";
	sys64[254]="inotify_add_watch";
	sys64[255]="inotify_rm_watch";
	sys64[256]="migrate_pages";
	sys64[257]="openat";
	sys64[258]="mkdirat";
	sys64[259]="mknodat";
	sys64[260]="fchownat";
	sys64[261]="futimesat";
	sys64[262]="newfstatat";
	sys64[263]="unlinkat";
	sys64[264]="renameat";
	sys64[265]="linkat";
	sys64[266]="symlinkat";
	sys64[267]="readlinkat";
	sys64[268]="fchmodat";
	sys64[269]="faccessat";
	sys64[270]="pselect6";
	sys64[271]="ppoll";
	sys64[272]="unshare";
	sys64[273]="set_robust_list";
	sys64[274]="get_robust_list";
	sys64[275]="splice";
	sys64[276]="tee";
	sys64[277]="sync_file_range";
	sys64[278]="vmsplice";
	sys64[279]="move_pages";
	sys64[280]="utimensat";
	sys64[281]="epoll_pwait";
	sys64[282]="signalfd";
	sys64[283]="timerfd_create";
	sys64[284]="eventfd";
	sys64[285]="fallocate";
	sys64[286]="timerfd_settime";
	sys64[287]="timerfd_gettime";
	sys64[288]="accept4";
	sys64[289]="signalfd4";
	sys64[290]="eventfd2";
	sys64[291]="epoll_create1";
	sys64[292]="dup3";
	sys64[293]="pipe2";
	sys64[294]="inotify_init1";
	sys64[295]="preadv";
	sys64[296]="pwritev";
	sys64[297]="rt_tgsigqueueinfo";
	sys64[298]="perf_event_open";
	sys64[299]="recvmmsg";
	sys64[300]="fanotify_init";
	sys64[301]="fanotify_mark";
	sys64[302]="prlimit64";
	sys64[303]="name_to_handle_at";
	sys64[304]="open_by_handle_at";
	sys64[305]="clock_adjtime";
	sys64[306]="syncfs";
	sys64[307]="sendmmsg";
	sys64[308]="setns";
	sys64[309]="getcpu";
	sys64[310]="process_vm_readv";
	sys64[311]="process_vm_writev";
}


char const *sysno64(unsigned sysno)
{
	if (sysno > sizeof(sys64)-1) {
		return "<invalid>";
	}
	return sys64[sysno];
}
