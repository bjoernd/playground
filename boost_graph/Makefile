OBJ = bgl.o
DOT = foo.dot
TARGETS = bgl foo.png

CXXFLAGS = -Wall

.PHONY : all clean cleanall

all : $(TARGETS)

bgl : $(OBJ)
	$(CXX) $(OBJ) -o bgl

$(OBJ) : Makefile

%.dot : bgl
	@./bgl

foo.png : foo.dot
	@dot -Tpng $< >$@

clean :
	$(RM) $(OBJ)
	$(RM) $(DOT)

cleanall : clean
	$(RM) $(TARGETS)
