CXX = g++
CXXFLAGS = -I$(IDIR)
IDIR = ../include
ODIR = ../obj
LIBS = -lpthreads

_DEPS = ocean.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ocean.o main.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

testEP1: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
