OBJ=pttest.o sys32.o sys64.o

TARGET=pt
CFLAGS=-Wall

.PHONY : all clean cleanall

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ) : Makefile

clean :
	$(RM) $(OBJ)

cleanall : clean
	$(RM) $(TARGET)
