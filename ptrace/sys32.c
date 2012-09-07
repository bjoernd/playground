#include <string.h>

char *sys32[350];

void init32()
{
	memset(sys32, 0, sizeof(sys32));
	sys32[0]="restart_syscall";
	sys32[1]="exit";
	sys32[2]="fork";
	sys32[3]="read";
	sys32[4]="write";
	sys32[5]="open";
	sys32[6]="close";
	sys32[7]="waitpid";
	sys32[8]="creat";
	sys32[9]="link";
	sys32[10]="unlink";
	sys32[11]="execve";
	sys32[12]="chdir";
	sys32[13]="time";
	sys32[14]="mknod";
	sys32[15]="chmod";
	sys32[16]="lchown";
	sys32[17]="break";
	sys32[18]="oldstat";
	sys32[19]="lseek";
	sys32[20]="getpid";
	sys32[21]="mount";
	sys32[22]="umount";
	sys32[23]="setuid";
	sys32[24]="getuid";
	sys32[25]="stime";
	sys32[26]="ptrace";
	sys32[27]="alarm";
	sys32[28]="oldfstat";
	sys32[29]="pause";
	sys32[30]="utime";
	sys32[31]="stty";
	sys32[32]="gtty";
	sys32[33]="access";
	sys32[34]="nice";
	sys32[35]="ftime";
	sys32[36]="sync";
	sys32[37]="kill";
	sys32[38]="rename";
	sys32[39]="mkdir";
	sys32[40]="rmdir";
	sys32[41]="dup";
	sys32[42]="pipe";
	sys32[43]="times";
	sys32[44]="prof";
	sys32[45]="brk";
	sys32[46]="setgid";
	sys32[47]="getgid";
	sys32[48]="signal";
	sys32[49]="geteuid";
	sys32[50]="getegid";
	sys32[51]="acct";
	sys32[52]="umount2";
	sys32[53]="lock";
	sys32[54]="ioctl";
	sys32[55]="fcntl";
	sys32[56]="mpx";
	sys32[57]="setpgid";
	sys32[58]="ulimit";
	sys32[59]="oldolduname";
	sys32[60]="umask";
	sys32[61]="chroot";
	sys32[62]="ustat";
	sys32[63]="dup2";
	sys32[64]="getppid";
	sys32[65]="getpgrp";
	sys32[66]="setsid";
	sys32[67]="sigaction";
	sys32[68]="sgetmask";
	sys32[69]="ssetmask";
	sys32[70]="setreuid";
	sys32[71]="setregid";
	sys32[72]="sigsuspend";
	sys32[73]="sigpending";
	sys32[74]="sethostname";
	sys32[75]="setrlimit";
	sys32[77]="getrusage";
	sys32[78]="gettimeofday";
	sys32[79]="settimeofday";
	sys32[80]="getgroups";
	sys32[81]="setgroups";
	sys32[82]="select";
	sys32[83]="symlink";
	sys32[84]="oldlstat";
	sys32[85]="readlink";
	sys32[86]="uselib";
	sys32[87]="swapon";
	sys32[88]="reboot";
	sys32[89]="readdir";
	sys32[90]="mmap";
	sys32[91]="munmap";
	sys32[92]="truncate";
	sys32[93]="ftruncate";
	sys32[94]="fchmod";
	sys32[95]="fchown";
	sys32[96]="getpriority";
	sys32[97]="setpriority";
	sys32[98]="profil";
	sys32[99]="statfs";
	sys32[100]="fstatfs";
	sys32[101]="ioperm";
	sys32[102]="socketcall";
	sys32[103]="syslog";
	sys32[104]="setitimer";
	sys32[105]="getitimer";
	sys32[106]="stat";
	sys32[107]="lstat";
	sys32[108]="fstat";
	sys32[109]="olduname";
	sys32[110]="iopl";
	sys32[111]="vhangup";
	sys32[112]="idle";
	sys32[113]="vm86old";
	sys32[114]="wait4";
	sys32[115]="swapoff";
	sys32[116]="sysinfo";
	sys32[117]="ipc";
	sys32[118]="fsync";
	sys32[119]="sigreturn";
	sys32[120]="clone";
	sys32[121]="setdomainname";
	sys32[122]="uname";
	sys32[123]="modify_ldt";
	sys32[124]="adjtimex";
	sys32[125]="mprotect";
	sys32[126]="sigprocmask";
	sys32[127]="create_module";
	sys32[128]="init_module";
	sys32[129]="delete_module";
	sys32[130]="get_kernel_syms";
	sys32[131]="quotactl";
	sys32[132]="getpgid";
	sys32[133]="fchdir";
	sys32[134]="bdflush";
	sys32[135]="sysfs";
	sys32[136]="personality";
	sys32[138]="setfsuid";
	sys32[139]="setfsgid";
	sys32[140]="_llseek";
	sys32[141]="getdents";
	sys32[142]="_newselect";
	sys32[143]="flock";
	sys32[144]="msync";
	sys32[145]="readv";
	sys32[146]="writev";
	sys32[147]="getsid";
	sys32[148]="fdatasync";
	sys32[149]="_sysctl";
	sys32[150]="mlock";
	sys32[151]="munlock";
	sys32[152]="mlockall";
	sys32[153]="munlockall";
	sys32[154]="sched_setparam";
	sys32[155]="sched_getparam";
	sys32[156]="sched_setscheduler";
	sys32[157]="sched_getscheduler";
	sys32[158]="sched_yield";
	sys32[159]="sched_get_priority_max";
	sys32[160]="sched_get_priority_min";
	sys32[161]="sched_rr_get_interval";
	sys32[162]="nanosleep";
	sys32[163]="mremap";
	sys32[164]="setresuid";
	sys32[165]="getresuid";
	sys32[166]="vm86";
	sys32[167]="query_module";
	sys32[168]="poll";
	sys32[169]="nfsservctl";
	sys32[170]="setresgid";
	sys32[171]="getresgid";
	sys32[172]="prctl";
	sys32[173]="rt_sigreturn";
	sys32[174]="rt_sigaction";
	sys32[175]="rt_sigprocmask";
	sys32[176]="rt_sigpending";
	sys32[177]="rt_sigtimedwait";
	sys32[178]="rt_sigqueueinfo";
	sys32[179]="rt_sigsuspend";
	sys32[180]="pread64";
	sys32[181]="pwrite64";
	sys32[182]="chown";
	sys32[183]="getcwd";
	sys32[184]="capget";
	sys32[185]="capset";
	sys32[186]="sigaltstack";
	sys32[187]="sendfile";
	sys32[188]="getpmsg";
	sys32[189]="putpmsg";
	sys32[190]="vfork";
	sys32[191]="ugetrlimit";
	sys32[192]="mmap2";
	sys32[193]="truncate64";
	sys32[194]="ftruncate64";
	sys32[195]="stat64";
	sys32[196]="lstat64";
	sys32[197]="fstat64";
	sys32[198]="lchown32";
	sys32[199]="getuid32";
	sys32[200]="getgid32";
	sys32[201]="geteuid32";
	sys32[202]="getegid32";
	sys32[203]="setreuid32";
	sys32[204]="setregid32";
	sys32[205]="getgroups32";
	sys32[206]="setgroups32";
	sys32[207]="fchown32";
	sys32[208]="setresuid32";
	sys32[209]="getresuid32";
	sys32[210]="setresgid32";
	sys32[211]="getresgid32";
	sys32[212]="chown32";
	sys32[213]="setuid32";
	sys32[214]="setgid32";
	sys32[215]="setfsuid32";
	sys32[216]="setfsgid32";
	sys32[217]="pivot_root";
	sys32[218]="mincore";
	sys32[219]="madvise";
	sys32[220]="getdents64";
	sys32[221]="fcntl64";
	sys32[224]="gettid";
	sys32[225]="readahead";
	sys32[226]="setxattr";
	sys32[227]="lsetxattr";
	sys32[228]="fsetxattr";
	sys32[229]="getxattr";
	sys32[230]="lgetxattr";
	sys32[231]="fgetxattr";
	sys32[232]="listxattr";
	sys32[233]="llistxattr";
	sys32[234]="flistxattr";
	sys32[235]="removexattr";
	sys32[236]="lremovexattr";
	sys32[237]="fremovexattr";
	sys32[238]="tkill";
	sys32[239]="sendfile64";
	sys32[240]="futex";
	sys32[241]="sched_setaffinity";
	sys32[242]="sched_getaffinity";
	sys32[243]="set_thread_area";
	sys32[244]="get_thread_area";
	sys32[245]="io_setup";
	sys32[246]="io_destroy";
	sys32[247]="io_getevents";
	sys32[248]="io_submit";
	sys32[249]="io_cancel";
	sys32[250]="fadvise64";
	sys32[252]="exit_group";
	sys32[253]="lookup_dcookie";
	sys32[254]="epoll_create";
	sys32[255]="epoll_ctl";
	sys32[256]="epoll_wait";
	sys32[257]="remap_file_pages";
	sys32[258]="set_tid_address";
	sys32[259]="timer_create";
	sys32[260]="timer_settime";
	sys32[261]="timer_gettime";
	sys32[262]="timer_getoverrun";
	sys32[263]="timer_delete";
	sys32[264]="clock_settime";
	sys32[265]="clock_gettime";
	sys32[266]="clock_getres";
	sys32[267]="clock_nanosleep";
	sys32[268]="statfs64";
	sys32[269]="fstatfs64";
	sys32[270]="tgkill";
	sys32[271]="utimes";
	sys32[272]="fadvise64_64";
	sys32[273]="vserver";
	sys32[274]="mbind";
	sys32[275]="get_mempolicy";
	sys32[276]="set_mempolicy";
	sys32[277]="mq_open";
	sys32[278]="mq_unlink";
	sys32[279]="mq_timedsend";
	sys32[280]="mq_timedreceive";
	sys32[281]="mq_notify";
	sys32[282]="mq_getsetattr";
	sys32[283]="kexec_load";
	sys32[284]="waitid";
	sys32[285]="sys_setaltroot";
	sys32[286]="add_key";
	sys32[287]="request_key";
	sys32[288]="keyctl";
	sys32[289]="ioprio_set";
	sys32[290]="ioprio_get";
	sys32[291]="inotify_init";
	sys32[292]="inotify_add_watch";
	sys32[293]="inotify_rm_watch";
	sys32[294]="migrate_pages";
	sys32[295]="openat";
	sys32[296]="mkdirat";
	sys32[297]="mknodat";
	sys32[298]="fchownat";
	sys32[299]="futimesat";
	sys32[300]="fstatat64";
	sys32[301]="unlinkat";
	sys32[302]="renameat";
	sys32[303]="linkat";
	sys32[304]="symlinkat";
	sys32[305]="readlinkat";
	sys32[306]="fchmodat";
	sys32[307]="faccessat";
	sys32[308]="pselect6";
	sys32[309]="ppoll";
	sys32[310]="unshare";
	sys32[311]="set_robust_list";
	sys32[312]="get_robust_list";
	sys32[313]="splice";
	sys32[314]="sync_file_range";
	sys32[315]="tee";
	sys32[316]="vmsplice";
	sys32[317]="move_pages";
	sys32[318]="getcpu";
	sys32[319]="epoll_pwait";
	sys32[320]="utimensat";
	sys32[321]="signalfd";
	sys32[322]="timerfd_create";
	sys32[323]="eventfd";
	sys32[324]="fallocate";
	sys32[325]="timerfd_settime";
	sys32[326]="timerfd_gettime";
	sys32[327]="signalfd4";
	sys32[328]="eventfd2";
	sys32[329]="epoll_create1";
	sys32[330]="dup3";
	sys32[331]="pipe2";
	sys32[332]="inotify_init1";
	sys32[333]="preadv";
	sys32[334]="pwritev";
	sys32[335]="rt_tgsigqueueinfo";
	sys32[336]="perf_event_open";
	sys32[337]="recvmmsg";
	sys32[338]="fanotify_init";
	sys32[339]="fanotify_mark";
	sys32[340]="prlimit64";
	sys32[341]="name_to_handle_at";
	sys32[342]="open_by_handle_at";
	sys32[343]="clock_adjtime";
	sys32[344]="syncfs";
	sys32[345]="sendmmsg";
	sys32[346]="setns";
	sys32[347]="process_vm_readv";
	sys32[348]="process_vm_writev";
}


char const *sysno32(unsigned sysno)
{
	if (sysno > sizeof(sys32)-1) {
		return "<invalid>";
	}
	return sys32[sysno];
}
