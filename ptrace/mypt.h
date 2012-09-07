extern char *sys32[350];
extern char *sys64[320];

void init32();
char const *sysno32(unsigned sysno);
#if __WORDSIZE == 64
void init64();
char const *sysno64(unsigned sysno);
#endif
