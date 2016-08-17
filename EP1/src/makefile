CXX = g++
CXXFLAGS = -I$(IDIR) 
IDIR = ../include
ODIR = ../obj
LIBS = -fopenmp

_DEPS = prime.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = prime.o main.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

testEP1: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 