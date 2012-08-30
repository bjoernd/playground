OBJ = ud.o

-include Makeconf.udis86
LDFLAGS += -L$(UDISLIBDIR) -ludis86 -lboost_serialization
CXXFLAGS = -Wall -I$(UDISINCDIR) #-std=c++11

TARGET = udserial

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $< $(LDFLAGS)

clean cleanall :
	$(RM) $(OBJ) $(TARGET)
