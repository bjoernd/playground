OBJ = serialize.o
TARGETS = sertest

CXXFLAGS = -Wall

.PHONY : all clean cleanall

all : $(TARGETS)

sertest: $(OBJ)
	$(CXX) $(OBJ) -o $@ -lboost_serialization

$(OBJ) : Makefile

clean :
	$(RM) $(OBJ)

cleanall : clean
	$(RM) $(TARGETS)
