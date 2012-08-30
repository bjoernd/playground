OBJ = foo.o
TARGETS = foo

CFLAGS = -Wall -I/home/doebel/local/include
LDFLAGS = -L/home/doebel/local/lib -ludis86

.PHONY : all clean cleanall

all : $(TARGETS)

foo: $(OBJ)
	gcc $(OBJ) $(LDFLAGS) -o $@

$(OBJ) : Makefile

clean :
	$(RM) $(OBJ)

cleanall : clean
	$(RM) $(TARGETS)
