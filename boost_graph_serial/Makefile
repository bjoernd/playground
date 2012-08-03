OBJ = graphserial.o
DOT = foo.dot foo2.dot
TARGETS = graphser foo.png foo2.png

CXXFLAGS = -Wall

.PHONY : all clean cleanall

all : $(TARGETS)

graphser: $(OBJ)
	$(CXX) $(OBJ) -o $@ -lboost_serialization

$(OBJ) : Makefile

%.dot : graphser
	@./graphser

%.png : %.dot
	@dot -Tpng $< >$@

clean :
	$(RM) $(OBJ)
	$(RM) $(DOT)
	$(RM) graph.dat

cleanall : clean
	$(RM) $(TARGETS)
