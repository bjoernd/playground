TARGET = ex_vdso

SRC_C = parse_vdso.c main.c
CFLAGS = -Wall -std=c99 -Wno-pointer-sign
CC=colorgcc

$(TARGET) : $(SRC_C:.c=.o)
	$(CC) -o $(TARGET) $?

.PHONY : clean

clean :
	$(RM) $(SRC_C:.c=.o)

cleanall : clean
	$(RM) $(TARGET)
